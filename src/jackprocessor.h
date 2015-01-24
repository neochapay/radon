#ifndef JACKPROCESSOR_H
#define JACKPROCESSOR_H

#include "qjack/processor.h"
#include "qjack/client.h"
#include "qjack/buffer.h"

class JackProcessor : public QJack::Processor
{
    public:
        JackProcessor(QJack::Client &client);
        ~JackProcessor();
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
};

#endif // JACKPROCESSOR_H
