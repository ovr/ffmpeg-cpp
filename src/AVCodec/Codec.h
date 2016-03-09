//
// Created by Дмитрий Пацура on 09.03.16.
//

#ifndef FFMPEG_TEST_CODEC_H
#define FFMPEG_TEST_CODEC_H

extern "C" {
    #include <libavcodec/avcodec.h>
}


namespace FFmpeg {
    namespace Codec {
        class Codec {
        protected:
            AVCodec *codec;
        public:
            Codec(AVCodec *codec) {
                this->codec = codec;
            }

            int getId();
        };
    }
}

#endif //FFMPEG_TEST_CODEC_H
