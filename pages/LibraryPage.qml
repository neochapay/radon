import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

import "../js/FontAwesome.js" as FontAwesome
import "Library"

Rectangle {
    id: libraryPageArea
    objectName: "libraryPageArea"
    width: parent.width
    height: parent.height
    color: "transparent"
    clip: true

    signal addFiles(variant list)

    Rectangle{
        id: artistArea
        width: 200
        height: parent.height-addFileButton.height-15
        x: 1
        y: 1
        clip: true
        color: "transparent"

        Rectangle{
            id: searchArtistArea
            anchors.margins: 3
            radius: 3
            x:2
            y:2
            width: parent.width-4
            height: searchArtist.height
            color: "white"

            TextInput{
                id: searchArtist
                focus: true
                selectByMouse: true
                autoScroll: true
                wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere;
                color: "black";
                onTextChanged: {
                    if(text.length > 0)
                    {
                        artistModel.searchQuery(text);
                    }
                    else
                    {
                        artistModel.cleanQuery();
                    }
                    artistModel.refresh();
                }
            }

        }
        Rectangle{
            width: parent.width
            height: artistArea.height-searchArtistArea.height
            clip: true
            anchors.top: searchArtistArea.bottom
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
            addFiles(list)
        }
        onRejected: { console.log("Rejected") }
    }
}

