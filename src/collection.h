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
    void addFile(QFile &file);
    void removeFile(QFile &file);
    void rescan();

    QDir collectionDir;

signals:
    void erorrAcces();

public slots:
};

#endif // COLLECTION_H
