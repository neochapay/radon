import QtQuick 2.0

Rectangle {
    width: parent.width
    height: tarckLabel.height+6
    color: index % 2 == 0 ? "#c7c7c7":"#d8d8d8"

    Text{
        id: tarckLabel
        text: title
        x: 3
        y: 3
        anchors.margins: 3
    }
}

