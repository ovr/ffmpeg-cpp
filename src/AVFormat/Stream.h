//
// Created by Дмитрий Пацура on 09.03.16.
//

#ifndef FFMPEG_TEST_STREAM_H
#define FFMPEG_TEST_STREAM_H

#include "../CFFmpeg.h"

namespace FFmpeg {
    namespace AVFormat {
        class Stream {
        protected:
            CFFmpeg::AVStream *stream;
        public:
            Stream(CFFmpeg::AVStream *stream) {
                this->stream = stream;
            }

            int getId();

            int getIndex();

            int getDuration();

            int framesCount();
        };
    }
}

#endif //FFMPEG_TEST_STREAM_H
