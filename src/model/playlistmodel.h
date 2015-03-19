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
    };

public:
    explicit PlayListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {return hash;}

    bool insertRows(int position, int rows, playListItem &item, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

public slots:
    void addItem(int track_id,QString type, int count=0);

signals:
    void playListUpdate();

private:
    QList<playListItem> playList;
    QHash<int,QByteArray> hash;
};

#endif // PLAYLIST_H
