#include "jackprocessor.h"
#include <jack/jack.h>

#include <QDebug>
#include <QAudioDecoder>

JackProcessor::JackProcessor(QJack::Client& client)
    :Processor(client)
{
    //volume

    attunation_l = 1.0;
    attunation_r = 1.0;

    //regisrty out ports
    stream_out_l    = client.registerAudioOutPort("stream_out_l");
    stream_out_r    = client.registerAudioOutPort("stream_out_r");

    //regisrty in ports
    stream_in_l = client.registerAudioInPort("stream_in_l");
    stream_in_r = client.registerAudioInPort("stream_in_r");


    streamRingBufferLeft  = QJack::AudioRingBuffer(44100 * 1000);
    streamRingBufferRight = QJack::AudioRingBuffer(44100 * 1000);

    audioDecoder = new QAudioDecoder();
    QObject::connect(audioDecoder, SIGNAL(bufferReady()), this, SLOT(transferSamples()));
}

void JackProcessor::setupMp3Decoder()
{
    QAudioFormat targetAudioFormat;
    targetAudioFormat.setSampleType(QAudioFormat::SignedInt);
    targetAudioFormat.setChannelCount(2);
    targetAudioFormat.setCodec("audio/x-raw");
    audioDecoder->setAudioFormat(targetAudioFormat);
}

void JackProcessor::loadFile(QString fileName)
{
    audioDecoder->setSourceFilename(fileName);
    audioDecoder->start();
}

void JackProcessor::transferSamples()
{
    QAudioBuffer audioBuffer = audioDecoder->read();
    int frames = audioBuffer.frameCount();

    samples += frames;

    if(audioBuffer.isValid())
    {
        QJack::AudioSample left[frames];
        QJack::AudioSample right[frames];

        const QAudioBuffer::S16S *stereoBuffer = audioBuffer.constData<QAudioBuffer::S16S>();
        for (int i = 0; i < frames; i++)
        {
            left[i]     = (QJack::AudioSample)(stereoBuffer[i].left / 65536.0);
            right[i]    = (QJack::AudioSample)(stereoBuffer[i].right / 65536.0);
        }
        streamRingBufferLeft.write(left, frames);
        streamRingBufferRight.write(right, frames);
    }
}


void JackProcessor::timerEvent(QTimerEvent*)
{

}

void JackProcessor::process(int samples)
{
   stream_out_l.buffer(samples).pop(streamRingBufferLeft);
   stream_out_r.buffer(samples).pop(streamRingBufferRight);
   stream_out_l.buffer(samples).multiply(attunation_l);
   stream_out_r.buffer(samples).multiply(attunation_r);
}

void JackProcessor::setVolume(double att_l, double att_r)
{
    attunation_l = att_l;
    attunation_r = att_r;
}

QList<double> JackProcessor::getVolume()
{
    QList<double> out;
    out.append(attunation_l);
    out.append(attunation_r);
    return out;
}

JackProcessor::~JackProcessor()
{

}

