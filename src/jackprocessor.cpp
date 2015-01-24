#include "jackprocessor.h"
#include <jack/jack.h>

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
}

JackProcessor::~JackProcessor()
{

}

