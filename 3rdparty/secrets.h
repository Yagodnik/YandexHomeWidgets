#ifndef SECRETS_H
#define SECRETS_H

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

#define APP_VERSION "app_version"

class Secrets
{
public:
    static Secrets *getInstance();

    QString get(QString key);
    Q_INVOKABLE void saveToSettings(QString key, QString value);
    void clearValue(QString key);
    int appVersion();

private:
    QMap<QString, QString> data;
    QSettings settings;

    Secrets();
    Secrets(const Secrets&);
    Secrets& operator=(Secrets&);
};

#endif // SECRETS_H
