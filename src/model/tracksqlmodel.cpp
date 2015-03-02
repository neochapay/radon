#include "tracksqlmodel.h"

TrackSqlModel::TrackSqlModel(QObject *parent) : QSqlQueryModel(parent)
{
    hash.insert(Qt::UserRole  ,QByteArray("track_id"));
    hash.insert(Qt::UserRole+1,QByteArray("artist_id"));
    hash.insert(Qt::UserRole+2,QByteArray("title"));
    hash.insert(Qt::UserRole+3,QByteArray("album"));
    hash.insert(Qt::UserRole+4,QByteArray("comment"));
    hash.insert(Qt::UserRole+5,QByteArray("genere"));
    hash.insert(Qt::UserRole+6,QByteArray("tarck"));
    hash.insert(Qt::UserRole+7,QByteArray("year"));
    refresh();
}

const char* TrackSqlModel::SQL_SELECT = "SELECT id as track_id,artist_id,title,album,comment,genere,track,year FROM songs";

QVariant TrackSqlModel::data(const QModelIndex &index, int role) const{
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

void TrackSqlModel::refresh()
{
    this->setQuery(SQL_SELECT);
}
