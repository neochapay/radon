#ifndef JACKPROCESSOR_H
#define JACKPROCESSOR_H

#include "qjack/processor.h"
#include "qjack/client.h"
#include "qjack/buffer.h"

#include <QAudioDecoder>

class JackProcessor : public QJack::Processor
{
    public:
        JackProcessor(QJack::Client &client);
        ~JackProcessor();

        void setupMp3Decoder();

        QJack::Client client;

        QJack::AudioPort stream_out_l;
        QJack::AudioPort stream_out_r;
        QJack::AudioPort dj_out_l;
        QJack::AudioPort dj_out_r;
        QJack::AudioPort dj_in_l;
        QJack::AudioPort dj_in_r;
        QJack::AudioPort aux_in_l;
        QJack::AudioPort aux_in_r;
        QJack::AudioPort alarm_l;
        QJack::AudioPort alarm_r;

        QJack::AudioRingBuffer ringBufferLeft;
        QJack::AudioRingBuffer ringBufferRight;

        QAudioDecoder audioDecoder;

    protected:
        void timerEvent(QTimerEvent*);

    public slots:
        void transferSamples();
        void loadFile(QString fileName);
};

#endif // JACKPROCESSOR_H
