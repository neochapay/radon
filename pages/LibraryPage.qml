import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

import "../js/FontAwesome.js" as FontAwesome

Rectangle {
    id: libraryPageArea
    objectName: "libraryPageArea"
    width: parent.width
    height: parent.height
    color: "transparent"

    signal addFiles(variant list)

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
        onClicked: Collection.rescanBase()
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

