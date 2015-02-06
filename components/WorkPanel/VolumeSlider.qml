import QtQuick 2.0

Rectangle {
    property string position: "left";
    property real value: 100;

    signal valueChange(real value);

    id: soundslider;
    color: "transparent";

    Rectangle{
        width: 4
        height: parent.height

        anchors{
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        Rectangle{
            id: red
            width: parent.width
            height: parent.height*0.10
            color: "red"
            anchors.top: parent.top
        }

        Rectangle{
            id: yellow
            width: parent.width
            height: parent.height*0.10
            color: "yellow"
            anchors.top: red.bottom
        }

        Rectangle{
            id: green
            width: parent.width
            height: parent.height*0.80
            color: "green"
            anchors.top: yellow.bottom
        }

        Rectangle {
            id: sliderBtn
            x: -8;
            y: parent.height*0.2;
            width: 20; height: 10
            radius: 2
            smooth: true
            color:"#f2f2f2"
            border.color: "#d4d4d4"
            border.width: 1

            MouseArea {
                anchors.fill: parent
                drag.target: parent
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: soundslider.height-parent.height
                onPositionChanged: {
                    value = ((soundslider.height-this.parent.y)/soundslider.height)*120
                    valueChange(value);
                }
           }
       }
    }
}

