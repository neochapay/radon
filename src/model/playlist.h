#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>

class PlayList : public QObject
{
    Q_OBJECT
public:
    explicit PlayList(QObject *parent = 0);
    QList<int> getPlayList();

signals:
    void playListUpdate();

public slots:
    void addItem(int track_id,int count=0);
private:
    QList<int> playList;
};

#endif // PLAYLIST_H
