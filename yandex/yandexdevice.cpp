#include "yandexdevice.h"
#include "qnetworkreply.h"

YandexDevice::YandexDevice(QString deviceId, QString deviceName, QObject *parent)
    : QObject{parent}
{
    this->deviceId = deviceId;
    this->deviceName = deviceName;
    updated = false;

    connect(this, &YandexDevice::infoReady, this, &YandexDevice::onInfoReady);
}

YandexDevice::~YandexDevice()
{
}

QString YandexDevice::getName()
{
    return deviceName;
}

QString YandexDevice::getId()
{
    return deviceId;
}

bool YandexDevice::isOnline()
{
    return deviceOnline;
}

void YandexDevice::update()
{
    getFullInfo();
}

bool YandexDevice::isUpdated()
{
    return updated;
}

bool YandexDevice::isChanged()
{
    return haveChanges;
}

void YandexDevice::markAsUpdated()
{
    updated = true;
}

void YandexDevice::markAsUnupdated()
{
    haveChanges = false;
    updated = false;
}

QString YandexDevice::getDeviceType()
{
    return deviceType;
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

    QNetworkReply *reply = networkManager.post(request, data);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            deviceOnline = true;
        } else {
            deviceOnline = false;
        }

        reply->deleteLater();

        emit actionFinished();
    });
}

void YandexDevice::getFullInfo()
{
    Secrets *secrets = Secrets::getInstance();

    QUrl deviceUrl = QUrl("https://api.iot.yandex.net/v1.0/devices/" + deviceId);
    QNetworkRequest request(deviceUrl);
    QString authorizationHeader = "Bearer " + secrets->get(OAUTH_TOKEN_NAME);

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Authorization", authorizationHeader.toLocal8Bit());

    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            deviceOnline = true;
            QByteArray response = reply->readAll();

            QJsonDocument document = QJsonDocument::fromJson(response);
            QJsonObject root = document.object();
            QJsonArray capabilities = root["capabilities"].toArray();

            emit infoReady(capabilities);
        } else if (reply->error() == QNetworkReply::HostNotFoundError ||
                   reply->error() == QNetworkReply::UnknownNetworkError){
            deviceOnline = false;
        }

        reply->deleteLater();
    });
}

void YandexDevice::generateRequest(QJsonObject action)
{
    QJsonObject baseRequest;

    QJsonArray actions;
    actions.append(action);

    QJsonArray devices;
    QJsonObject device;
    device["id"] = deviceId;
    device["actions"] = actions;

    devices.append(device);

    baseRequest["devices"] = devices;

    QJsonDocument document(baseRequest);
    sendPostRequest(document.toJson());
}

void YandexDevice::setType(QString type)
{
    deviceType = type;
}

void YandexDevice::addCapability(QString name, bool live)
{
    capabilities.insert(name, live);
}

void YandexDevice::onInfoReady(QJsonArray deviceCapabilities)
{
    foreach (QJsonValueRef ref, deviceCapabilities) {
        QJsonObject capability = ref.toObject();
        QString capabilityType = capability["type"].toString();
        QJsonObject state = capability["state"].toObject();
        QString capabilityInstance = state["instance"].toString();

        if (capabilities.value(capabilityType)) {
            QJsonObject state = capability["state"].toObject();

            if (values.value(capabilityInstance) != state["value"].toVariant())
                haveChanges = true;

            values[capabilityInstance] = state["value"].toVariant();
        }
    }

    emit updateFinished(getId());
}
