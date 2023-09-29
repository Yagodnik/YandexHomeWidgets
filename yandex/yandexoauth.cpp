#include "yandexoauth.h"

YandexOAuth::YandexOAuth(QObject *parent)
    : QObject{parent}, replyHandler(1337)
{
//    replyHandler = new QOAuthHttpServerReplyHandler(1337, this);

    Secrets *secrets = Secrets::getInstance();

    token = secrets->get(OAUTH_TOKEN_NAME);

    oauth2.setReplyHandler(&replyHandler);
    oauth2.setAuthorizationUrl(QUrl("https://oauth.yandex.ru/authorize"));
    oauth2.setAccessTokenUrl(QUrl("https://oauth.yandex.ru/token?grant_type=authorization_code"));
    oauth2.setClientIdentifier(secrets->get("client_id"));
    oauth2.setClientIdentifierSharedKey(secrets->get("client_secret"));
    oauth2.setScope("iot:view iot:control login:info login:avatar");

    replyHandler.setCallbackText(getCallbackContent());

    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](QAbstractOAuth::Status status) {
        if (status == QAbstractOAuth::Status::Granted) {
            token = oauth2.token();
            emit granted();
        }
    });

    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, [=](QUrl url) {
        QUrlQuery query(url);
        query.addQueryItem("response_type", "code");
        url.setQuery(query);

        QDesktopServices::openUrl(url);
    });
}

YandexOAuth::~YandexOAuth()
{
//    oauth2->deleteLater();
//    replyHandler->deleteLater();
}

void YandexOAuth::grant()
{
    oauth2.grant();
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

void YandexOAuth::logout()
{
    Secrets *secrets = Secrets::getInstance();

    secrets->clearValue(OAUTH_TOKEN_NAME);
}

QString YandexOAuth::getCallbackContent()
{
    QFile document(":/assets/web/callback.html");

    if (!document.open(QIODevice::ReadOnly)) {
        qDebug() << "Cant open file with callback!";
        return tr("Авторизация выполнена успешно! Теперь вы можете свободно закрыть эту страницу и вернуться в приложение");
    }

    QString content = document.readAll();
    document.close();

    return content;
}
