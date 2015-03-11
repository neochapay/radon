import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.0

import trackAdapter 1.0
import artistAdapter 1.0

Dialog{
    id: editTrackDialog
    property string trackTitle: "Unknow Track"
    property string trackArtist: "Unknow Artist"
    property string trackAlbum
    property string trackGenere
    property string trackComment
    property string filename
    property int trackYear
    property int trackNum
    property int track_id;

    function setTrackId(trackId)
    {
        editTrackDialog.track_id = trackId
        var trackB =  editTrack.toId(trackId)
        trackTitle = trackB.getTitle();
        trackAlbum = trackB.getAlbum();
        trackGenere = trackB.getGenere();
        trackYear = trackB.getYear();
        trackNum = trackB.getNumber();
        trackComment = trackB.getComment();

        var artistB = editArtist.toId(trackB.getArtistId());
        trackArtist = artistB.getName();
    }

    function saveTags()
    {
        var trackB =  editTrack.toId(editTrackDialog.track_id)
        trackB.setTitle(trackTitle);
        editTrackDialog.visible = false;
        trackSqlModel.refresh();
    }

    BTrack {
        id: editTrack
    }

    BArtist{
        id: editArtist
    }

    width: 400
    height: 300

    title: qsTr("Edit track")
    standardButtons: StandardButton.Save
    contentItem: Rectangle{
        color: "#aaaaaa"
        anchors.fill: parent

        Row{
            id: artistRow
            x: 5
            y: 5
            Text{
                id: artistLabel
                width: 100
                text: qsTr("Artist:")
            }

            Rectangle{
                id: artistInputArea
                radius: 3
                width: editTrackDialog.width-artistLabel.width-12
                height: artistInput.height
                clip: true
                TextInput{
                    id: artistInput
                    text: editTrackDialog.trackArtist
                    width: parent.width
                    maximumLength: 50
                }
            }
        }

        Row{
            id: titleRow
            x: 5
            y: 5
            anchors{
                topMargin: 5
                top: artistRow.bottom
            }
            Text{
                id: titleLabel
                width: 100
                text: qsTr("Title")
            }
            Rectangle{
                id: titleInputArea
                radius: 3
                width: editTrackDialog.width-titleLabel.width-12
                height: artistInput.height
                clip: true
                TextInput{
                    id: titleInput
                    text: editTrackDialog.trackTitle
                    width: parent.width
                    maximumLength: 50
                }
            }
        }

        Row{
            id: albumRow
            x: 5
            y: 5
            anchors{
                topMargin: 5
                top: titleRow.bottom
            }
            Text{
                id: albumLabel
                width: 100
                text: qsTr("Album")
            }
            Rectangle{
                id: albumInputArea
                radius: 3
                width: editTrackDialog.width-albumLabel.width-12
                height: albumInput.height
                clip: true
                TextInput{
                    id: albumInput
                    text: editTrackDialog.trackAlbum
                    width: parent.width
                    maximumLength: 50
                }
            }
        }

        Row{
            id: tarckYearRow
            x: 5
            y: 5
            anchors{
                topMargin: 5
                top: albumRow.bottom
            }
            Text{
                id: trackLabel
                width: 100
                text: qsTr("Track")
            }
            Rectangle{
                id: trackInputArea
                radius: 3
                width: editTrackDialog.width/2-trackLabel.width-12
                height: albumInput.height
                clip: true
                anchors.left: trackLabel.right
                TextInput{
                    id: trackInput
                    text: editTrackDialog.trackNum
                    width: parent.width
                    maximumLength: 2
                    inputMask: "90"
                }
            }
            Text{
                id: yearLabel
                width: 100
                text: qsTr("Year")
                anchors{
                    leftMargin: 6
                    left: trackInputArea.right
                }
            }
            Rectangle{
                id: yearInputArea
                radius: 3
                width: editTrackDialog.width/2-trackLabel.width-6
                height: albumInput.height
                clip: true
                anchors.left: yearLabel.right
                TextInput{
                    id: yearInput
                    text: editTrackDialog.trackYear
                    width: parent.width
                    maximumLength: 4
                    inputMask: "0000"
                }
            }
        }

        Button{
            id: saveButton
            text: qsTr("Save")

            onClicked: {
                editTrackDialog.trackArtist = artistInput.text
                editTrackDialog.trackTitle = titleInput.text
                editTrackDialog.saveTags();
            }

            anchors{
                bottom: parent.bottom
                right: parent.right
                margins: 5
            }
        }

    }

}
