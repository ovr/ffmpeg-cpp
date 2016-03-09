//
// Created by Дмитрий Пацура on 06.03.16.
//

#ifndef FFMPEG_TEST_FORMATCONTEXT_H
#define FFMPEG_TEST_FORMATCONTEXT_H

#include <string>
#include "../CFFmpeg.h"
#include "../AVCodec/Codec.h"

namespace FFmpeg {
    namespace AVFormat {
        class FormatContext {
        protected:
            CFFmpeg::AVFormatContext *formatContext;
        public:
            void openFile(std::string url) throw(int);

            FormatContext() {
                this->formatContext = CFFmpeg::avformat_alloc_context();
            }

            ~FormatContext() {
                CFFmpeg::avformat_free_context(this->formatContext);
            }

            void findStreamInfo() throw(int);

            void dump() throw(int);

            uint8_t streamsCount() throw(int);

            int getProbeScore();

            FFmpeg::Codec::Codec *getVideoCodec();

            void closeInput();
        };
    }
}

#endif //FFMPEG_TEST_FORMATCONTEXT_H
