#include "jackprocessor.h"
#include <jack/jack.h>

#include <QDebug>
#include <QAudioDecoder>

JackProcessor::JackProcessor(QJack::Client& client, QString chanel_name, bool have_in)
    :Processor(client)
{
    //regisrty out port
    out_l    = client.registerAudioOutPort("out_l_"+chanel_name.toUtf8());
    out_r    = client.registerAudioOutPort("out_r_"+chanel_name.toUtf8());

    //regisrty in port
    if(have_in)
    {
        in_l = client.registerAudioInPort("in_l_"+chanel_name.toUtf8());
        in_r = client.registerAudioInPort("in_r_"+chanel_name.toUtf8());
    }

    ringBufferLeft  = QJack::AudioRingBuffer(44100 * 1000);
    ringBufferRight = QJack::AudioRingBuffer(44100 * 1000);

    attunation_l = 1.0;
    attunation_r = 1.0;

    client.activate();

/*    client.connect(client.portByName("system:capture_1"),dj_in_l);
    client.connect(client.portByName("system:capture_2"),dj_in_r);

    client.connect(dj_out_l,client.portByName("system:playback_1"));
    client.connect(dj_out_r,client.portByName("system:playback_2"));
    client.connect(stream_out_l,client.portByName("system:playback_3"));
    client.connect(stream_out_r,client.portByName("system:playback_4"));*/

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
   out_l.buffer(samples).pop(ringBufferLeft);
   out_r.buffer(samples).pop(ringBufferRight);
   out_l.buffer(samples).multiply(attunation_l);
   out_l.buffer(samples).multiply(attunation_r);
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

