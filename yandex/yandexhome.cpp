#include "yandexhome.h"

YandexHome::YandexHome(QObject *parent)
    : QObject{parent}
{
    networkAccessManager = new QNetworkAccessManager(this);
    devices = YandexDevices::getInstance();
    watcher = new YandexWatcher();

    watcher->pause();
}

void YandexHome::loadDevices()
{
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

            foreach (QJsonValueRef ref, devices) {
                QJsonObject currentDevice = ref.toObject();
                QString deviceType = currentDevice["type"].toString();

                if (deviceType == "devices.types.light") {
                    QString lampId = currentDevice["id"].toString();
                    QString lampName = currentDevice["name"].toString();

                    YandexLamp *lamp = new YandexLamp(lampId, lampName);

                    connect(lamp, &YandexLamp::actionFinished,
                            this, &YandexHome::onActionFinished);

                    this->devices->add(lamp);
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
    });
}

void YandexHome::setWatcherState(bool state)
{
    if (state) watcher->resume();
    else watcher->pause();
}

void YandexHome::setState(QString deviceId, bool state)
{    
    YandexLamp *lamp = (YandexLamp*) devices->withId(deviceId);

    if (lamp == nullptr) {
        emit lampError(deviceId);
        return;
    }

    watcher->pause();
    lamp->setState(state);
}

void YandexHome::setBrightness(QString deviceId, int brightness)
{
    YandexLamp *lamp = (YandexLamp*) devices->withId(deviceId);

    if (lamp == nullptr) {
        emit lampError(deviceId);
        return;
    }

    if (brightness == 0)
        brightness = 1;

//    watcher->pause();
    lamp->setBrightness(brightness);
}

void YandexHome::setColor(QString deviceId, QString color)
{
    YandexLamp *lamp = (YandexLamp*) devices->withId(deviceId);

    if (lamp == nullptr) {
        emit lampError(deviceId);
        return;
    }

//    watcher->pause();
    QRgb _color = QColor(color).rgb();
    lamp->setColor(_color);
}

void YandexHome::setTemperature(QString deviceId, int temperature)
{

    YandexLamp *lamp = (YandexLamp*) devices->withId(deviceId);

    if (lamp == nullptr) {
        emit lampError(deviceId);
        return;
    }

//    watcher->pause();
    lamp->setTemperature(temperature);
}

void YandexHome::onActionFinished()
{
    watcher->resume();
}
