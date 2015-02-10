import QtQuick 2.1
import QtQuick.Controls 1.0

import "components"
import "js/FontAwesome.js" as FontAwesome

ApplicationWindow {
    id: main
    visible: true
    visibility: "Maximized"
    title: qsTr("RadON")

    FontLoader{
        source: "fonts/fontawesome-webfont.ttf"
    }

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
