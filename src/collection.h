#ifndef COLLECTION_H
#define COLLECTION_H

#include <QObject>
#include <QFile>
#include <QDir>

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

public slots:
    Q_INVOKABLE void addFile(QString fileName);
    void removeFile(QFile &file);
    void rescan();
};

#endif // COLLECTION_H
