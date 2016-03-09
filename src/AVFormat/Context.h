//
// Created by Дмитрий Пацура on 06.03.16.
//

#ifndef FFMPEG_TEST_FORMATCONTEXT_H
#define FFMPEG_TEST_FORMATCONTEXT_H

#include <string>
#include "../CFFmpeg.h"
#include "../AVCodec/Codec.h"
#include "Stream.h"

namespace FFmpeg {
    namespace AVFormat {
        class FormatContext {
        protected:
            CFFmpeg::AVFormatContext *formatContext;
        public:
            void openFile(std::string url) throw(std::exception);

            FormatContext() {
                this->formatContext = CFFmpeg::avformat_alloc_context();
            }

            ~FormatContext() {
                CFFmpeg::avformat_free_context(this->formatContext);
            }

            void findStreamInfo() throw(std::exception);

            void dump();

            uint8_t streamsCount();

            int getProbeScore();

            FFmpeg::Codec::Codec *getVideoCodec();

            Stream *getStream(int id);

            void closeInput();
        };
    }
}

#endif //FFMPEG_TEST_FORMATCONTEXT_H
