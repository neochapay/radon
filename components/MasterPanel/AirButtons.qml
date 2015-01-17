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
        x: 10
        y: 10
        state: "off"
        Text{
            id: airStatusLabel
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
            onClicked: {
                if(airStatus.state == "off")
                {
                    airStatus.state = "on"
                }
                else
                {
                    airStatus.state = "off"
                    liveStatus.state = "off"
                }
            }
        }
        StateGroup{
            states: [
                State{
                    name: "on";
                    PropertyChanges {
                        target: airStatus
                        color: "#3f3a3a"
                    }
                    PropertyChanges {
                        target: airStatusLabel
                        text: "ON AIR"
                    }
                },
                State{
                    name: "off";
                    PropertyChanges {
                        target: airStatus
                        color: "#c21717"
                    }
                    PropertyChanges {
                        target: airStatusLabel
                        text: "OFF AIR"
                    }
                    PropertyChanges {
                        target: liveStatus
                        state: "off"
                    }
                }

            ]
        }
    }

    Rectangle{
        id: liveStatus
        width: 100
        height: 20
        color: "#6e6e6e"
        x: 10
        state: "off"
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
            onClicked: liveStatus.state
        }
        StateGroup{
            states: [
                State{
                    name: "off"
                    PropertyChanges {
                        target: liveStatus
                        color: "#6e6e6e"
                    }
                },
                State{
                    name: "on"
                    PropertyChanges {
                        target: liveStatus
                        color: "#5caa15"
                    }
                }
            ]
        }
    }
}

