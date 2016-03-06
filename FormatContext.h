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
};


#endif //FFMPEG_TEST_FORMATCONTEXT_H
