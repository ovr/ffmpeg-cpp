//
// Created by Дмитрий Пацура on 06.03.16.
//

#include "FormatContext.h"

void FormatContext::openFile(std::string url) {
    auto tmp = avformat_open_input(&this->formatContext, url.c_str(), nullptr, nullptr);
    if (tmp < 0) {
        throw tmp;
    }
}

void FormatContext::findStreamInfo() {
    auto tmp = avformat_find_stream_info(this->formatContext, nullptr);
    if (tmp < 0) {
        throw tmp;
    }
}

void FormatContext::dump() {
    av_dump_format(this->formatContext, 0, nullptr, 0);
}
