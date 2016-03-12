//
// Created by Дмитрий Пацура on 10.03.16.
//

#ifndef FFMPEG_TEST_CODECCONTEXT_H
#define FFMPEG_TEST_CODECCONTEXT_H

#include "../CFFmpeg.h"
#include "Codec.h"

namespace FFmpeg {
    namespace Codec {
        class CodecContext {
        protected:
            CFFmpeg::AVCodecContext *context;
        public:
            CodecContext(CFFmpeg::AVCodecContext *context) {
                this->context = context;
            }

            int getBitRate();

            int getWidth();

            int getHeight();

            CFFmpeg::AVPixelFormat getFormat();

            FFmpeg::Codec::Codec *getCodec() throw(std::exception);
        };
    }
}


#endif //FFMPEG_TEST_CODECCONTEXT_H
