import QtQuick 2.0
import "MasterPanel/"

Rectangle {
    id: masterPanel
    width: parent.width
    height: 100
    color: "#3d3d3d"
    NowPlaying{
        anchors.left: masterPanel.left
    }
}

