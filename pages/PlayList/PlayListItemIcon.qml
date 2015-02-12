import QtQuick 2.0

Text {
    signal buttonClicked();

    anchors{
        bottom: parent.bottom
        rightMargin: 3
        bottomMargin: 3
    }
    MouseArea{
        anchors.fill: parent
        onClicked: buttonClicked()
    }
}

