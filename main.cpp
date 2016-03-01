#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
}

void saveVideoFrame(AVFrame *pFrame, AVStream *videoStream, AVFormatContext *inputFormatContext);

extern AVPacket* getNewPacket()
{
    AVPacket *packet = new(AVPacket);
    av_init_packet(packet);

    packet->size = 0;
    packet->data = nullptr;

    return packet;
}

using namespace std;

int main() {
    string filename = "/Users/ovr/ClionProjects/ffmpeg-test/1.mp4";
    AVStream *videoStream = nullptr;
    int code;

    av_register_all();
    avcodec_register_all();


    AVFormatContext *inputFormatContext;

    //  * @return 0 on success, a negative AVERROR on failure.
    code = avformat_open_input(&inputFormatContext, filename.c_str(), nullptr, nullptr);
    if (code < 0) {
        cout << "Error on avformat_open_input was cause with code " << av_err2str(code) << endl;
        return 0;
    }


    //  * @return >=0 if OK, AVERROR_xxx on error
    code = avformat_find_stream_info(inputFormatContext, nullptr);
    if (code < 0) {
        cout << "Error on avformat_find_stream_info was cause with code " << av_err2str(code) << endl;
        return 0;
    }

    //av_dump_format(inputFormatContext, 0, nullptr, 0);

    for (int i = 0; i < inputFormatContext->nb_streams; i++) {
        auto *currentStream = inputFormatContext->streams[i];
        if (currentStream->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = currentStream;
        }
    }

    if (videoStream == nullptr) {
        cout << "No video stream :(" << endl;
        return 0;
    }

    cout << "Video Stream" << endl;
    cout << "Index " << videoStream->index << endl;
    cout << "Id " << videoStream->id << endl;


    AVCodec *videoCodec = nullptr;
    videoCodec = avcodec_find_decoder(videoStream->codec->codec_id);
    if (videoCodec == nullptr) {
        cout << "Cannot open codec decoder :(" << endl;
        return 0;
    }

    /**
     * @return zero on success, a negative value on error
     */
    code = avcodec_open2(videoStream->codec, videoCodec, nullptr);
    if (code < 0) {
        cout << "Cannot avcodec_open2 for videoStream :(" << endl;
        return 0;
    }


    /**
     * Исходный кадр
     */
    AVFrame *videoFrame = nullptr;
    videoFrame = av_frame_alloc();
    if (videoFrame == nullptr) {
        cout << "Cannot allocate memory for videoFrame for next decoding for it" << endl;
        return 0;
    }

    AVFrame *videoFrameRGB;
    videoFrameRGB = av_frame_alloc();
    if (videoFrameRGB == nullptr) {
        cout << "Cannot allocate memory for videoFrameRGB for next converting for it" << endl;
        return 0;
    }

    cout << "VideoStream->CodecContext Width " << videoStream->codec->width << endl;
    cout << "VideoStream->CodecContext Height " << videoStream->codec->height << endl;

    auto swContext = sws_getContext(
        videoStream->codec->width,
        videoStream->codec->height,
        videoStream->codec->pix_fmt,
        videoStream->codec->width,
        videoStream->codec->height,
        PIX_FMT_RGB24,
        SWS_FAST_BILINEAR,
        nullptr,
        nullptr,
        nullptr
    );

    /**
     * We need to count and fill buffe to videoFrameRGB via it's empty
     */
    int num_bytes = avpicture_get_size(AV_PIX_FMT_RGB24, videoStream->codec->width, videoStream->codec->height);
    uint8_t* frame2_buffer = (uint8_t *) av_malloc(num_bytes * sizeof(uint8_t));
    avpicture_fill((AVPicture*) videoFrameRGB, frame2_buffer, AV_PIX_FMT_RGB24, videoStream->codec->width, videoStream->codec->height);

    videoFrameRGB->format = AVPixelFormat::AV_PIX_FMT_RGB24;
    videoFrameRGB->width = videoStream->codec->width;
    videoFrameRGB->height = videoStream->codec->height;

    AVPacket *packet;
    int frameFinished;
    packet = new(AVPacket);

    while (true) {
        av_init_packet(packet);

        cout << "Read packet..." << endl;

        code = av_read_frame(inputFormatContext, packet);
        if (code < 0) {
            if (code == AVERROR_EOF) {
                /** It is the of file */
                break;
            } else {
                cout << av_err2str(code) << endl;
                return 0;
            }
        }

        /** This packet is a packet from video stream (Frame) */
        if (packet->stream_index == videoStream->index) {

            /**
             * @return On error a negative value is returned, otherwise the number of bytes
             * used or zero if no frame could be decompressed.
             * */
            code = avcodec_decode_video2(videoStream->codec, videoFrame, &frameFinished, packet);
            cout << "Decode buff " << code << endl;

            /**
             * Return the height of the output slice
             */
            if (frameFinished > 0) {
                code = sws_scale(
                        swContext,
                        videoFrame->data,
                        videoFrame->linesize,
                        0,
                        videoStream->codec->height,
                        videoFrameRGB->data,
                        videoFrameRGB->linesize
                );

                cout << "Out height" << code << endl;
                av_free_packet(packet);


                saveVideoFrame(videoFrameRGB, videoStream, inputFormatContext);

                break;
            }
        }

        av_free_packet(packet);
    }

    return 0;
}

void saveVideoFrame(AVFrame *pFrame, AVStream *videoStream, AVFormatContext *inputFormatContext) {
    int tmp;

    AVCodec *outCodec = avcodec_find_encoder(CODEC_ID_PNG);
    if (!outCodec) {
        cout << "Cannot avcodec_find_encoder for image :(" << endl;
        return;
    }

    AVCodecContext *outCodecCtx = avcodec_alloc_context3(outCodec);

    outCodecCtx->width = videoStream->codec->width;
    outCodecCtx->height = videoStream->codec->height;
    outCodecCtx->pix_fmt = PIX_FMT_RGB24;
    outCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    outCodecCtx->time_base.num = videoStream->codec->time_base.num;
    outCodecCtx->time_base.den = videoStream->codec->time_base.den;

    tmp = avcodec_open2(outCodecCtx, outCodec, nullptr);
    if (tmp < 0) {
        cout << "Cannot avcodec_open2 for image :(" << endl;
        return;
    }

    auto packet = getNewPacket();
    int gotFrame = 0;

    tmp = avcodec_encode_video2(outCodecCtx, packet, pFrame, &gotFrame);
    cout << "Encode status " << tmp << endl;

    FILE * outPng = fopen("/Users/ovr/projects/ovr/test/1.png", "wb");
    fwrite(packet->data, packet->size, 1, outPng);
    fclose(outPng);
}
