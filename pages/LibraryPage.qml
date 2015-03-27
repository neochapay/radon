import QtQuick 2.2
import QtQuick.Controls 1.2

import "Library"

TabView{
    anchors.fill: parent;
    clip: true;
    Tab{
        title: "Music Collection"
        anchors.fill: parent;
        TracksTab{
            id: tracksTabArea
        }
    }
    Tab{
        title: "Jingles"
    }
    Tab{
        title: "Advertising"
    }
    Tab{
        title: "Live air records"
    }
}
