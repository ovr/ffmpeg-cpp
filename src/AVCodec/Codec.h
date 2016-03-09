//
// Created by Дмитрий Пацура on 09.03.16.
//

#ifndef FFMPEG_TEST_CODEC_H
#define FFMPEG_TEST_CODEC_H

#include "../CFFmpeg.h"

namespace FFmpeg {
    namespace Codec {
        class Codec {
        protected:
            CFFmpeg::AVCodec *codec;
        public:
            Codec(CFFmpeg::AVCodec *codec) {
                this->codec = codec;
            }

            int getId();
        };
    }
}

#endif //FFMPEG_TEST_CODEC_H
