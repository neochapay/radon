import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    width: parent.width
    height: tarckLabel.height+6
    color: index % 2 == 0 ? "#c7c7c7":"#d8d8d8"

    Menu{
        id: contextMenu

        MenuItem
        {
            text: qsTr('Add next')
        }
        MenuItem
        {
            text: qsTr('Add to end of playlist')
        }
        MenuItem
        {
            text: qsTr('Edit tag')
            onTriggered: {
                editTrackDialog.setTrackId(track_id);
                editTrackDialog.visible = true;
            }
        }
        MenuItem
        {
            text: qsTr('Block track')
        }
        MenuItem
        {
            text: qsTr('Delete')
        }
    }

    Text{
        id: tarckLabel
        text: artist_name+" - "+title
        x: 3
        y: 3
        anchors.margins: 3
    }

    MouseArea{
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: contextMenu.popup()
    }
}

