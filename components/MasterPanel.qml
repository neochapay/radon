import QtQuick 2.0
import "MasterPanel/"

Rectangle {
    id: masterPanel
    width: parent.width
    height: 100
    color: "#3d3d3d"
    gradient: Gradient {
        GradientStop {
            position: 0.0;
            color: "#5D5D5D";
        }
        GradientStop {
            position: 1.0;
            color: "#3D3D3D";
        }
    }
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

