import QtQuick 2.1
import QtQuick.Controls 1.0

import trackAdapter 1.0
import artistAdapter 1.0

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

    property string prevTextLabel: qsTr("Unknow Artist - Unknow Song")
    property string prevTimeLabel: "00:00:00"

    property int progress: 34
    property string currentTextLabel: qsTr("Unknow Artist - Unknow Song")

    property string nextTextLabel: qsTr("Unknow Artist - Unknow Song")
    property string nextTimeLabel: "00:00:00"

    BTrack {id: mThisTrack}
    BArtist{id: mThisArtist}

    function setCurrentPlay(index)
    {
        var curTrackId = playListModel.get(index);
        var curTrack = mThisTrack.toId(curTrackId);
        var curArtistId = curTrack.getArtistId();
        var curArtist = mThisArtist.toId(curArtistId);

        main.prevTextLabel = main.currentTextLabel;
        main.prevTimeLabel = Qt.formatTime(new Date(),"hh:mm:ss");
        main.currentTextLabel = curArtist.getName() + " - " + curTrack.getTitle();

        var nxtTrackId = playListModel.get(index+1);
        if(nxtTrackId !== 0)
        {
            var nxtTrack = mThisTrack.toId(nxtTrackId);
            var nxtArtistId = nxtTrack.getArtistId();
            var nxtArtist = mThisArtist.toId(nxtArtistId);
            main.nextTextLabel = nxtArtist.getName() + " - " + nxtTrack.getTitle();
            main.nextTimeLabel = Qt.formatTime(new Date(new Date().getTime()+curTrack.getLength()),"hh:mm:ss");
        }
        else
        {
            main.nextTextLabel = "Unknow Artist - Unknow Song";
        }

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
