import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Rectangle {
    id: libraryPageArea
    width: parent.width
    height: parent.height
    color: "transparent"

    Button{
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
            console.log("Accepted: " + fileUrls)
            for (var i = 0; i < fileUrls.length; ++i)
            {
                Collection.addFile(fileUrls[i].replace("file://",""));
            }
        }
        onRejected: { console.log("Rejected") }
    }
}

