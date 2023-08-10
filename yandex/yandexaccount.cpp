#include "yandexaccount.h"

YandexAccount::YandexAccount(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager(this);
}

void YandexAccount::askInfo()
{
    Secrets *secrets = Secrets::getInstance();

    QUrl deviceUrl = QUrl("https://login.yandex.ru/info");
    QNetworkRequest request(deviceUrl);
    QString authorizationHeader = "OAuth " + secrets->get(OAUTH_TOKEN_NAME);

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Authorization", authorizationHeader.toLocal8Bit());

    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();

            QJsonDocument document = QJsonDocument::fromJson(response);
            QJsonObject root = document.object();

            name = root.value("display_name").toString();
            avatarId = root.value("default_avatar_id").toString();

            emit infoReady();
        } else {
            qDebug() << "Error occured during getting account info:" << reply->errorString();

            emit error();
        }
    });
}

QString YandexAccount::getName()
{
    return name;
}

QString YandexAccount::getAvatarId()
{
    return avatarId;
}
