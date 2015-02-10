import QtQuick 2.0
import "./NavigatorPanel"

Rectangle {
    id: navigationPanel
    width: parent.width
    height: 30
    color: "#3d3d3d"
    border.color: "black"
    border.width: 1

    function deactive()
    {
        playlistButton.state = "deactevated";
        libraryButton.state = "deactevated";
        calendarButton.state = "deactevated";
        informationButton.state = "deactevated";
        settingButton.state = "deactevated";
    }

    Component.onCompleted: {
        playlistButton.state = "actived"
    }


    NavigatorItem{
        id: playlistButton
        anchors.left: parent.left
        label: qsTr("Playlist")
        activate: false;
    }

    NavigatorItem{
        id: libraryButton
        anchors.left: playlistButton.right
        label: qsTr("Library")
        activate: false
    }

    NavigatorItem{
        id: calendarButton
        anchors.left: libraryButton.right
        label: qsTr("Calendar")
        activate: false;
    }

    NavigatorItem{
        id: informationButton
        anchors.left: calendarButton.right
        label: qsTr("Information")
        activate: false;
    }

    NavigatorItem{
        id: settingButton
        anchors.right: parent.right
        label: qsTr("Settings")
        activate: false;
    }
}

