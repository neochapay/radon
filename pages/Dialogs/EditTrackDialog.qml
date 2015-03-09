import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.0

Dialog{
    property string trackTitle: "Unknow Track"
    property string trackArtist: "Unknow Artist"
    property string trackAlbum
    property string trackGenere
    property string filename
    property int trackYear
    property int trackNum

    function setTrackId(track_id)
    {
        console.log(track_id)
    }

    signal saveTags()

    id: editTrackDialog
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
