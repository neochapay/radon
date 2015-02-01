#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <QObject>
#include <QFile>

class AudioFile : public QObject
{
    Q_OBJECT
public:
    explicit AudioFile(QString audiofile, QObject *parent = 0);
    ~AudioFile();

    QList<QString> getTags();
    bool setTags(QList<QString> tags);

private:
    QFile *mediaFile;

signals:
    void fileNotFound();
    void tagsArrayNotFound();

public slots:
};

#endif // AUDIOFILE_H
