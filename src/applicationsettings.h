#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QSettings>

class ApplicationSettings : public QObject{
    Q_OBJECT

public:
    explicit ApplicationSettings(QObject *parent = 0);
    ~ApplicationSettings();
    QSettings *settings;

signals:

public slots:
    Q_INVOKABLE void setValue(const QString &key, const QVariant &value);
    Q_INVOKABLE QVariant value(const QString &key, const QVariant &defaultValue = QVariant());
    Q_INVOKABLE void sync();
};

#endif // APPLICATIONSETTINGS_H
