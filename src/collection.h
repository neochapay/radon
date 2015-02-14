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

signals:
    void erorrAcces();
    void notAllTags();
    void readyToCopy(QString file);

public slots:
    void addFiles(QVariant files);
    void addFile(QString fileName);
    void removeFile(QFile &file);
    void rescan();
};

#endif // COLLECTION_H
