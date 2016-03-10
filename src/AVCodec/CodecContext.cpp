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

FFmpeg::Codec::Codec *FFmpeg::Codec::CodecContext::getCodec() {
    auto codec = avcodec_find_decoder(this->context->codec_id);
    avcodec_open2(this->context, codec, nullptr);

    return new FFmpeg::Codec::Codec((CFFmpeg::AVCodec*)(this->context->codec));
}
