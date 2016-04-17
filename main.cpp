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
                << "\t\t Bit rate " << codecContext->getBitRate() << endl
                << "\t\t Delay " << codecContext->getDelay() << endl;

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

        auto *videoStreamCodecContext = videoStream->codecContext();
        auto *videoFrame = new(FFmpeg::AVUtil::Frame);
        cout << "VideoStream->CodecContext Width " << videoStreamCodecContext->getWidth() << endl;
        cout << "VideoStream->CodecContext Height " << videoStreamCodecContext->getHeight() << endl;

        const auto imageQuantumFormat = CFFmpeg::AVPixelFormat::AV_PIX_FMT_RGB24;
        auto *videoFrameRGB = new FFmpeg::AVUtil::Frame(imageQuantumFormat, videoStreamCodecContext->getWidth(), videoStreamCodecContext->getHeight());

        auto *swContext = new FFmpeg::SWScale::Context(
                videoStreamCodecContext->getWidth(),
                videoStreamCodecContext->getHeight(),
                videoStreamCodecContext->getFormat(),
                videoStreamCodecContext->getWidth(),
                videoStreamCodecContext->getHeight(),
                CFFmpeg::AVPixelFormat::AV_PIX_FMT_RGB24
        );
        delete swContext;

        int code = 0;
        int *frameFinished = new int(0);

        while (code == 0) {
            auto *packet = new(FFmpeg::AVCodec::Packet);
            cout << "Read packet..." << endl;

            code = inputFormatContext->readFrame(packet);
            if (code == 0 && packet->getStreamIndex() == videoStream->getIndex()) {
                cout << "Tick video packet..." << endl;

                auto buffer = videoStream->decodeVideoPacket(packet, frameFinished, videoFrame);
                cout << "Decode buff " << buffer << endl;

                if (*frameFinished > 0) {
                    auto transform = swContext->scale(
                            videoFrame->getData(),
                            videoFrame->getLineSize(),
                            0,
                            videoStreamCodecContext->getHeight(),
                            videoFrameRGB->getData(),
                            videoFrame->getLineSize()
                    );
                    cout << "Out height" << transform << endl;
                }
            }

            delete packet;
        }

        delete frameFinished;

        delete videoFrameRGB;
        delete videoFrame;

        inputFormatContext->closeInput();
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }

    delete inputFormatContext;
}

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
