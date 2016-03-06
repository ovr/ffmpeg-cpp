//
// Created by Дмитрий Пацура on 06.03.16.
//

#include "FormatContext.h"

int FormatContext::openFile(std::string url) {
    return avformat_open_input(&this->formatContext, url.c_str(), nullptr, nullptr);
}
