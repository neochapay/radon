import QtQuick 2.0

Rectangle {
    property string position: "left";
    property var value;
    id: soundslider;
    color: "transparent";

    Rectangle{
        width: 4
        height: parent.height

        anchors{
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        gradient: Gradient {
                GradientStop { position: 0.0; color: "red" }
                GradientStop { position: 0.15; color: "green" }
            }

        Rectangle {
            id: sliderBtn
            x: -8;
            y: parent.height*0.1;
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
                drag.maximumY: soundslider.height-parent.height-1
                onPositionChanged: {
                    value = ((soundslider.height-this.parent.y)/soundslider.height*1.15)*100
                    console.log(value);
                }
           }
       }
    }
}

