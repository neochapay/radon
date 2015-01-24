import QtQuick 2.0
import "./NavigatorPanel"

Rectangle {
    id: navigationPanel
    width: parent.width
    height: 30
    color: "#3d3d3d"
    border.color: "black"
    border.width: 1

    function activateButton(id)
    {
        NavigatorItem.disable()
    }

    NavigatorItem{
        id: playlistButton
        anchors.left: parent.left
        label: qsTr("Playlist")
    }

    NavigatorItem{
        id: libraryButton
        anchors.left: playlistButton.right
        label: qsTr("Library")
    }

    NavigatorItem{
        id: calendarButton
        anchors.left: libraryButton.right
        label: qsTr("Calendar")
    }

    NavigatorItem{
        id: informationButton
        anchors.left: calendarButton.right
        label: qsTr("Information")
    }

    NavigatorItem{
        id: settingButton
        anchors.right: parent.right
        label: qsTr("Settings")
    }
}

