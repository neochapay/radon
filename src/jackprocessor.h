#ifndef JACKPROCESSOR_H
#define JACKPROCESSOR_H

#include "qjack/processor.h"
#include "qjack/client.h"
#include "qjack/buffer.h"

#include <QAudioDecoder>
#include <QObject>

class JackProcessor : public QJack::Processor
{
     Q_OBJECT

    public:
        JackProcessor(QJack::Client &client);
        ~JackProcessor();

        void setupMp3Decoder();
        void process(int samples);

        int samples;

        double attunation_l;
        double attunation_r;

        QJack::Client client;

        QJack::AudioPort stream_out_l;
        QJack::AudioPort stream_out_r;
        QJack::AudioPort dj_out_l;
        QJack::AudioPort dj_out_r;
        QJack::AudioPort stream_in_l;
        QJack::AudioPort stream_in_r;
        QJack::AudioPort dj_in_l;
        QJack::AudioPort dj_in_r;

        QJack::AudioRingBuffer streamRingBufferLeft;
        QJack::AudioRingBuffer streamRingBufferRight;
        QJack::AudioRingBuffer djRingBufferLeft;
        QJack::AudioRingBuffer djRingBufferRight;

        QAudioDecoder *audioDecoder;

        Q_INVOKABLE QList<double> getVolume();

    protected:
        void timerEvent(QTimerEvent*);

    public slots:
        void transferSamples();
        void loadFile(QString fileName);
        Q_INVOKABLE void setVolume(double att_l,double att_r);
};

#endif // JACKPROCESSOR_H
