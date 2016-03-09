//
// Created by Дмитрий Пацура on 06.03.16.
//

#include "FormatContext.h"

namespace AvFormat {
    void FormatContext::openFile(std::string url) throw(int) {
        auto tmp = avformat_open_input(&this->formatContext, url.c_str(), nullptr, nullptr);
        if (tmp < 0) {
            throw tmp;
        }
    }

    void FormatContext::findStreamInfo() throw(int) {
        auto tmp = avformat_find_stream_info(this->formatContext, nullptr);
        if (tmp < 0) {
            throw tmp;
        }
    }

    void FormatContext::dump() throw(int) {
        av_dump_format(this->formatContext, 0, nullptr, 0);
    }

    uint8_t FormatContext::streamsCount() throw(int) {
        return (uint8_t) this->formatContext->nb_streams;
    }

    int FormatContext::getProbeScore() {
        return av_format_get_probe_score(this->formatContext);
    }

    void FormatContext::closeInput() {
        avformat_close_input(&this->formatContext);
    }

    AVCodec *FormatContext::getVideoCodec() {
        return av_format_get_video_codec(this->formatContext);
    }
}
