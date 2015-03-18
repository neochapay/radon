#include "playlistmodel.h"
#include <QDebug>
#include <QAbstractListModel>

PlayListModel::PlayListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    playList.append(1);
    playList.append(2);
    playList.append(3);
}


void PlayListModel::addItem(int track_id, int count)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount()-1);
    playList.append(track_id);
    qDebug() << playList;
    endInsertRows();
}

int PlayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return playList.count();
}

QVariant PlayListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= playList.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return playList.at(index.row());
    else
        return QVariant();
}

bool PlayListModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        playList.insert(position, 0);
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
