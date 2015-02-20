#ifndef DBADAPTER_H
#define DBADAPTER_H

#include <QObject>
#include <QtSql>

class dbAdapter : public QObject
{
    Q_OBJECT
public:
    explicit dbAdapter(QObject *parent = 0);
    ~dbAdapter();

    int getArtistID(QString);
    void addArtist(QString);
    QList<int> getArtistSong(int artist_id);

    void addSong(int artist_id, QString title, QString album, QString comment, QString genere, int track, int year);

private:
    QSqlDatabase db;
    QSqlQuery query;
    void initDB();

signals:
    void baseCreate();

public slots:
    void rescanCollection();
};

#endif // DBADAPTER_H
