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
private:
    QSqlDatabase db;
    void initDB();

signals:
    void baseCreate();

public slots:
    void rescanCollection();
};

#endif // DBADAPTER_H
