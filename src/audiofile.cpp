#include "audiofile.h"

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <QFileInfo>
#include <QIODevice>

AudioFile::AudioFile(QString audiofile, QObject *parent) : QObject(parent)
{
    mediaFile = new QFile(audiofile);
    if(!mediaFile->exists())
    {
        emit fileNotFound();
    }
    else
    {
        mediaFile->open(QIODevice::ReadWrite);
        tagFile = new TagLib::FileRef(QFileInfo(mediaFile->fileName()).absoluteFilePath().toUtf8());
        this->getTags();
    }
}

void AudioFile::getTags()
{
    TagLib::String artist = tagFile->tag()->artist();
    TagLib::String title = tagFile->tag()->title();
    TagLib::String album = tagFile->tag()->album();
    TagLib::String comment = tagFile->tag()->comment();
    TagLib::String genre = tagFile->tag()->genre();
    TagLib::uint track = tagFile->tag()->track();
    TagLib::uint year = tagFile->tag()->year();

    this->artist = QString::fromStdWString(artist.toCWString());
    this->album = QString::fromStdWString(album.toCWString());
    this->title = QString::fromStdWString(title.toCWString());
    this->comment = QString::fromStdWString(comment.toCWString());
    this->genre = QString::fromStdWString(genre.toCWString());
    this->track = track;
    this->year = year;
}

void AudioFile::setArtist(QString artist)
{
    this->artist = artist;
}

void AudioFile::setAlbum(QString album)
{
    this->album = album;
}

void AudioFile::setTitle(QString title)
{
    this->title = title;
}

void AudioFile::setComment(QString comment)
{
    this->comment = comment;
}

void AudioFile::setGenre(QString genre)
{
    this->genre = genre;
}

void AudioFile::setTrack(uint track)
{
    this->track = track;
}

void AudioFile::setYear(uint year)
{
    this->year = year;
}

bool AudioFile::sync()
{
    tagFile->tag()->setAlbum(this->album.toStdWString());
    tagFile->tag()->setArtist(this->artist.toStdWString());
    tagFile->tag()->setComment(this->comment.toStdWString());
    tagFile->tag()->setGenre(this->genre.toStdWString());
    tagFile->tag()->setTitle(this->title.toStdWString());
    tagFile->tag()->setTrack(this->track);
    tagFile->tag()->setYear(this->year);
    return tagFile->save();
}


AudioFile::~AudioFile()
{
    mediaFile->close();
}

