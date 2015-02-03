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
        JackProcessor(QJack::Client &client, QString chanel_name, bool have_in);
        ~JackProcessor();

        void setupMp3Decoder();
        void process(int samples);

        double attunation_l;
        double attunation_r;

        QJack::Client client;

        QJack::AudioPort out_l;
        QJack::AudioPort out_r;
        QJack::AudioPort in_l;
        QJack::AudioPort in_r;

        QJack::AudioRingBuffer ringBufferLeft;
        QJack::AudioRingBuffer ringBufferRight;

        QAudioDecoder *audioDecoder;
        void setVolume(double att_l,double att_r);
        QList<double> getVolume();

    protected:
        void timerEvent(QTimerEvent*);

    public slots:
        void transferSamples();
        void loadFile(QString fileName);
};

#endif // JACKPROCESSOR_H
