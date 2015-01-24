import QtQuick 2.0

Rectangle {
    property var label;

    width: 110
    height: parent.height
    color: "transparent"

    function disable()
    {
        console.log("DIS")
    }

    Text{
        id: itemText
        anchors.fill: parent
        color: "#ccc"
        text: label
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.weight: Font.Bold
        font.capitalization: Font.AllUppercase
    }

    MouseArea {
        anchors.fill: parent;
        anchors.margins: 5
        hoverEnabled: true
        onEntered: {
            parent.color = "black"
            itemText.color = "white"
        }
        onExited: {
            parent.color = "transparent"
            itemText.color = "#ccc"
        }
    }
}

