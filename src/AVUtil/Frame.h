//
// Created by Дмитрий Пацура on 12.03.16.
//

#ifndef FFMPEG_TEST_FRAME_H
#define FFMPEG_TEST_FRAME_H

#include "../CFFmpeg.h"

namespace FFmpeg {
    namespace AVUtil {
        class Frame {
        protected:
            CFFmpeg::AVFrame *frame;
        public:
            Frame() {
                this->frame = CFFmpeg::av_frame_alloc();
            }
        };
    }
}

#endif //FFMPEG_TEST_FRAME_H
