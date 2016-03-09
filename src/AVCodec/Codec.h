//
// Created by Дмитрий Пацура on 09.03.16.
//

#ifndef FFMPEG_TEST_CODEC_H
#define FFMPEG_TEST_CODEC_H

namespace CAVCodec {
    extern "C" {
        #include <libavformat/avformat.h>
        #include <libavutil/error.h>
        #include <libavutil/avutil.h>
        #include <libswscale/swscale.h>
        #include <libavutil/error.h>
        #include <libavutil/avutil.h>
        #include <libavformat/avformat.h>
        #include <libavcodec/avcodec.h>
    }
}

namespace FFmpeg {
    namespace Codec {
        class Codec {
        protected:
            CAVCodec::AVCodec *codec;
        public:
            Codec(CAVCodec::AVCodec *codec) {
                this->codec = codec;
            }

            int getId();
        };
    }
}

#endif //FFMPEG_TEST_CODEC_H
