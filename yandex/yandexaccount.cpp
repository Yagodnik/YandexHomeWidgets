#include "yandexaccount.h"

YandexAccount::YandexAccount(QObject *parent)
    : QObject{parent}
{
    networkManager = new QNetworkAccessManager(this);
}

YandexAccount::~YandexAccount()
{
    networkManager->deleteLater();
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

            qDebug() << reply->error();

            switch (reply->error()) {
            case QNetworkReply::AuthenticationRequiredError:
                emit error(1);
                break;
            case QNetworkReply::UnknownNetworkError:
                emit error(2);
                break;
            case QNetworkReply::HostNotFoundError:
                emit error(2);
                break;
            default:
                emit error(0);
                break;
            }
        }

        reply->deleteLater();
    });
}

QString YandexAccount::getName()
{
    if (name.length() >= 15)
        return name.mid(0, 15) + "...";

    return name;
}

QString YandexAccount::getAvatarId()
{
    return avatarId;
}
