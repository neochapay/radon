import QtQuick 2.0
import "MasterPanel/"

Rectangle {
    id: masterPanel
    width: parent.width
    height: 100
    color: "#3d3d3d"
    NowPlaying{
        id: nowPlaying
        anchors.left: masterPanel.left
    }
    CurrentShow{
        anchors.left: nowPlaying.right
    }
    AirButtons{
        anchors.right: masterPanel.right
    }
}

