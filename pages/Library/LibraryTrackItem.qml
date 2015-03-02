import QtQuick 2.0

Rectangle {
    width: parent.width
    height: tarckLabel.height+6
    color: index % 2 == 0 ? "#d8d8d8" : "#c7c7c7"

    Text{
        id: tarckLabel
        text: title
    }
}

