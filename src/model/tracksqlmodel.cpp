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
    hash.insert(Qt::UserRole+8,QByteArray("artist_name"));
    refresh();
}

const char* TrackSqlModel::SQL_SELECT = "SELECT songs.id as track_id,songs.artist_id,songs.title,songs.album,songs.comment,songs.genere,songs.track,songs.year,artist.name as artist_name FROM songs INNER JOIN artist ON artist.id = songs.artist_id ORDER BY artist_name ASC";

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


void TrackSqlModel::setArtist(int artist_id)
{
    SQL_SELECT = QString("SELECT songs.id as track_id,songs.artist_id,songs.title,songs.album,songs.comment,songs.genere,songs.track,songs.year,artist.name as artist_name FROM songs INNER JOIN artist ON artist.id = songs.artist_id WHERE artist_id = %1 ORDER BY artist_name ASC").arg(artist_id).toUtf8();
}


void TrackSqlModel::cleanQuery()
{
    SQL_SELECT = "SELECT songs.id as track_id,songs.artist_id,songs.title,songs.album,songs.comment,songs.genere,songs.track,songs.year,artist.name as artist_name FROM songs INNER JOIN artist ON artist.id = songs.artist_id ORDER BY artist_name ASC";
}
