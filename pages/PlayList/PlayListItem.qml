import QtQuick 2.0
import QtQuick.Controls 1.0

import trackAdapter 1.0
import artistAdapter 1.0

import "../../js/FontAwesome.js" as FontAwesome

Rectangle {
    id: playListItem
    width: parent.width-2
    height: lisenButton.height
    x: 1
    y: 1

    property int artist_id;
    property var track;
    property var artist;

    BTrack {
        id: thisTrack
    }

    BArtist{
        id: thisArtist
    }

    Component.onCompleted:
    {
        track = thisTrack.toId(trackId)
        artist_id = track.getArtistId();
        artist = thisArtist.toId(artist_id);

        if(trackType == "track")
        {
            playListItem.color = index % 2 == 0 ? "#d8d8d8" : "#c7c7c7"
        }
        if(trackType == "advertising")
        {
            playListItem.color = index % 2 == 0 ? "#ff5d1a" : "#e55317"
        }
        if(trackType == "livecast")
        {
            playListItem.color = index % 2 == 0 ? "#95d5f7" : "#86bfde"
        }
    }

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
        font.family: "FontAwesome"
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
        text: playEd ? FontAwesome.Icon.stop : FontAwesome.Icon.play
        font.family: "FontAwesome"
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
                playListView.currentIndex = index;
            }
        }
    }

    Text{
        id: artistTitle
        text: artist.getName()
        font.pointSize: 12
        x: 100
        anchors.verticalCenter: lisenButton.verticalCenter
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
        text: track.getTitle()
        font.pointSize: 12
        anchors{
            left: minus.right
            top: artistTitle.top
            leftMargin: 5
        }
    }

    Text{
        id: trackTimeText
        text: Qt.formatTime(new Date(track.getLength()*1000),"mm:ss")
        font.pointSize: 12
        anchors{
            right:  parent.right
            top: artistTitle.top
            rightMargin: 10
        }
    }

    MouseArea{
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: contextMenu.popup()
    }

    Rectangle{
        width: parent.width
        height: 1
        color: "#5b5b5b"
        anchors.bottom: parent.bottom
    }
}

