//
// Created by Дмитрий Пацура on 12.03.16.
//

#ifndef FFMPEG_TEST_CONTEXT_H
#define FFMPEG_TEST_CONTEXT_H

#include "../CFFmpeg.h"

namespace FFmpeg {
    namespace SWScale {
        class Context {
        protected:
            CFFmpeg::SwsContext *context;
        public:
            Context(int srcW, int srcH, enum CFFmpeg::AVPixelFormat srcFormat,
                    int dstW, int dstH, enum CFFmpeg::AVPixelFormat dstFormat) {
                this->context = CFFmpeg::sws_getContext(
                        srcW, srcH, srcFormat,
                        dstW, dstH, dstFormat,
                        0, nullptr, nullptr, nullptr
                );
            }
            ~Context() {
                CFFmpeg::sws_freeContext(this->context);
            }

            int scale(const uint8_t* const *srcData, int *srcLineSize, int i, int height, uint8_t* const *dstData, int *dstLineSize);
        };
    }
}

#endif //FFMPEG_TEST_CONTEXT_H
