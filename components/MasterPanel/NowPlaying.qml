import QtQuick 2.0

Rectangle {
    width: 480
    height: parent.height
    color: "transparent"
    anchors{
        leftMargin: 10
        rightMargin: 5
    }

    Rectangle{
        id: prevRow
        width: parent.width
        height: 30
        color: "transparent"
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
            text: main.prevTextLabel
            color: "#dfdfdf"
            anchors.left: prevLabel.right
        }
        Text{
            id: prevTime
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            color: "#969696"
            anchors.right: parent.right
            text: main.prevTimeLabel
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
            text: main.currentTextLabel
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
                width: parent.width/100*main.progress
            }
        }
    }

    Rectangle{
        id: nextRow
        width: parent.width
        height: 30
        color: "transparent"
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
            text: main.nextTextLabel
            color: "#dfdfdf"
            anchors.left: nextLabel.right
        }
        Text{
            id: nextTime
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            color: "#969696"
            anchors.right: parent.right
            text: main.nextTimeLabel
        }
    }
}

