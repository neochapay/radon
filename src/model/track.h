#ifndef TRACK_H
#define TRACK_H

#include <QtCore>
#include "item.h"

class Artist;

class Track : public Item
{
    Q_OBJECT
public:
    Track();

    bool setArtistId(int artist_id);
    bool setTitle(QString title);
    void setAlbum(QString album) {this->album = album;}
    void setGenere(QString genere) {this->genere = genere;}
    void setTrack(int track) {this->number = track;}
    void setYear(int year) {this->year = year;}
    void setComment(QString comment) {this->comment = comment;}

    Artist* getArtist() {return artist;}
    void setArtist(Artist *artist) {this->artist = artist;}

    static void remove(int track_id);
    void insert();
    void update();

public slots:
    Q_INVOKABLE static Track* toId(int trackId);
    Q_INVOKABLE QString getTitle() {return this->title;}
    Q_INVOKABLE QString getAlbum() {return this->album;}
    Q_INVOKABLE QString getGenere() {return this->genere;}
    Q_INVOKABLE QString getComment() {return this->comment;}

    int getArtistId() {return this->artist_id;}
    int getNumber() {return this->number;}
    int getYear() {return this->year;}


signals:
    void titleChanged();

private:
    static QHash<int, Track*> cache;

    int artist_id;
    QString title;
    QString album;
    QString genere;
    int number;
    int year;
    QString comment;

    Artist *artist;
    bool played;

    uint startTime;
    uint endTime;
};
#endif // TRACK_H
