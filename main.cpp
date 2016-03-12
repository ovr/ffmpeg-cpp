#include <iostream>

#include "src/FFmpeg.h"
#include "src/AVCodec/Packet.h"

using namespace std;

int main() {
    string filename = "/Users/ovr/ClionProjects/ffmpeg-test/1.mp4";

    CFFmpeg::av_register_all();
    CFFmpeg::avcodec_register_all();

    cout
        << endl
        << "Version of avformat " << CFFmpeg::avformat_version() << endl;


    auto inputFormatContext = new (FFmpeg::AVFormat::FormatContext);

    try {
        inputFormatContext->openFile(filename);
        inputFormatContext->findStreamInfo();
        //inputFormatContext->dump();

        cout << "Streams-count " << int(inputFormatContext->streamsCount()) << endl;
        cout << "Probe score " << inputFormatContext->getProbeScore() << endl;

        cout << "Stream count " << inputFormatContext->streamsCount() << endl;

        FFmpeg::AVFormat::Stream *videoStream = nullptr;

        for (int streamId = 0; streamId < inputFormatContext->streamsCount(); streamId++) {
            auto stream = inputFormatContext->getStream(streamId);
            if (stream->isVideo()) {
                videoStream = stream;
            }

            cout
                << "Stream (" << streamId << ")" << endl
                << "\t Id " << stream->getId() << endl
                << "\t Index " << stream->getIndex() << endl
                << "\t Duration " << stream->getDuration() << endl
                << "\t Frames Count " << stream->framesCount() << endl;

            auto codecContext = stream->codecContext();
            cout
                << "\t CodecContext " << endl
                << "\t\t Bit rate " << codecContext->getBitRate() << endl;

            auto codec = codecContext->getCodec();
            cout
                << "\t CodecContext->Codec " << endl
                << "\t\t Name " << codec->getName() << endl;
        }

        cout << endl;

        if (videoStream == nullptr) {
            cout << "No video stream :(" << endl;
            return 0;
        } else {
            cout << "Video stream found (" << videoStream->getIndex() << ", "  << videoStream->getId() << ")" << endl;
        }

        cout << endl;

        auto *videoFrame = new(FFmpeg::AVUtil::Frame);
        auto *videoFrameRGB = new(FFmpeg::AVUtil::Frame);

        cout << "VideoStream->CodecContext Width " << videoStream->codecContext()->getWidth() << endl;
        cout << "VideoStream->CodecContext Height " << videoStream->codecContext()->getHeight() << endl;

        const auto imageQuantumFormat = CFFmpeg::AVPixelFormat::AV_PIX_FMT_RGB24;
        videoFrameRGB->setFormat(imageQuantumFormat);
        videoFrameRGB->setWidth(videoStream->codecContext()->getWidth());
        videoFrameRGB->setHeight(videoStream->codecContext()->getHeight());

        auto *swContext = new FFmpeg::SWScale::Context(
                videoStream->codecContext()->getWidth(),
                videoStream->codecContext()->getHeight(),
                videoStream->codecContext()->getFormat(),
                videoStream->codecContext()->getWidth(),
                videoStream->codecContext()->getHeight(),
                CFFmpeg::PIX_FMT_RGB24
        );
        delete swContext;

        auto *packet = new(FFmpeg::AVCodec::Packet);
        delete packet;

        delete videoFrameRGB;
        delete videoFrame;

        inputFormatContext->closeInput();
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    delete inputFormatContext;
}

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
