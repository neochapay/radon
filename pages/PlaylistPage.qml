import QtQuick 2.0
import QtQuick.Dialogs 1.1

import "PlayList/"

Rectangle {
    width: parent.width
    height: parent.height
    color: "transparent"
    clip: true

    ListModel {
        id: playListModel

        ListElement {
            artist: "Би-2"
            track: "Реки любви"
        }
        ListElement {
            artist: "Би-2"
            track: "16+"
        }

        ListElement {
            artist: "Би-2"
            track: "Полковнику ни кто не пишет"
        }
        ListElement {
            artist: "Запрещённые барабанщики"
            track: "Миллион долларов США"
        }
    }

    ListView{
        id: playListView
        model: playListModel
        width: parent.width
        height: parent.height
        y: 1
        delegate: PlayListItem{

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

