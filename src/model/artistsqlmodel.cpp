#include "artistsqlmodel.h"

#include <QSqlQueryModel>

ArtistSqlModel::ArtistSqlModel(QObject *parent) : QSqlQueryModel(parent)
{
    hash.insert(Qt::UserRole,QByteArray("artist_id"));
    hash.insert(Qt::UserRole+1,QByteArray("name"));
    refresh();
}

const char* ArtistSqlModel::SQL_SELECT = "SELECT id as artist_id, name FROM artist ORDER BY name ASC";

QVariant ArtistSqlModel::data(const QModelIndex &index, int role) const{
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

void ArtistSqlModel::refresh()
{
    this->setQuery(SQL_SELECT);
}
