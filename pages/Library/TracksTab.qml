import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

import "../../js/FontAwesome.js" as FontAwesome

Rectangle {
    id: libraryPageArea
    objectName: "libraryPageArea"
    color: "transparent"
    clip: true

    Rectangle{
        id: artistArea
        width: 200
        height: parent.height-addFileButton.height-15
        x: 1
        y: 1
        clip: true
        color: "transparent"

        TextField{
            id: searchArtist
            x: 5
            y: 5
            width: parent.width-10
            focus: true
            onTextChanged: {
                if(text.length > 0)
                {
                    artistSqlModel.searchQuery(text);
                }
                else
                {
                    artistSqlModel.cleanQuery();
                }
                artistSqlModel.refresh();
            }
        }

        Rectangle{
            width: parent.width
            height: artistArea.height-searchArtist.height-10
            clip: true
            anchors{
                topMargin: 5
                top: searchArtist.bottom
            }
            color: "transparent"
            ListView{
                id: artisListView
                width: parent.width
                height: parent.height
                y: 1
                model: artistSqlModel
                delegate: LibraryArtistItem {
                }
            }
        }
    }

    Rectangle{
        id: songArea
        width: parent.width-artistArea.width-2
        height: parent.height-addFileButton.height-15
        anchors.left: artistArea.right
        y:1
        clip: true
        color: "transparent"
        ListView{
            id: trackListView
            width: parent.width
            height: parent.height
            y: 1
            model: trackSqlModel
            delegate: LibraryTrackItem{
            }
        }
    }

    Button{
        width: height
        anchors{
            right: addFileButton.left
            bottom: libraryPageArea.bottom
            bottomMargin: 5
            rightMargin: 5
        }
        Text{
            anchors.fill: parent
            text: FontAwesome.Icon.refresh
            font.family: "FontAwesome"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        onClicked:{
            Collection.rescanBase()
            trackSqlModel.refresh()
            artistSqlModel.refresh()
        }
    }

    Button{
        id: addFileButton
        text: "Add files to library"
        onClicked: fileDialog.visible = true;
        anchors{
            bottom: libraryPageArea.bottom
            right: libraryPageArea.right
            bottomMargin: 5
            rightMargin: 5
        }
    }

    FileDialog {
        id: fileDialog
        nameFilters: ["Audio Files (*.mp3)"]
        selectedNameFilter: "All files (*)"
        selectMultiple: true
        onAccepted: {
            var list = []
            for (var i = 0; i < fileUrls.length; ++i)
            {
                list.push(fileUrls[i].replace("file://",""))
            }
            Collection.addFiles(list)
            trackSqlModel.refresh()
            artistSqlModel.refresh()
        }
        onRejected: { console.log("Rejected") }
    }
}
