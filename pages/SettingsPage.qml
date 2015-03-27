import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Rectangle {
    id: settingsPageArea
    width: parent.width
    height: parent.height
    color: "transparent"

    Rectangle{
        width: childrenRect.width+6
        height: childrenRect.height
        z: 9
        x: 20
        y: 4
        color: "#aaaaaa"

        Text{
            text: qsTr("Main settings")
            x: 3
        }
    }

    Rectangle{
        id: mainSettings
        width: parent.width-20
        height: parent.height-20
        border.color: "#5b5b5b"
        color: "transparent"
        x: 10
        y: 10
        z:8

        Button{
            text: qsTr("Save settings")
            anchors{
                bottom: mainSettings.bottom
                right: mainSettings.right
                bottomMargin: 5
                rightMargin: 5
            }

            onClicked:{
                Settings.sync();
            }
        }
    }
}

