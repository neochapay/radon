import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    property string title: "Unknow Artist"

    width: parent.width
    height: label.height+6
    color: index % 2 == 0 ? "#d8d8d8" : "#c7c7c7"

    Menu{
        id: contextMenu
        MenuItem
        {
            text: qsTr('Edit')
        }
        MenuItem
        {
            text: qsTr('Block artist')
        }
        MenuItem
        {
            text: qsTr('Delete')
        }
    }

    Text{
        id: label
        width: parent.width
        text: title
        x: 3
        y: 3
        anchors.margins: 3
        wrapMode: Text.WordWrap
        clip: true
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: contextMenu.popup()
        }
    }
}

