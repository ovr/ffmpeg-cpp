//
// Created by Дмитрий Пацура on 12.03.16.
//

#include "Packet.h"

int FFmpeg::AVCodec::Packet::getStreamIndex() {
    return this->packet->stream_index;
}
