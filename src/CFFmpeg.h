//
// Created by Дмитрий Пацура on 09.03.16.
//

#ifndef FFMPEG_TEST_CFFMPEG_H
#define FFMPEG_TEST_CFFMPEG_H

namespace CFFmpeg {
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

#endif //FFMPEG_TEST_CFFMPEG_H