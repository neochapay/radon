import QtQuick 2.0
import "."
Rectangle {
    id: mainContent
    width: parent.width
    height: parent.height
    MasterPanel{
        id: master
    }
    NavigationPanel{
        id: nav
        anchors.top: master.bottom
    }
    WorkPanel{
        id: work
        anchors{
            top: nav.bottom
            bottom:mainContent.bottom
        }
    }
}

