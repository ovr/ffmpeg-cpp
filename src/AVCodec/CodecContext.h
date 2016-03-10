//
// Created by Дмитрий Пацура on 10.03.16.
//

#ifndef FFMPEG_TEST_CODECCONTEXT_H
#define FFMPEG_TEST_CODECCONTEXT_H

#include "../CFFmpeg.h"

namespace FFmpeg {
    namespace Codec {
        class CodecContext {
        protected:
            CFFmpeg::AVCodecContext *context;
        public:
            CodecContext(CFFmpeg::AVCodecContext *context) {
                this->context = context;
            }
        };
    }
}


#endif //FFMPEG_TEST_CODECCONTEXT_H
