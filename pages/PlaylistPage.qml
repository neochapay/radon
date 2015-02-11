import QtQuick 2.0
import "PlayList/"

Rectangle {
    width: parent.width
    height: parent.height
    color: "transparent"

    ListModel {
        id: playListModel

        ListElement {
            artist: "Би-2"
            title: "Реки любви"
        }
        ListElement {
            artist: "Би-2"
            title: "16+"
        }

        ListElement {
            artist: "Би-2"
            title: "Полковнику ни кто не пишет"
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
}

