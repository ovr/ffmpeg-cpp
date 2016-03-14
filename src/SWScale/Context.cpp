//
// Created by Дмитрий Пацура on 12.03.16.
//

#include "Context.h"

int FFmpeg::SWScale::Context::scale(uint8_t *srcData, int *srcLineSize, int i, int height, uint8_t *dstData,
                                        int *dstLineSize) {
    return CFFmpeg::sws_scale(
            this->context,
            (const uint8_t *const *)srcData,
            srcLineSize,
            i,
            height,
            (uint8_t *const *)dstData,
            dstLineSize
    );
}