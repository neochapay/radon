import QtQuick 2.1
import QtQuick.Controls 1.0

import "components"

ApplicationWindow {
    id: main
    visible: true
    visibility: "Maximized"
    title: qsTr("RadON")

    Item{
        id: content
        anchors.fill: parent
        MainContent{
            width: parent.width
            height: parent.height-statusBar.height
        }
    }

    StatusBar{
        id: statusBar
        anchors.bottom: content.bottom
        Image{
            id: statusImage
            height: parent.height
            width: parent.height
            anchors{
                rightMargin: 5
                left: parent.left
            }

        }
        Text{
            id: statusText
            anchors{
                fill: parent
                right: statusImage.left
            }
        }
    }
}
