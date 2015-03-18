#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QAbstractListModel>

class PlayListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlayListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

public slots:
    void addItem(int track_id,int count=0);

signals:
    void playListUpdate();

private:
    QList<int> playList;
};

#endif // PLAYLIST_H
