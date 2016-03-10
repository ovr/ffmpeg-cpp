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
