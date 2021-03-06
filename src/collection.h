#ifndef COLLECTION_H
#define COLLECTION_H

#include "dbadapter.h"

#include <QObject>
#include <QFile>
#include <QDir>
#include <QVariant>
#include <QtSql>


class Collection : public QObject
{
    Q_OBJECT
public:
    explicit Collection(QObject *parent = 0);
    ~Collection();

    QDir collectionDir;
    QString collectionDirString;
    Q_INVOKABLE QSqlQueryModel *artistModel;
    Q_INVOKABLE QSqlQueryModel *songModel;

private:
    dbAdapter* dba;

    QThread* thread;
    double copyCount;
    double copyAll;
    void setProcess();
    void initDB();

signals:
    void erorrAcces();
    void notAllTags();
    void readyToCopy(QString file);
    void setStatusText(QVariant status);
    void setStatusProcess(QVariant prc);
    void fileCopyTick();
    void baseCreate();

public slots:
    void addFiles(QVariant files);
    void removeFile(QFile &file);
    void setStatus(QString status);
    void processTick();
    void rescanBase();
};

#endif // COLLECTION_H
