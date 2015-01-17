import QtQuick 2.0

Rectangle {
    width: 480
    height: parent.height
    color: "#3d3d3d"
    anchors{
        leftMargin: 10
        rightMargin: 5
    }

    property string prevTextLabel: "Unknow Artist - Unknow Song"
    property string prevTimeLabel: "00:00:00"

    property int progress: 34
    property string currentTextLabel: "Unknow Artist - Unknow Song"

    property string nextTextLabel: "Unknow Artist - Unknow Song"
    property string nextTimeLabel: "00:00:00"

    Rectangle{
        id: prevRow
        width: parent.width
        height: 30
        color: "#3d3d3d"
        Text{
            id: prevLabel
            text: qsTr("Previews:")
            color: "#969696"
            height: parent.height
            width: 100
            verticalAlignment: Text.AlignVCenter
            anchors.left: prevRow.left
        }
        Text{
            id: prevText
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            text: prevTextLabel
            color: "#dfdfdf"
            anchors.left: prevLabel.right
        }
        Text{
            id: prevTime
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            color: "#969696"
            anchors.right: parent.right
            text: prevTimeLabel
        }
    }

    Rectangle{
        id: currentRow
        width: parent.width
        height: 40
        color: "#3a3a3a"
        anchors{
            top: prevRow.bottom
            margins: 5
        }

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
                color: "#f97202"
                height: parent.height
                width: parent.width/100*progress
            }
        }
    }

    Rectangle{
        id: nextRow
        width: parent.width
        height: 30
        color: "#3d3d3d"
        anchors.top: currentRow.bottom
        Text{
            id: nextLabel
            text: qsTr("Next:")
            color: "#969696"
            height: parent.height
            width: 100
            verticalAlignment: Text.AlignVCenter
            anchors.left: nextRow.left
        }
        Text{
            id: nextText
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            text: nextTextLabel
            color: "#dfdfdf"
            anchors.left: nextLabel.right
        }
        Text{
            id: nextTime
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            color: "#969696"
            anchors.right: parent.right
            text: nextTimeLabel
        }
    }
}

