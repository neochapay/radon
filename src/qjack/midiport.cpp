///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//    This file is part of QJack.                                            //
//    Copyright (C) 2014-2015 Jacob Dawid <jacob@omg-it.works>               //
//                                                                           //
//    QJack is free software: you can redistribute it and/or modify          //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    QJack is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with QJack. If not, see <http://www.gnu.org/licenses/>.          //
//                                                                           //
//    It is possible to obtain a closed-source license of QJack.             //
//    If you're interested, contact me at: jacob@omg-it.works                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// Own includes
#include "midiport.h"

namespace QJack {

MidiPort::MidiPort()
    : Port() {
}

MidiPort::MidiPort(const Port& other)
    : Port(other) {
    if(!other.isMidiPort()) {
        // Invalidate.
        _jackPort = 0;
    }
}

MidiPort::MidiPort(const MidiPort& other)
    : Port(other) {
}

MidiPort::MidiPort(jack_port_t *jackPort)
    : Port(jackPort) {
}

MidiBuffer MidiPort::buffer(int samples) const {
    if(isValid()) {
        return MidiBuffer(samples, jack_port_get_buffer(_jackPort, samples));
    }
    return MidiBuffer(samples, 0);
}

}
