#include "jackprocessor.h"
#include <jack/jack.h>

#include <QDebug>
#include <QAudioDecoder>

JackProcessor::JackProcessor(QJack::Client& client)
    :Processor(client)
{
    //regisrty out port
    stream_out_l    = client.registerAudioOutPort("stream_l");
    stream_out_r    = client.registerAudioOutPort("stream_r");
    dj_out_l        = client.registerAudioOutPort("dj_out_l");
    dj_out_r        = client.registerAudioOutPort("dj_out_r");
    alarm_l         = client.registerAudioOutPort("alarm_r");
    alarm_r         = client.registerAudioOutPort("alarm_l");

    //regisrty in port
    dj_in_l         = client.registerAudioInPort("dj_in_l");
    dj_in_r         = client.registerAudioInPort("dj_in_r");
    aux_in_l        = client.registerAudioInPort("aux_l");
    aux_in_r        = client.registerAudioInPort("aux_r");

    ringBufferLeft  = QJack::AudioRingBuffer(44100 * 1000);
    ringBufferRight = QJack::AudioRingBuffer(44100 * 1000);

    client.activate();

    client.connect(client.portByName("system:capture_1"),dj_in_l);
    client.connect(client.portByName("system:capture_2"),dj_in_r);

    client.connect(dj_out_l,client.portByName("system:playback_1"));
    client.connect(dj_out_r,client.portByName("system:playback_2"));
    client.connect(stream_out_l,client.portByName("system:playback_3"));
    client.connect(stream_out_r,client.portByName("system:playback_4"));

    audioDecoder = new QAudioDecoder();
}

void JackProcessor::setupMp3Decoder() {
    QAudioFormat targetAudioFormat;
    targetAudioFormat.setSampleRate(client.sampleRate());
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

void JackProcessor::transferSamples() {
    QAudioBuffer audioBuffer = audioDecoder->read();
    if(audioBuffer.isValid())
    {
        int frames = audioBuffer.frameCount();
        QJack::AudioSample left[frames];
        QJack::AudioSample right[frames];


        const QAudioBuffer::S16S *stereoBuffer = audioBuffer.constData<QAudioBuffer::S16S>();
        for (int i = 0; i < frames; i++)
        {
            left[i]     = (QJack::AudioSample)(stereoBuffer[i].left / 65536.0);
            right[i]    = (QJack::AudioSample)(stereoBuffer[i].right / 65536.0);
        }

        ringBufferLeft.write(left, frames);
        ringBufferRight.write(right, frames);
    }
}


void JackProcessor::timerEvent(QTimerEvent*) {
    qDebug() << "Samples remaining in the ring buffer: "
             << ringBufferLeft.numberOfElementsAvailableForRead()
             << " / "
             << ringBufferRight.numberOfElementsAvailableForRead();
}

void JackProcessor::process(int samples) {
    // Just shift samples from the ringbuffers to the outputs buffers.
    dj_out_l.buffer(samples).pop(ringBufferLeft);
    dj_out_r.buffer(samples).pop(ringBufferRight);
}

JackProcessor::~JackProcessor()
{

}

