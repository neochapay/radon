#ifndef DBADAPTER_H
#define DBADAPTER_H

#include <QObject>
#include <QtSql>
#include <QSqlQueryModel>

class dbAdapter : public QObject
{
    Q_OBJECT
public:
    explicit dbAdapter(QObject *parent = 0);
    ~dbAdapter();

    static dbAdapter& instance();

    int getArtistID(QString);
    void addArtist(QString);
    QList<int> getArtistSong(int artist_id);

    void addSong(int artist_id, QString title, QString album, QString comment, QString genere, int track, int year);
    QSqlQueryModel *getTable(QString table);

private:
    QSqlDatabase db;
    QSqlQuery query;
    QMutex lock;
    void initDB();

signals:
    void baseCreate();
    void dbRescanEnd();

public slots:
    void rescanCollection();
};

#endif // DBADAPTER_H
