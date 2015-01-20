import QtQuick 2.0

Rectangle {
    width: 480
    height: parent.height
    color: "transparent"
    anchors{
        leftMargin: 10
        rightMargin: 10
    }
    property string currentTextLabel: qsTr("Linear Air")
    property int progress: 11

    Rectangle{
        id: currentRow
        width: parent.width
        height: 40
        color: "#3a3a3a"
        anchors{
            leftMargin: 5
            rightMargin: 5
        }
        y:35

        Text{
            id: currentLabel
            height: parent.height-5
            color: "white"
            verticalAlignment: Text.AlignVCenter
            anchors{
                margins: 5
                left: parent.left
            }
            text: currentTextLabel
            font.pixelSize: 18
        }

        Rectangle{
            id: progressbarWrapper
            width: parent.width
            height: 5
            anchors.bottom: parent.bottom
            color: "#141414"
            Rectangle{
                id: progressbar
                color: "#d40000"
                height: parent.height
                width: parent.width/100*progress
            }
        }
    }

}

