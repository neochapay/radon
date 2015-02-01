#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QSettings>

class ApplicationSettings : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationSettings(QObject *parent = 0);
    ~ApplicationSettings();
    QSettings *settings;

signals:

public slots:
};

#endif // APPLICATIONSETTINGS_H
