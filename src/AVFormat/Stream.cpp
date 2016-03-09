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
    }
}
