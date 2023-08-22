#include "yandexdevice.h"
#include "qnetworkreply.h"

YandexDevice::YandexDevice(QString deviceId, QString deviceName, QObject *parent)
    : QObject{parent}
{
    this->deviceId = deviceId;
    this->deviceName = deviceName;

    networkManager = new QNetworkAccessManager(this);
}

QString YandexDevice::getName()
{
    return deviceName;
}

QString YandexDevice::getId()
{
    return deviceId;
}

void YandexDevice::sendPostRequest(QByteArray data)
{
    Secrets *secrets = Secrets::getInstance();

    QTime time;

    QUrl deviceUrl = QUrl("https://api.iot.yandex.net/v1.0/devices/actions");
    QNetworkRequest request(deviceUrl);
    QString authorizationHeader = "Bearer " + secrets->get(OAUTH_TOKEN_NAME);
    QString hash = QString(QCryptographicHash::hash(time.currentTime().toString().toLocal8Bit(),
                                                    QCryptographicHash::Md5).toHex());
    request.setRawHeader("X-Request-Id", hash.toLocal8Bit());
    request.setRawHeader("Authorization", authorizationHeader.toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkManager->post(request, data);
}

QJsonObject YandexDevice::getCapability(QString targetCapability)
{
    Secrets *secrets = Secrets::getInstance();

    QUrl deviceUrl = QUrl("https://api.iot.yandex.net/v1.0/devices/" + deviceId);
    QNetworkRequest request(deviceUrl);
    QString authorizationHeader = "Bearer " + secrets->get(OAUTH_TOKEN_NAME);

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Authorization", authorizationHeader.toLocal8Bit());

    QNetworkReply *reply = networkManager->get(request);

    temp = QJsonObject();

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();

            QJsonDocument document = QJsonDocument::fromJson(response);
            QJsonObject root = document.object();
            QJsonArray capabilities = root["capabilities"].toArray();

            foreach (QJsonValueRef ref, capabilities) {
                QJsonObject capability = ref.toObject();

                if (capability["type"] == targetCapability) {
                    temp = capability;
//                    qDebug() << "Before:" << temp;
                    break;
                }
            }
        } else {
//            qDebug() << "Error with device" << deviceId << "cant get capabilities!";
        }
    });

//    qDebug() << "After:" << temp;

    return temp;
}
