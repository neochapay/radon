#ifndef TRACKSQLMODEL_H
#define TRACKSQLMODEL_H

#include <QSqlQueryModel>

class TrackSqlModel :public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit TrackSqlModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    void refresh();
    QHash<int, QByteArray> roleNames() const {return hash;}

private:
    const static char* SQL_SELECT;
    QHash<int,QByteArray> hash;
};

#endif // TRACKSQLMODEL_H
