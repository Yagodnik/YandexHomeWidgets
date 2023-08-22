#include "yandexhome.h"

YandexHome::YandexHome(QObject *parent)
    : QObject{parent}
{
    networkAccessManager = new QNetworkAccessManager(this);
}

void YandexHome::getAllDevices(QVariant model)
{
    LampsListModel* lampsModel = nullptr;

    if (model.canConvert<LampsListModel*>())
        lampsModel = qvariant_cast<LampsListModel*>(model);

    Secrets *secrets = Secrets::getInstance();

    QString requestUrl = "https://api.iot.yandex.net/v1.0/user/info";
    QString authorizationHeader = QString("Bearer " + secrets->get(OAUTH_TOKEN_NAME));
    QNetworkRequest request(requestUrl);

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Authorization", authorizationHeader.toLocal8Bit());

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();

            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
            QJsonObject jsonObject = jsonResponse.object();

            QJsonArray devices = jsonObject["devices"].toArray();

            for (int i = 0;i < devices.count();i++) {
                QJsonObject currentDevice = devices.at(i).toObject();
                QString deviceType = currentDevice["type"].toString();

                if (deviceType == "devices.types.light") {
                    QString lampId = currentDevice["id"].toString();
                    QString lampName = currentDevice["name"].toString();

                    YandexLamp *lamp = new YandexLamp(lampId, lampName);

                    lamps.append(lamp);
                }
            }

            if (devices.isEmpty()) {
                qDebug() << "No yandex devices!";
            }

            if (lampsModel != nullptr) {
                lampsModel->add(lamps);
            }

            // Pass devices to
            emit devicesLoaded(lamps.length());
        } else {
            qDebug() << "Error occured during getting devices:" << reply->errorString();

            emit devicesLoaded(-1);
        }
    });
}

void YandexHome::reloadInfo()
{
    foreach (YandexLamp *lamp, lamps) {
//        qDebug() << lamp->getId();

        lamp->getState();
    }
}

void YandexHome::on(QString deviceId)
{
    YandexLamp *lamp = withId(deviceId);
    if (lamp == nullptr) {
        emit lampError(deviceId);
        return;
    }

    lamp->on();
}

void YandexHome::off(QString deviceId)
{
    YandexLamp *lamp = withId(deviceId);
    if (lamp == nullptr) {
        emit lampError(deviceId);
        return;
    }

    lamp->off();
}

void YandexHome::setBrightness(QString deviceId, int brightness)
{
    YandexLamp *lamp = withId(deviceId);
    if (lamp == nullptr) {
        emit lampError(deviceId);
        return;
    }

    lamp->setBrightness(brightness);
}

YandexLamp *YandexHome::withId(QString id)
{
    foreach (YandexLamp *lamp, lamps) {
        if (lamp->getId() == id)
            return lamp;
    }

    return nullptr;
}
