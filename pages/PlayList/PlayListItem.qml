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
            onTriggered: {
                editTrackDialog.setTrackId(trackId);
                editTrackDialog.visible = true;
            }
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
            id: effectMenuItem
            text: qsTr('Show effect bar')
            onTriggered: {
                if(jingleArea.visible == true)
                {
                    jingleArea.visible = false
                    effectMenuItem.text = "Show effect bar"
                    playListItem.height = lisenButton.height
                }
                else
                {
                    jingleArea.visible = true
                    effectMenuItem.text = "Hide effect bar"
                    playListItem.height = lisenButton.height+20
                }
            }
        }
        MenuItem
        {
            text: qsTr('Remove from playlist')
            onTriggered: {
                playListModel.remove(index);
            }
        }
    }

    Text{
        id: lisenButton
        text: FontAwesome.Icon.volume_up
        font.family: "FontAwesome"
        font.pointSize: 25
        x: 10
        anchors.verticalCenter: parent.verticalCenter
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
            verticalCenter: parent.verticalCenter
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
        x: 90
        y: 7
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
            verticalCenter: playNowButton.verticalCenter
            rightMargin: 10
        }
    }

    MouseArea{
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: contextMenu.popup()
    }

    Rectangle{
        id: jingleArea
        color: "#86BDFA"
        width: parent.width-artistTitle.x-trackTimeText.width-20
        height: 20
        radius: 3
        visible: false
        anchors{
            left: artistTitle.left
            top: artistTitle.bottom
            topMargin: 2
        }

        Rectangle {
            id: jingleBtn
            width: 20;
            height: 20
            radius: 2
            smooth: true
            color:"#99FF5D1A"
            border.width: 1

            MouseArea {
                anchors.fill: parent
                drag.target: parent
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: jingleArea.width-20
                onPositionChanged: {
                    //value = ((soundslider.height-this.parent.y)/soundslider.height)*120
                    //console.log(value)
                }
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

