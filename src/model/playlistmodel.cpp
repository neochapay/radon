#include "playlistmodel.h"
#include <QDebug>
#include <QAbstractListModel>

PlayListModel::PlayListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    hash.insert(Qt::UserRole ,QByteArray("trackId"));
    hash.insert(Qt::UserRole+1 ,QByteArray("trackType"));
    hash.insert(Qt::UserRole+2 ,QByteArray("playEd"));
}


void PlayListModel::addItem(int track_id,QString type,int count)
{
    playListItem item;
    item.trackId = track_id;
    item.trackType = type;
    item.playEd = false;

    if(count == 0)
    {
        count = playList.size();
    }
    insertRows(count,1,item);
}

int PlayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return playList.count();
}

QVariant PlayListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);
    if (!index.isValid())
        return QVariant();

    if (index.row() >= playList.size())
        return QVariant();
    playListItem item = playList.at(index.row());
    if(role == Qt::UserRole)
    {
        return item.trackId;
    }
    else if(role == Qt::UserRole+1)
    {
        return item.trackType;
    }
    else if(role == Qt::UserRole+2)
    {
        return item.playEd;
    }
    return QVariant();
}

bool PlayListModel::insertRows(int position, int rows, playListItem &item, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        playList.insert(position, item);
    }
    endInsertRows();
    return true;
}

bool PlayListModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        playList.removeAt(position);
    }
    endRemoveRows();
    return true;
}

void PlayListModel::setPlayed(int index)
{
    if(index <= playList.count())
    {
        for (int row = 0; row < playList.count(); ++row) {
            playList[row].playEd = false;
        }
        playList[index].playEd = true;
    }
    emit dataChanged(QModelIndex(),QModelIndex());
}
