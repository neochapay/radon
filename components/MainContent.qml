import QtQuick 2.0
import "."
import "../pages"

Rectangle {
    id: mainContent
    width: parent.width
    height: parent.height
    MasterPanel{
        id: master
    }

    function update(label)
    {
        work.listPage(label)
    }

    NavigationPanel{
        id: nav
        anchors.top: master.bottom
    }

    WorkPanel{
        id: work
        width: parent.width
        height: mainContent.height-master.height-nav.height-1000
        anchors{
            top: nav.bottom
            bottom:mainContent.bottom
        }
    }

}

