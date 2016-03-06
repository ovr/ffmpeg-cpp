//
// Created by Дмитрий Пацура on 06.03.16.
//

#ifndef FFMPEG_TEST_FORMATCONTEXT_H
#define FFMPEG_TEST_FORMATCONTEXT_H

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/error.h>
#include <libavutil/avutil.h>
};

#include <string>

class FormatContext {
protected:
    AVFormatContext *formatContext;
public:
    void openFile(std::string url);
    FormatContext() {
        this->formatContext = avformat_alloc_context();
    }
    ~FormatContext() {
        avformat_free_context(this->formatContext);
    }

    void findStreamInfo();

    void dump();

    uint8_t streamsCount();
};


#endif //FFMPEG_TEST_FORMATCONTEXT_H
