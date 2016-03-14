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
            ~Frame() {
                CFFmpeg::av_frame_free(&this->frame);
            }

            void setWidth(int width);

            void setHeight(int height);

            void setFormat(CFFmpeg::AVPixelFormat format);

            CFFmpeg::AVFrame *getStruct() {
                return this->frame;
            }

            uint8_t *getData();
            int *getLineSize();
        };
    }
}

#endif //FFMPEG_TEST_FRAME_H
