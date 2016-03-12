//
// Created by Дмитрий Пацура on 12.03.16.
//

#include "Frame.h"

void FFmpeg::AVUtil::Frame::setWidth(int width) {
    this->frame->width = width;
}

void FFmpeg::AVUtil::Frame::setHeight(int height) {
    this->frame->height = height;
}

void FFmpeg::AVUtil::Frame::setFormat(CFFmpeg::AVPixelFormat format) {
    this->frame->format = format;
}
