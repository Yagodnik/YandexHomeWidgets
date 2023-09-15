#ifndef YANDEXOAUTH_H
#define YANDEXOAUTH_H

#include <QObject>
#include <QDebug>
#include <QtNetworkAuth>
#include <QByteArray>
#include <QDesktopServices>
#include <QFile>
#include "3rdparty/secrets.h"
#include "3rdparty/constants.h"

class YandexOAuth : public QObject
{
    Q_OBJECT
public:
    explicit YandexOAuth(QObject *parent = nullptr);
    ~YandexOAuth();

    Q_INVOKABLE void grant();
    Q_INVOKABLE QString getToken();
    Q_INVOKABLE void saveToken(QString token);
    Q_INVOKABLE void logout();

signals:
    void granted();

private:
    QOAuth2AuthorizationCodeFlow oauth2;
    QOAuthHttpServerReplyHandler replyHandler;
    QString token;

    QString getCallbackContent();
};

#endif // YANDEXOAUTH_H
