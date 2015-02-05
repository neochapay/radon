#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <QObject>
#include <QFile>
#include <taglib/fileref.h>

class AudioFile : public QObject
{
    Q_OBJECT
public:
    explicit AudioFile(QString audiofile, QObject *parent = 0);
    ~AudioFile();

    QString artist;
    QString title;
    QString album;
    QString comment;
    QString genre;
    uint track;
    uint year;

    bool sync();
    void loadTags();

private:
    QFile *mediaFile;
    TagLib::FileRef *tagFile;

signals:
    void fileNotFound();
    void tagsArrayNotFound();

public slots:
};

#endif // AUDIOFILE_H
