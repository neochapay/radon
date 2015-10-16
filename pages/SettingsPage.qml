import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Rectangle {
    id: settingsPageArea
    width: parent.width
    height: parent.height
    color: "transparent"

    Rectangle{
        id: repeatSettings
        width: childrenRect.width
        height: 100
        border.color: "#5b5b5b"
        color: "transparent"
        x: 10
        y: 10
        z:8

        Rectangle{
            id: settingsLabel
            width: childrenRect.width+6
            height: childrenRect.height
            z: 9
            x: 10
            y: -8
            color: "#aaaaaa"

            Text{
                text: qsTr("Repeat settings")
                x: 3
            }
        }


        Rectangle{
            id: songRepeatItem
            width: settingsPageArea.width-20
            height: songRepeat.height
            color: "transparent"

            anchors{
                top: parent.top
                left: parent.left
                topMargin: 15
            }

            Text{
                id: songRepeatLabel
                text: qsTr("Song repeat:")
                width: 200;
                anchors{
                    left: parent.left
                    verticalCenter: songRepeat.verticalCenter
                    leftMargin: 10
                }
            }
            TextField{
                id: songRepeat
                anchors{
                    left: songRepeatLabel.right
                }
                text: Settings.value("SongRepeat",240)
                validator: IntValidator{}
                onEditingFinished: {
                    Settings.setValue("SongRepeat",songRepeat.text)
                }
            }
            Text{
                id: songRepeatHelp
                text: qsTr("time in minuts that must elapse before song can played")
                anchors{
                    left: songRepeat.right
                    verticalCenter: songRepeat.verticalCenter
                    leftMargin: 10
                }
            }
        }

        Rectangle{
            id: artistRepeatItem
            width: settingsPageArea.width-20
            height: artistRepeat.height
            color: "transparent"

            anchors{
                top: songRepeatItem.bottom
                left: parent.left
                topMargin: 15
            }

            Text{
                id: artistRepeatLabel
                text: qsTr("Artist repeat:")
                width: 200;
                anchors{
                    left: parent.left
                    verticalCenter: artistRepeat.verticalCenter
                    leftMargin: 10
                }
            }
            TextField{
                id: artistRepeat
                anchors{
                    left: artistRepeatLabel.right
                }
                text: Settings.value("ArtistRepeat",60)
                validator: IntValidator{}
                onEditingFinished: {
                    Settings.setValue("ArtistRepeat",artistRepeat.text)
                }
            }
            Text{
                id: artistRepeatHelp
                text: qsTr("time in minuts that must elapse before songs of artist can played")
                anchors{
                    left: artistRepeat.right
                    verticalCenter: artistRepeat.verticalCenter
                    leftMargin: 10
                }
            }
        }
    }

    Button{
        text: qsTr("Save settings")
        anchors{
            bottom: settingsPageArea.bottom
            right: settingsPageArea.right
            bottomMargin: 5
            rightMargin: 5
        }

        onClicked:{
            Settings.sync();
        }
    }
}

