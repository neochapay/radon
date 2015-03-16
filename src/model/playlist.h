#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>

class PlayList : public QObject
{
    Q_OBJECT
public:
    explicit PlayList(QObject *parent = 0);

signals:
    void playListUpdate();

public slots:
    void addItem(int track_id,int count=0);
    QList<int> getPlayList() const {return playList;}

private:
    QList<int> playList;
};

#endif // PLAYLIST_H
