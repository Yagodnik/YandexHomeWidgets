#include "yandexhome.h"

YandexHome::YandexHome(QObject *parent)
    : QObject{parent}
{
    devices = YandexDevices::getInstance();
    watcher = new YandexWatcher(this);

    watcher->pause();
}

YandexHome::~YandexHome()
{
    devices->deleteLater();
}

void YandexHome::clearDevices()
{
    devices->clear();
}

void YandexHome::loadDevices()
{
    Secrets *secrets = Secrets::getInstance();

    QString requestUrl = "https://api.iot.yandex.net/v1.0/user/info";
    QString authorizationHeader = "Bearer " + secrets->get(OAUTH_TOKEN_NAME);
    QNetworkRequest request(requestUrl);

//    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("User-Agent", "YandexHomeWidgets");
    request.setRawHeader("Authorization", authorizationHeader.toLocal8Bit());

    QNetworkReply *reply = networkAccessManager.get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        QByteArray response = reply->readAll();

        qDebug() << QString(response);

        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
            QJsonObject jsonObject = jsonResponse.object();
            QJsonArray devices = jsonObject["devices"].toArray();

            clearDevices();

            foreach (QJsonValueRef ref, devices) {
                QJsonObject currentDevice = ref.toObject();
                QString deviceType = currentDevice["type"].toString();

                QString _deviceId = currentDevice["id"].toString();
                QString _deviceName = currentDevice["name"].toString();

                if (deviceType == "devices.types.light") {
                    // TODO: Move to class
                    int temperatureMin = 0, temperatureMax = 0;
                    ColorModel colorModel = DEFAULT;

                    QJsonArray capabilities = currentDevice["capabilities"].toArray();
                    foreach (QJsonValueRef ref, capabilities) {
                        QJsonObject capability = ref.toObject();
                        QJsonObject parameters = capability["parameters"].toObject();

                        if (capability["type"] == "devices.capabilities.color_setting") {
                            QJsonObject temperatures = parameters["temperature_k"].toObject();
                            QString colorModelString = parameters["color_model"].toString();

                            temperatureMin = temperatures["min"].toInt();
                            temperatureMax = temperatures["max"].toInt();

                            if (colorModelString == "hsv") colorModel = HSV;
                            else if (colorModelString == "rgb") colorModel = RGB;
                        }
                    }

                    YandexLamp *lamp = new YandexLamp(_deviceId,
                                                      _deviceName,
                                                      temperatureMin,
                                                      temperatureMax,
                                                      colorModel);

                    if (lamp == nullptr) {
                        qDebug() << "Cant create device" << _deviceName << ";" << _deviceId;
                        continue;
                    }

                    connect(lamp, &YandexLamp::actionFinished, this, &YandexHome::onActionFinished);

                    this->devices->add(lamp);
                } else if (deviceType == "devices.types.socket") {
                    YandexSocket *socket = new YandexSocket(_deviceId, _deviceName);

                    if (socket == nullptr) {
                        qDebug() << "Cant create device" << _deviceName << ";" << _deviceId;
                        continue;
                    }

                    connect(socket, &YandexLamp::actionFinished, this, &YandexHome::onActionFinished);

                    this->devices->add(socket);
                }
            }

            if (devices.isEmpty()) {
                qDebug() << "No yandex devices!";
            }

            emit devicesLoaded(devices.count());
        } else {
            qDebug() << "Error occured during getting devices:" << reply->errorString();

            emit devicesLoaded(-1);
        }

        reply->deleteLater();
    });
}

void YandexHome::setWatcherState(bool state)
{
    if (state) watcher->resume();
    else watcher->pause();
}

YandexDevice *YandexHome::withId(QString id)
{
    return devices->withId(id);
}

void YandexHome::onActionFinished()
{
    watcher->resume();
}
