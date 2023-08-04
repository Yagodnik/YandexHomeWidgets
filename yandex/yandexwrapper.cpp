#include "yandexwrapper.h"

YandexWrapper::YandexWrapper(QObject *parent)
    : QObject{parent}
{
    auto replyHandler = new QOAuthHttpServerReplyHandler(1337, this);
    oauth2.setReplyHandler(replyHandler);
    oauth2.setAuthorizationUrl(QUrl("https://oauth.yandex.ru/authorize"));
    oauth2.setAccessTokenUrl(QUrl("https://oauth.yandex.ru/token?grant_type=authorization_code"));
    oauth2.setClientIdentifier("839335dce224427c832a48442c324552");
    oauth2.setClientIdentifierSharedKey("d9a7c46f9dd64fd582eb155fbd28aa1a");
    oauth2.setScope("iot:view iot:control");

    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](QAbstractOAuth::Status status) {
        if (status == QAbstractOAuth::Status::Granted) {
            qDebug() << "granted!";
            qDebug() << "OAuth token: " << oauth2.token();
        }
    });

    connect(&oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
        [=](QUrl url) {
            QUrlQuery query(url);

            qDebug() << url;

            query.addQueryItem("response_type", "code");

            url.setQuery(query);
            QDesktopServices::openUrl(url);
        });
}

void YandexWrapper::grant()
{
    oauth2.grant();
}
