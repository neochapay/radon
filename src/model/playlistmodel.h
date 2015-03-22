#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QAbstractListModel>

class PlayListModel : public QAbstractListModel
{
    Q_OBJECT
    struct playListItem{
        int trackId;
        QString trackType;
        bool playEd;
    };

public:
    explicit PlayListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {return hash;}

    bool insertRows(int position, int rows, playListItem &item, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    QList<playListItem> playList;

public slots:
    void addItem(int track_id,QString type, int count=0);
    void setPlayed(int index);

signals:
    void playListUpdate();

private:
    QHash<int,QByteArray> hash;
};

#endif // PLAYLIST_H
