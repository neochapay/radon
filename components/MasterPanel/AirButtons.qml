import QtQuick 2.0

Rectangle {
    width: 120
    height: parent.height
    color: "#3d3d3d"
    anchors{
        margins: 10
    }

    Rectangle{
        id: airStatus
        width: 100
        height: 60
        color: "#3f3a3a"
//      color: "#c21717"
        x: 10
        y: 10
        Text{
            text: "OFF AIR"
            color: "white"
            font.bold: true
            font.pixelSize: 18
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        MouseArea{
            anchors.fill: parent;
        }
    }

    Rectangle{
        id: liveStatus
        width: 100
        height: 20
        color: "#6e6e6e"
//#5caa15
        x: 10
        anchors.top: airStatus.bottom
        Text{
            text: "LIVE"
            color: "white"
            font.bold: true
            font.pixelSize: 12
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        MouseArea{
            anchors.fill: parent;
        }
    }
}

