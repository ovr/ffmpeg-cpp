//
// Created by Дмитрий Пацура on 06.03.16.
//

#include "Context.h"

namespace FFmpeg {
    namespace AVFormat {
        void FormatContext::openFile(std::string url) throw(std::exception) {
            CFFmpeg_CHECK_EXCEPTION(avformat_open_input(&this->formatContext, url.c_str(), nullptr, nullptr));
        }

        void FormatContext::findStreamInfo() throw(std::exception) {
            CFFmpeg_CHECK_EXCEPTION(avformat_find_stream_info(this->formatContext, nullptr));
        }

        void FormatContext::dump() {
            av_dump_format(this->formatContext, 0, nullptr, 0);
        }

        uint8_t FormatContext::streamsCount() {
            return (uint8_t) this->formatContext->nb_streams;
        }

        int FormatContext::getProbeScore() {
            return av_format_get_probe_score(this->formatContext);
        }

        void FormatContext::closeInput() {
            avformat_close_input(&this->formatContext);
        }

        FFmpeg::Codec::Codec *FormatContext::getVideoCodec() {
            return new FFmpeg::Codec::Codec(av_format_get_video_codec(this->formatContext));
        }

        Stream *FormatContext::getStream(int id) {
            return new Stream(this->formatContext->streams[id]);
        }
    }
}