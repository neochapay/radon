import QtQuick 2.0
import QtQuick.Controls 1.0

import "../components/WorkPanel"
import "../pages"

Rectangle {
    id: workPanel
    color:"#7f7f7f";
    width: parent.width

    Rectangle{
        id: workArea
        width: workPanel.width-controls.width-30
        height: workPanel.height-20
        x: 10
        y: 10
        color: "#aaaaaa"
        border.color: "#5b5b5b"
        anchors{
            left: workPanel.left
            leftMargin: 10
        }

        Component.onCompleted: {
            playlistPage.visible = true;
        }

        function listPage(page)
        {
            console.log("Page="+page)
        }

        CalendarPage{
            id: calendarPage
            visible: false;
        }
        PlaylistPage{
            id: playlistPage
            visible: false;
        }
        InformationPage{
            id: informationPage
            visible: false;
        }
        LibraryPage{
            id: libraryPage
            visible: false;
        }
        SettingsPage{
            id: settingsPage
            visible: false;
        }
    }

    Rectangle{
        id: controls
        width: 250
        height: workPanel.height-20
        x: 10
        y: 10
        color: "#aaaaaa"
        border.color: "#5b5b5b"
        anchors{
            left: workArea.right
            leftMargin: 10
        }

        Rectangle{
            id: sliders
            width: 230
            height: 300
            color: "transparent"
            anchors{
                topMargin: 10
                top: controls.top
            }
            x: 17

            Rectangle{
                id: streamSliders
                width: 100
                height: 300
                color: "transparent"

                VolumeSlider{
                    id: streamLeftSlider
                    height: 280-streamLabel.height
                    x: 27
                    y: 10
                    onValueChange:{
                        streamRightSlider.setValue(this.value)
                        streamProcessor.setVolume(streamLeftSlider.value/100, streamRightSlider.value/100)
                    }
                }

                VolumeSlider{
                    id: streamRightSlider
                    height: 280-streamLabel.height
                    anchors.left: streamLeftSlider.right
                    y: 10
                    onValueChange: {
                        streamLeftSlider.setValue(this.value)
                        streamProcessor.setVolume(streamLeftSlider.value/100, streamRightSlider.value/100)
                    }
                }

                Text{
                    id: streamLabel
                    anchors.bottom: streamSliders.bottom
                    text: qsTr("Stream")
                    width: streamSliders.width
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Rectangle{
                id: djSliders
                width: 100
                height: 300
                color: "transparent"
                anchors{
                    left: streamSliders.right
                    leftMargin: 10
                }

                VolumeSlider{
                    id: djLeftSlider
                    height: 280-djLabel.height
                    y: 10
                    x: 27
                    onValueChange: djRightSlider.setValue(this.value)
                }

                VolumeSlider{
                    id: djRightSlider
                    height: 280-djLabel.height
                    anchors.left: djLeftSlider.right
                    y: 10
                    onValueChange: djLeftSlider.setValue(this.value)
                }

                Text{
                    id: djLabel
                    anchors.bottom: djSliders.bottom
                    text: qsTr("DJ")
                    width: djSliders.width
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }
}

