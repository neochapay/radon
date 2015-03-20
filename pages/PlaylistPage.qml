import QtQuick 2.0
import QtQuick.Dialogs 1.1

import "PlayList/"

Rectangle {
    id: playList
    width: parent.width
    height: parent.height
    color: "transparent"
    clip: true

    ListView{
        id: playListView
        model: playListModel
        width: parent.width
        height: parent.height
        y: 1
        delegate: PlayListItem{}
        onCurrentItemChanged: {

        }
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

