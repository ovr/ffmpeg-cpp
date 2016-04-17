//
// Created by Дмитрий Пацура on 10.03.16.
//

#include "CodecContext.h"

namespace FFmpeg {
    namespace Codec {

    }
}

int FFmpeg::Codec::CodecContext::getBitRate() {
    return this->context->bit_rate;
}

FFmpeg::Codec::Codec *FFmpeg::Codec::CodecContext::getCodec() throw(std::exception) {
    auto codec = avcodec_find_decoder(this->context->codec_id);
    if (codec == nullptr) {
        throw std::runtime_error("Cannot open codec");
    }

    CFFmpeg_CHECK_EXCEPTION(avcodec_open2(this->context, codec, nullptr))
    return new FFmpeg::Codec::Codec((CFFmpeg::AVCodec*)(this->context->codec));
}

int FFmpeg::Codec::CodecContext::getWidth() {
    return this->context->width;
}

int FFmpeg::Codec::CodecContext::getHeight() {
    return this->context->height;
}

CFFmpeg::AVPixelFormat FFmpeg::Codec::CodecContext::getFormat() {
    return this->context->pix_fmt;
}

int FFmpeg::Codec::CodecContext::getDelay() {
    return this->context->delay;
}
