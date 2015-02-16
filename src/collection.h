#ifndef COLLECTION_H
#define COLLECTION_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QVariant>

class Collection : public QObject
{
    Q_OBJECT
public:
    explicit Collection(QObject *parent = 0);
    ~Collection();

    QDir collectionDir;
    QString collectionDirString;

private:
    QThread* thread;

signals:
    void erorrAcces();
    void notAllTags();
    void readyToCopy(QString file);
    void setStatusText(QVariant status);

public slots:
    void addFiles(QVariant files);
    void addFile(QString fileName);
    void removeFile(QFile &file);
    void setStatus(QString status);
    void rescan();
};

#endif // COLLECTION_H
