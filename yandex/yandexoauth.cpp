#include "yandexoauth.h"

YandexOAuth::YandexOAuth(QObject *parent)
    : QObject{parent}
{
    replyHandler = new QOAuthHttpServerReplyHandler(1337, this);
    oauth2 = new QOAuth2AuthorizationCodeFlow(this);

    Secrets *secrets = Secrets::getInstance();

    qDebug() << "Client id:" << secrets->get("client_id");

    oauth2->setReplyHandler(replyHandler);
    oauth2->setAuthorizationUrl(QUrl("https://oauth.yandex.ru/authorize"));
    oauth2->setAccessTokenUrl(QUrl("https://oauth.yandex.ru/token?grant_type=authorization_code"));
    oauth2->setClientIdentifier(secrets->get("client_id"));
    oauth2->setClientIdentifierSharedKey(secrets->get("client_secret"));
    oauth2->setScope("iot:view iot:control");

    connect(oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](QAbstractOAuth::Status status) {
        if (status == QAbstractOAuth::Status::Granted) {
            qDebug() << "granted!";

            token = oauth2->token();
            emit granted();
        }
    });

    connect(oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, [=](QUrl url) {
        QUrlQuery query(url);

        qDebug() << url;

        query.addQueryItem("response_type", "code");

        url.setQuery(query);
        QDesktopServices::openUrl(url);
    });
}

void YandexOAuth::grant()
{
    oauth2->grant();
}

QString YandexOAuth::getToken()
{
    return token;
}
