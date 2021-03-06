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

        FFmpeg::Codec::CodecContext* Stream::codecContext() {
            return new Codec::CodecContext(this->stream->codec);
        }

        int Stream::decodeVideoPacket(FFmpeg::AVCodec::Packet *packet, int *frameFinished, FFmpeg::AVUtil::Frame *frame) {
            return CFFmpeg::avcodec_decode_video2(
                    this->stream->codec, frame->getStruct(), frameFinished, packet->getStruct()
            );
        }

        bool Stream::isVideo() {
            return this->stream->codec->codec_type == CFFmpeg::AVMEDIA_TYPE_VIDEO;
        }

        bool Stream::isAudio() {
            return this->stream->codec->codec_type == CFFmpeg::AVMEDIA_TYPE_AUDIO;
        }
    }
}
