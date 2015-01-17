import QtQuick 2.1
import QtQuick.Controls 1.0

import "components"

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    id: main
    title: qsTr("RadON")

    Item{
        id: content
        anchors.fill: parent
        MainContent{}
    }

    StatusBar{
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
