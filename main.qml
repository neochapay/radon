import QtQuick 2.1
import QtQuick.Controls 1.0

import "components"

ApplicationWindow {
    id: main
    visible: true
    visibility: "Maximized"
    title: qsTr("RadON")
    minimumHeight: 600
    minimumWidth: 1100

    FontLoader{
        source: "fonts/fontawesome-webfont.ttf"
    }

    Item{
        id: content
        anchors.fill: parent
        MainContent{
            id: mainContent
            width: parent.width
            height: parent.height-statusBar.height
        }
    }

    StatusBar{
        id: statusBar
        objectName: "statusBar"
        anchors.bottom: content.bottom

        function setStatus(status)
        {
            statusText.text = status;
            textTimer.restart();
        }

        function setProcess(val)
        {
            statusProgres.value = val;
            statusProgres.visible = true;
        }

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
            width: parent-statusProgres.width
            anchors{
                fill: parent
                right: statusImage.left
            }
        }

        ProgressBar{
            id: statusProgres
            width: 200
            height: parent.height
            anchors.right: parent.right
            maximumValue: 100
            minimumValue: 0
            visible: false
        }

        Timer{
            id: textTimer
            interval: 2000
            repeat: false
            running: true;
            onTriggered: {
                statusProgres.visible = false
                statusText.text = ""
            }
        }
    }
}
