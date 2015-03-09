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

    int getArtistId() {return artist_id;}
    QString getTitle() {return title;}
    QString getAlibum() {return album;}
    QString getGenere() {return genere;}
    int getTrack() {return track;}
    int getYear() {return year;}
    QString getComment() {return comment;}

    bool setArtistId(int artist_id);
    bool setTitle(QString title);
    void setAlbum(QString album) {this->album = album;}
    void setGenere(QString genere) {this->genere = genere;}
    void setTrack(int track) {this->track = track;}
    void setYear(int year) {this->year = year;}
    void setComment(QString comment) {this->comment = comment;}

    Artist* getArtist() {return artist;}
    void setArtist(Artist *artist) {this->artist = artist;}

    static Track* toId(int trackId);
    static void remove(int track_id);

    void insert();
    void update();

private:
    static QHash<int, Track*> cache;

    int artist_id;
    QString title;
    QString album;
    QString genere;
    int track;
    int year;
    QString comment;

    Artist *artist;
    bool played;

    uint startTime;
    uint endTime;
};

#endif // TRACK_H
