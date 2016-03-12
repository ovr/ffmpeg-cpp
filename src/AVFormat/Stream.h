//
// Created by Дмитрий Пацура on 09.03.16.
//

#ifndef FFMPEG_TEST_STREAM_H
#define FFMPEG_TEST_STREAM_H

#include "../CFFmpeg.h"
#include "../AVCodec/CodecContext.h"
#include "../AVUtil/Frame.h"
#include "../AVCodec/Packet.h"

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

            FFmpeg::Codec::CodecContext* codecContext();

            int decodeVideoPacket(FFmpeg::AVCodec::Packet *packet, int *frameFinished, FFmpeg::AVUtil::Frame *frame);

            bool isVideo();

            bool isAudio();
        };
    }
}

#endif //FFMPEG_TEST_STREAM_H
