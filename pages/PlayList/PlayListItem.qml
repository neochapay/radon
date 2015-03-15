import QtQuick 2.0
import QtQuick.Controls 1.0

import trackAdapter 1.0
import artistAdapter 1.0

import "../../js/FontAwesome.js" as FontAwesome

Rectangle {
    id: playListItem
    width: parent.width-2
    height: 40
    x: 1
    y: 1
    color: index % 2 == 0 ? "#d8d8d8" : "#c7c7c7"

    property int track_id;
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
        track_id = trackId;
        track = thisTrack.toId(track_id)
        artist_id = track.getArtistId();
        artist = thisArtist.toId(artist_id);
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
        text: FontAwesome.Icon.play
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
                console.log("click lisen")
            }
        }
    }

    Text{
        id: artistTitle
        text: artist.getName()
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
        text: track.getTitle()
        font.pointSize: 12
        anchors{
            left: minus.right
            top: artistTitle.top
            leftMargin: 5
        }
    }

    Text {
        id: blockArtistButton
        text: FontAwesome.Icon.user_times
        anchors{
            right: parent.right
            bottom: parent.bottom
            rightMargin: 3
            bottomMargin: 3
        }
    }

    PlayListItemIcon {
        id: blockTrackButton
        text: FontAwesome.Icon.times
        font.family: "FontAwesome"
        anchors.right: blockArtistButton.left
        onButtonClicked: {
            messageDialog.dialogTitle = "TITLE"
            messageDialog.visible = true;
        }
    }


    PlayListItemIcon {
        id: editTrackButton
        text: FontAwesome.Icon.pencil_square_o
        font.family: "FontAwesome"
        anchors.right: blockTrackButton.left
    }

    PlayListItemIcon {
        id: removeFromPlayListButton
        text: FontAwesome.Icon.minus_square
        font.family: "FontAwesome"
        anchors.right: editTrackButton.left
    }

    Rectangle{
        width: parent.width
        height: 1
        color: "#5b5b5b"
        anchors.bottom: parent.bottom
    }
}

