#include "playlistmodel.h"
#include "../dbadapter.h"
#include "../applicationsettings.h"

#include <QDebug>
#include <QAbstractListModel>
#include <QSqlDatabase>
#include <QSqlQuery>

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

void PlayListModel::setPlayed(int idx, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(idx <= playList.count())
    {
        for (int row = 0; row < playList.count(); ++row) {
            playList[row].playEd = false;
            dataChanged(index(row),index(row));
        }
        playList[idx].playEd = true;
        dataChanged(index(idx),index(idx));

        //add to database
        int track_id = get(idx);
        QSqlDatabase db = dbAdapter::instance().db;
        QSqlQuery query(db);
        query.prepare("INSERT INTO playlist (`song_id`, `time`) VALUES ( :trackid , :time)");
        query.bindValue(":trackid",track_id);
        query.bindValue(":time", QDateTime().toTime_t());

        bool ok = query.exec();
        if(!ok)
        {
            qDebug() << query.lastQuery() << query.lastError().text();
        }
    }
}

int PlayListModel::get(int idx)
{
    if(idx < playList.size())
    {
        return playList[idx].trackId;
    }
    return 0;
}


void PlayListModel::remove(int idx)
{
    this->removeRows(idx,1);
}

//Format auto playlist
void PlayListModel::formatAutoPlaylist()
{
    ApplicationSettings *settings = new ApplicationSettings();
    uint songRepeat = settings->value("SongRepeat").toInt()*60;
    uint artistRepeat = settings->value("ArtistRepeat").toInt()*60;

    int smartSong = 10; //How many songs add to playlist
    int errors = 0;     //num of errors
    int buildRepear = 8;//mar repeat of find song

    for(int i=0; i < smartSong; i++)
    {
        if(errors > buildRepear)
        {
            break;
        }

        QString s_notin = QString("0");
        QString a_notin = QString("0");

        foreach (playListItem item, playList) {
            s_notin.append(","+item.trackId);
        }

        QSqlDatabase db = dbAdapter::instance().db;
        QSqlQuery query(db);
//create played artist list
        query.prepare("SELECT songs.artist_id FROM songs "
                      "INNER JOIN playlist ON songs.id = playlist.song_id "
                      "WHERE ptime < :atime");
        query.bindValue(":atime",QDateTime().toTime_t()-artistRepeat);
        if(query.next())
        {
            a_notin.append(",");
            a_notin.append(query.value(0).toString());
        }
//create songs list
        query.prepare("SELECT songs.id,playlist.time as ptime FROM songs "
                  "LEFT OUTER JOIN playlist ON songs.id = playlist.song_id "
                  "WHERE ptime < :stime OR ptime IS NULL "
                  "AND songs.id NOT IN (:s_notin) "
                  "AND artist_id NOT IN (:a_notin) "
                  "ORDER BY RANDOM()");
        query.bindValue(":stime",QDateTime().toTime_t()-songRepeat);
        query.bindValue(":s_notin",s_notin);
        query.bindValue(":a_notin",a_notin);

        bool ok = query.exec();
        if(!ok)
        {
            qDebug() << query.lastQuery() << query.lastError().text();
        }

        if(query.next())
        {
             addItem(query.value(0).toInt(),"track");
        }
        else
        {
            errors++;
            i++;
        }
    }
}
