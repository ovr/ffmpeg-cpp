//
// Created by Дмитрий Пацура on 12.03.16.
//

#include "Context.h"

int FFmpeg::SWScale::Context::scale(const uint8_t* const *srcData, int *srcLineSize, int i, int height, uint8_t* const *dstData,
                                        int *dstLineSize) {
    return CFFmpeg::sws_scale(
            this->context,
            srcData,
            srcLineSize,
            i,
            height,
            dstData,
            dstLineSize
    );
}