import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.0

import artistAdapter 1.0

Dialog{
    id: editArtistDialog
    property string artistName;
    property int artist_id;

    function setArtistID(artistId)
    {
        editArtistDialog.artist_id = artistId

        var artistB = editArtist.toId(artistId);
        editArtistDialog.artistName = artistB.getName();
    }


    BArtist{
        id: editArtist
    }

    width: 400
    height: 60

    title: qsTr("Edit Artist")
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
                width: editArtistDialog.width-artistLabel.width-12
                height: artistInput.height
                clip: true
                TextInput{
                    id: artistInput
                    text: editArtistDialog.artistName
                    width: parent.width
                    maximumLength: 50
                }
            }
        }

        Button{
            id: saveButton
            text: qsTr("Save")

            onClicked: {
                var artistB = editArtist.toId(editArtistDialog.artist_id);
                artistName = artistB.setName(editArtistDialog.artistName)
                artistB.update();
                artistSqlModel.refresh()
                trackSqlModel.refresh()
                editArtistDialog.visible = false;
            }

            anchors{
                bottom: parent.bottom
                right: parent.right
                margins: 5
            }
        }
    }
}
