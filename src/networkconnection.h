#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <QSettings>



class NetworkConnection : public QObject
{
    Q_OBJECT
public:
    explicit NetworkConnection(QObject *parent = 0);
    ~NetworkConnection();
    QSettings *settings;
    QString baseUrl;
    QString appKey;
    QString serverKey;

signals:
    void needConfig();

public slots:
};

#endif // NETWORKCONNECTION_H
