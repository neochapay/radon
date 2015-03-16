#include "playlist.h"

PlayList::PlayList(QObject *parent) :
    QObject(parent)
{
}


void PlayList::addItem(int track_id, int count)
{

}

QList<int> PlayList::getPlayList()
{
    return playList;
}
