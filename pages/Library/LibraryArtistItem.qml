import QtQuick 2.0

Rectangle {
    property string title: "Unknow Artist"
    property int artist_id;

    width: parent.width
    height: label.height+6
    color: index % 2 == 0 ? "#d8d8d8" : "#c7c7c7"

    Text{
        id: label
        width: parent.width
        text: title
        x: 3
        y: 3
        anchors.margins: 3
        wrapMode: Text.WordWrap
        clip: true
    }
}

