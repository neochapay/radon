import QtQuick 2.0

Rectangle {
    id: airButtons
    width: 120
    height: parent.height
    color: "transparent"
    anchors{
        margins: 10
    }

    signal onAir()
    signal offAir()
    signal onLine()
    signal offLine()

    Rectangle{
        id: airStatus
        width: 100
        height: 60
        color: "#3f3a3a"
        x: 10
        y: 10
        state: "offair"
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
                if(airStatus.state == "offair")
                {
                    airStatus.state = "onair";
                    airButtons.onAir();
                }
                else
                {
                    airStatus.state = "offair"
                    airButtons.offAir();
                }
            }
        }
        states: [
            State{
                name: "offair";
                PropertyChanges {target: airStatus; color: "#3f3a3a"}
                PropertyChanges {target: airStatusLabel; text: "OFF AIR"}
            },
            State{
                name: "onair";
                PropertyChanges {target: airStatus; color: "#c21717"}
                PropertyChanges {target: airStatusLabel; text: "ON AIR"}
                PropertyChanges {target: liveStatus; state: "off"}
            }
        ]
    }

    Rectangle{
        id: liveStatus
        width: 100
        height: 20
        color: "#6e6e6e"
        x: 10
        state: "offlive"
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
            onClicked: {
                if(airStatus.state == "onair")
                {
                    if(liveStatus.state != "onlive")
                    {
                        liveStatus.state = "onlive"
                        airButtons.onLine();
                    }
                    else
                    {
                        liveStatus.state = "offlive"
                        airButtons.offLive();
                    }
                }
                else
                {
                    liveStatus.state = "offlive"
                }
            }
        }
         states: [
             State{
                 name: "offlive"
                 PropertyChanges {target: liveStatus; color: "#6e6e6e"}
             },
             State{
                 name: "onlive"
                 PropertyChanges {target: liveStatus; color: "#5caa15"}
             }
         ]
    }
}

