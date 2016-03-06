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
