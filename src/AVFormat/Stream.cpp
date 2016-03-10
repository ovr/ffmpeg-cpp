//
// Created by Дмитрий Пацура on 09.03.16.
//

#include "Stream.h"

namespace FFmpeg {
    namespace AVFormat {
        int FFmpeg::AVFormat::Stream::getId() {
            return this->stream->id;
        }

        int Stream::getIndex() {
            return this->stream->index;
        }

        int Stream::getDuration() {
            return int(this->stream->duration);
        }

        int Stream::framesCount() {
            return int(this->stream->nb_frames);
        }

        FFmpeg::Codec::CodecContext Stream::codecContext() {
            return Codec::CodecContext(this->stream->codec);
        }
    }
}
