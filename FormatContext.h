//
// Created by Дмитрий Пацура on 06.03.16.
//

#ifndef FFMPEG_TEST_FORMATCONTEXT_H
#define FFMPEG_TEST_FORMATCONTEXT_H

extern "C" {
#include <libavformat/avformat.h>
};

#include <string>

class FormatContext {
protected:
    AVFormatContext *formatContext;
public:
    int openFile(std::string url);
    FormatContext() {
        this->formatContext = avformat_alloc_context();
    }
    ~FormatContext() {
        avformat_free_context(this->formatContext);
    }
};


#endif //FFMPEG_TEST_FORMATCONTEXT_H
