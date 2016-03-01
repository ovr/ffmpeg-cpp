#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
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

    av_dump_format(inputFormatContext, 0, nullptr, 0);
    
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

    auto videoFrame = av_frame_alloc();
    auto videoFrameRGB = av_frame_alloc();


    return 0;
}