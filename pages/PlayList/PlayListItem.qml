import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    id: playListItem
    width: parent.width-2
    height: 62
    x: 1
    y: 1
    color: index % 2 == 0 ? "#d8d8d8" : "#c7c7c7"

    Menu{
        id: contextMenu
        MenuItem
        {
            text: qsTr('Edit tags')
        }
        MenuItem
        {
            text: qsTr('Delete')
        }
    }

    Text{
        text: artist
    }

    MouseArea {
        id: menuArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
             if (mouse.button == Qt.RightButton)
             {
                contextMenu.popup()
             }
        }
    }

    Rectangle{
        width: parent.width
        height: 1
        color: "#5b5b5b"
        anchors.bottom: parent.bottom
    }
}

