#ifndef YANDEXACCOUNT_H
#define YANDEXACCOUNT_H

#include <QObject>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <QJsonDocument>
#include <QJsonObject>
#include "3rdparty/secrets.h"
#include "3rdparty/constants.h"

class YandexAccount : public QObject
{
    Q_OBJECT
public:
    explicit YandexAccount(QObject *parent = nullptr);

    Q_INVOKABLE void askInfo();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE QString getAvatarId();

signals:
    void infoReady();
    void error(int errorCode);

private:
    QNetworkAccessManager networkManager;

    QString name;
    QString avatarId;
};

#endif // YANDEXACCOUNT_H
