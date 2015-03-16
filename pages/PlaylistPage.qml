import QtQuick 2.0
import QtQuick.Dialogs 1.1

import "PlayList/"

Rectangle {
    id: playList
    width: parent.width
    height: parent.height
    color: "transparent"
    clip: true

    ListModel {
        id: playListModel

        ListElement {
            trackId: 1
        }
        ListElement {
            trackId: 2
        }

        ListElement {
            trackId: 3
        }
        ListElement {
            trackId: 4
        }
    }

    ListView{
        id: playListView
        model: playList.getPlayList()
        width: parent.width
        height: parent.height
        y: 1
        delegate: PlayListItem{}
    }

    MessageDialog {
        property string dialogTitle
        property string dialogText

        id: messageDialog
        title: dialogTitle
        text: dialogText
        standardButtons: StandardButton.Yes | StandardButton.No
    }
}

