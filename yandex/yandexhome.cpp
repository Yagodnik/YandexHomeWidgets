#include "yandexhome.h"

YandexHome::YandexHome(QObject *parent)
    : QObject{parent}
{
    networkAccessManager = new QNetworkAccessManager(this);
    devices = YandexDevices::getInstance();
    watcher = new YandexWatcher();

    watcher->pause();
}

YandexHome::~YandexHome()
{
    networkAccessManager->deleteLater();
    devices->deleteLater();
    watcher->deleteLater();
}

void YandexHome::clearDevices()
{
    devices->clear();
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

            clearDevices();

            foreach (QJsonValueRef ref, devices) {
                QJsonObject currentDevice = ref.toObject();
                QString deviceType = currentDevice["type"].toString();

                if (deviceType == "devices.types.light") {
                    // TODO: Move to class
                    QString lampId = currentDevice["id"].toString();
                    QString lampName = currentDevice["name"].toString();
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

                    YandexLamp *lamp = new YandexLamp(lampId,
                                                      lampName,
                                                      temperatureMin,
                                                      temperatureMax,
                                                      colorModel);

                    if (lamp == nullptr) {
                        qDebug() << "Cant create device" << lampName << ";" << lampId;
                        lamp->deleteLater();
                        continue;
                    }

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

        reply->deleteLater();
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

    watcher->pause();
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

int YandexHome::minTemperature(QString deviceId)
{
    return ((YandexLamp*) devices->withId(deviceId))->getMinTemperature();
}

int YandexHome::maxTemperature(QString deviceId)
{
    return ((YandexLamp*) devices->withId(deviceId))->getMaxTemperature();
}

void YandexHome::onActionFinished()
{
    watcher->resume();
}
