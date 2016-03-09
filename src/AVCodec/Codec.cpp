//
// Created by Дмитрий Пацура on 09.03.16.
//

#include "Codec.h"

namespace FFmpeg {
    namespace Codec {
        int Codec::getId() {
            return this->codec->id;
        }

        std::string Codec::getName() {
            return std::string(this->codec->name);
        }
    }
}