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
    }
}

QList<QString> AudioFile::getTags()
{
    QList<QString> tags;

    TagLib::FileRef file(QFileInfo(mediaFile->fileName()).absoluteFilePath().toUtf8());

    TagLib::String artist = file.tag()->artist();
    TagLib::String title = file.tag()->title();
    TagLib::String album = file.tag()->album();

    tags.append(QString::fromStdWString(artist.toCWString()));
    tags.append(QString::fromStdWString(title.toCWString()));
    tags.append(QString::fromStdWString(album.toCWString()));

    return tags;
}

bool AudioFile::setTags(QList<QString> tags)
{
    if(tags.length() != 3)
    {
        emit tagsArrayNotFound();
        return false;
    }

    TagLib::FileRef file(QFileInfo(mediaFile->fileName()).absoluteFilePath().toUtf8());
    file.tag()->setArtist(tags[0].toStdWString());
    file.tag()->setTitle(tags[1].toStdWString());
    file.tag()->setAlbum(tags[2].toStdWString());
    return file.save();
}

AudioFile::~AudioFile()
{
    mediaFile->close();
}

