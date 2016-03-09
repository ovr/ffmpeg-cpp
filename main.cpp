#include <iostream>
#include "src/AVFormat/Context.h"

using namespace std;

int main() {
    string filename = "/Users/ovr/ClionProjects/ffmpeg-test/1.mp4";

    AVFormat::av_register_all();
    AVFormat::avcodec_register_all();
    
    auto inputFormatContext = new (AVFormat::FormatContext);

    try {
        inputFormatContext->openFile(filename);
        inputFormatContext->findStreamInfo();
        inputFormatContext->dump();

        cout << "Streams-count " << int(inputFormatContext->streamsCount()) << endl;
        cout << "Probe score " << inputFormatContext->getProbeScore() << endl;

        cout << AVFormat::avformat_version() << endl;

        inputFormatContext->closeInput();
    } catch (int e) {
        cout << AVFormat::av_err2str(e) << endl;
    }

    delete inputFormatContext;
}

//
//    av_dump_format(inputFormatContext, 0, nullptr, 0);
//
//    for (int i = 0; i < inputFormatContext->nb_streams; i++) {
//        auto *currentStream = inputFormatContext->streams[i];
//        if (currentStream->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
//            videoStream = currentStream;
//        }
//    }
//
//    if (videoStream == nullptr) {
//        cout << "No video stream :(" << endl;
//        return 0;
//    }
//
//    cout << "Video Stream" << endl;
//    cout << "Index " << videoStream->index << endl;
//    cout << "Id " << videoStream->id << endl;
//
//
//    AVCodec *videoCodec = nullptr;
//    videoCodec = avcodec_find_decoder(videoStream->codec->codec_id);
//    if (videoCodec == nullptr) {
//        cout << "Cannot open codec decoder :(" << endl;
//        return 0;
//    }
//
//    /**
//     * @return zero on success, a negative value on error
//     */
//    code = avcodec_open2(videoStream->codec, videoCodec, nullptr);
//    if (code < 0) {
//        cout << "Cannot avcodec_open2 for videoStream :(" << endl;
//        return 0;
//    }
//
//
//    /**
//     * Исходный кадр
//     */
//    AVFrame *videoFrame = nullptr;
//    videoFrame = av_frame_alloc();
//    if (videoFrame == nullptr) {
//        cout << "Cannot allocate memory for videoFrame for next decoding for it" << endl;
//        return 0;
//    }
//
//    AVFrame *videoFrameRGB;
//    videoFrameRGB = av_frame_alloc();
//    if (videoFrameRGB == nullptr) {
//        cout << "Cannot allocate memory for videoFrameRGB for next converting for it" << endl;
//        return 0;
//    }
//
//    cout << "VideoStream->CodecContext Width " << videoStream->codec->width << endl;
//    cout << "VideoStream->CodecContext Height " << videoStream->codec->height << endl;
//
//    const auto imageQuantumFormat = AVPixelFormat::AV_PIX_FMT_RGB24;
//    videoFrameRGB->format = imageQuantumFormat;
//    videoFrameRGB->width = videoStream->codec->width;
//    videoFrameRGB->height = videoStream->codec->height;
//
//    auto swContext = sws_getContext(
//        videoStream->codec->width,
//        videoStream->codec->height,
//        videoStream->codec->pix_fmt,
//        videoStream->codec->width,
//        videoStream->codec->height,
//        PIX_FMT_RGB24,
//        SWS_FAST_BILINEAR,
//        nullptr,
//        nullptr,
//        nullptr
//    );
//
//    avpicture_alloc((AVPicture*) videoFrameRGB, imageQuantumFormat, videoStream->codec->width, videoStream->codec->height);
//
//    AVPacket *packet;
//    int frameFinished;
//    packet = new(AVPacket);
//
//    while (true) {
//        av_init_packet(packet);
//
//        cout << "Read packet..." << endl;
//
//        code = av_read_frame(inputFormatContext, packet);
//        if (code < 0) {
//            if (code == AVERROR_EOF) {
//                /** It is the of file */
//                break;
//            } else {
//                cout << av_err2str(code) << endl;
//                return 0;
//            }
//        }
//
//        /** This packet is a packet from video stream (Frame) */
//        if (packet->stream_index == videoStream->index) {
//
//            /**
//             * @return On error a negative value is returned, otherwise the number of bytes
//             * used or zero if no frame could be decompressed.
//             * */
//            code = avcodec_decode_video2(videoStream->codec, videoFrame, &frameFinished, packet);
//            cout << "Decode buff " << code << endl;
//
//            /**
//             * Return the height of the output slice
//             */
//            if (frameFinished > 0) {
//                code = sws_scale(
//                        swContext,
//                        videoFrame->data,
//                        videoFrame->linesize,
//                        0,
//                        videoStream->codec->height,
//                        videoFrameRGB->data,
//                        videoFrameRGB->linesize
//                );
//
//                cout << "Out height" << code << endl;
//                av_free_packet(packet);
//
//
//                saveVideoFrame(videoFrameRGB, videoStream, inputFormatContext);
//                break;
//            }
//        }
//
//        av_free_packet(packet);
//    }
//
//
//    av_frame_free(&videoFrame);
//    av_frame_free(&videoFrameRGB);
//
//    sws_freeContext(swContext);
//
//    return 0;
//}
//
//void saveVideoFrame(AVFrame *pFrame, AVStream *videoStream, AVFormatContext *inputFormatContext) {
//    int tmp;
//
//    AVCodec *outCodec = avcodec_find_encoder(CODEC_ID_PNG);
//    if (!outCodec) {
//        cout << "Cannot avcodec_find_encoder for image :(" << endl;
//        return;
//    }
//
//    AVCodecContext *outCodecCtx = avcodec_alloc_context3(outCodec);
//
//    outCodecCtx->width = videoStream->codec->width;
//    outCodecCtx->height = videoStream->codec->height;
//    outCodecCtx->pix_fmt = (AVPixelFormat) pFrame->format;
//    outCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
//    outCodecCtx->time_base.num = videoStream->codec->time_base.num;
//    outCodecCtx->time_base.den = videoStream->codec->time_base.den;
//
//    tmp = avcodec_open2(outCodecCtx, outCodec, nullptr);
//    if (tmp < 0) {
//        cout << "Cannot avcodec_open2 for image :(" << endl;
//        return;
//    }
//
//    auto packet = getNewPacket();
//    int gotFrame = 0;
//
//    tmp = avcodec_encode_video2(outCodecCtx, packet, pFrame, &gotFrame);
//    cout << "Encode status " << tmp << endl;
//
//    FILE * outPng = fopen("/Users/ovr/projects/ovr/test/1.png", "wb");
//    fwrite(packet->data, packet->size, 1, outPng);
//    fclose(outPng);
//
//    avcodec_free_context(&outCodecCtx);
//}
