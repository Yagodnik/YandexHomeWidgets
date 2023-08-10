#include "yandexoauth.h"

YandexOAuth::YandexOAuth(QObject *parent)
    : QObject{parent}
{
    replyHandler = new QOAuthHttpServerReplyHandler(1337, this);
    oauth2 = new QOAuth2AuthorizationCodeFlow(this);

    Secrets *secrets = Secrets::getInstance();

    token = secrets->get(OAUTH_TOKEN_NAME);

    qDebug() << "Saved token:" << token;

    oauth2->setReplyHandler(replyHandler);
    oauth2->setAuthorizationUrl(QUrl("https://oauth.yandex.ru/authorize"));
    oauth2->setAccessTokenUrl(QUrl("https://oauth.yandex.ru/token?grant_type=authorization_code"));
    oauth2->setClientIdentifier(secrets->get("client_id"));
    oauth2->setClientIdentifierSharedKey(secrets->get("client_secret"));
    oauth2->setScope("iot:view iot:control login:info login:avatar");

    connect(oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](QAbstractOAuth::Status status) {
        if (status == QAbstractOAuth::Status::Granted) {
            token = oauth2->token();
            emit granted();
        }
    });

    connect(oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, [=](QUrl url) {
        QUrlQuery query(url);
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

void YandexOAuth::saveToken(QString token)
{
    Secrets *secrets = Secrets::getInstance();

    secrets->saveToSettings(OAUTH_TOKEN_NAME, token);
}
