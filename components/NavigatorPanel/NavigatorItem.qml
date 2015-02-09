import QtQuick 2.0

Rectangle {
    id: navButton
    property var label;
    property bool activate: false;

    signal navButtonClick(string label);

    width: 110
    height: parent.height
    state: "deactevated"

    Text{
        id: itemText
        anchors.fill: parent
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

        onClicked: {
            navigationPanel.deactive()
            parent.state = "actived";
            parent.parent.parent.update(label)
        }
    }

    states:[
        State{
            name: "actived"; when: activate
            PropertyChanges {target: navButton; color: "black"}
            PropertyChanges {target: itemText; color: "white"}
        },
        State {
            name: "deactevated"; when: !activate
            PropertyChanges {target: navButton; color: "transparent"}
            PropertyChanges {target: itemText; color: "#ccc"}
        }
    ]
}

