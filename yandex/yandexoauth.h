#ifndef YANDEXOAUTH_H
#define YANDEXOAUTH_H

#include <QObject>
#include <QDebug>
#include <QtNetworkAuth>
#include <QByteArray>
#include <QDesktopServices>
#include "3rdparty/secrets.h"

class YandexOAuth : public QObject
{
    Q_OBJECT
public:
    explicit YandexOAuth(QObject *parent = nullptr);

    Q_INVOKABLE void grant();
    Q_INVOKABLE QString getToken();

signals:
    void granted();

private:
    QOAuth2AuthorizationCodeFlow *oauth2;
    QOAuthHttpServerReplyHandler *replyHandler;
    QString token;
};

#endif // YANDEXOAUTH_H
