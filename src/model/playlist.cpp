#include "playlist.h"
#include <QDebug>

PlayList::PlayList(QObject *parent) :
    QObject(parent)
{
    playList.append(1);
    playList.append(2);
    playList.append(3);
}


void PlayList::addItem(int track_id, int count)
{
    playList.append(track_id);
    qDebug() << playList;
}
