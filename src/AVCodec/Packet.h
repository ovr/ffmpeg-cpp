//
// Created by Дмитрий Пацура on 12.03.16.
//

#ifndef FFMPEG_TEST_PACKET_H
#define FFMPEG_TEST_PACKET_H

#include "../CFFmpeg.h"

namespace FFmpeg {
    namespace AVCodec {
        class Packet {
        protected:
            CFFmpeg::AVPacket *packet;
        public:
            Packet() {
                CFFmpeg::av_init_packet(this->packet);
            }
            ~Packet() {
                CFFmpeg::av_free_packet(this->packet);
            }
            CFFmpeg::AVPacket *getStruct() {
                return this->packet;
            }
            int getStreamIndex();
        };
    }
}

#endif //FFMPEG_TEST_PACKET_H
