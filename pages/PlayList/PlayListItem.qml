import QtQuick 2.0
import QtQuick.Controls 1.0

import "../../js/FontAwesome.js" as FontAwesome

Rectangle {
    id: playListItem
    width: parent.width-2
    height: 40
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
            text: qsTr('Block artist')
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
        id: lisenButton
        text: FontAwesome.Icon.volume_up
        font.pointSize: 25
        x: 10
        MouseArea{
            id: lisenButtonArea
            anchors.fill: parent
            onClicked: {
                console.log("click lisen")
            }
        }
    }

    Text{
        id: playNowButton
        text: FontAwesome.Icon.play
        font.pointSize: 25
        color: "#FF5D1A"
        x: 10
        anchors{
            leftMargin: 10
            left: lisenButton.right
        }
        MouseArea{
            id: playNowButtonArea
            anchors.fill: parent
            onClicked: {
                console.log("click lisen")
            }
        }
    }

    Text{
        id: artistTitle
        text: artist
        font.pointSize: 12
        x: 100
        y: 10
    }

    Text{
        id: minus
        text: "-"
        anchors{
            left: artistTitle.right
            top: artistTitle.top
            leftMargin: 5
        }
    }

    Text{
        id: trackTitle
        text: track
        font.pointSize: 12
        anchors{
            left: minus.right
            top: artistTitle.top
            leftMargin: 5
        }
    }

    Text {
        id: menuButton
        text: FontAwesome.Icon.reorder
        anchors{
            right: parent.right
            bottom: parent.bottom
            rightMargin: 3
            bottomMargin: 3
        }
        MouseArea{
            id: menuButtonArea
            anchors.fill: parent
            onClicked: {
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

