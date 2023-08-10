#include "yandexlamp.h"

YandexLamp::YandexLamp(QString deviceId,
                       QString deviceName,
                       QObject *parent) : QObject(parent)
{
    this->deviceId = deviceId;
    this->deviceName = deviceName;
    this->lampState = UNKNOWN;

    networkManager = new QNetworkAccessManager(this);

    connect(networkManager, &QNetworkAccessManager::finished, this, &YandexLamp::onReply);
}

YandexLamp::~YandexLamp()
{
    networkManager->deleteLater();
}

LampState YandexLamp::getState()
{
    Secrets *secrets = Secrets::getInstance();

    QUrl deviceUrl = QUrl("https://api.iot.yandex.net/v1.0/devices/" + deviceId);
    QNetworkRequest request(deviceUrl);
    QString authorizationHeader = "Bearer " + secrets->get(OAUTH_TOKEN_NAME);

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Authorization", authorizationHeader.toLocal8Bit());

    QNetworkReply *reply = networkManager->get(request);

    Q_UNUSED(reply);

    return UNKNOWN;
}

QString YandexLamp::getId()
{
    return deviceId;
}

YandexDeviceData *YandexLamp::getDeviceData()
{
    return new YandexDeviceData(
        deviceId, deviceName
    );
}

void YandexLamp::on()
{
    QJsonObject action = generateAction(LampState::ON);
    QJsonObject baseRequest = generateRequest(action);

    QJsonDocument document(baseRequest);
    sendPostRequest(document.toJson());
}

void YandexLamp::off()
{
    QJsonObject action = generateAction(LampState::OFF);
    QJsonObject baseRequest = generateRequest(action);

    QJsonDocument document(baseRequest);
    sendPostRequest(document.toJson());
}

void YandexLamp::setBrightness(int brightness)
{
    QJsonObject action = generateAction(brightness);
    QJsonObject baseRequest = generateRequest(action);

    QJsonDocument document(baseRequest);
    sendPostRequest(document.toJson());
}

void YandexLamp::setColor(QRgb color)
{
    QJsonObject action = generateAction(color);
    QJsonObject baseRequest = generateRequest(action);

    qDebug() << baseRequest;

    QJsonDocument document(baseRequest);
    sendPostRequest(document.toJson());
}

QJsonObject YandexLamp::generateRequest(QJsonObject action)
{
    QJsonObject root;

    QJsonArray actions;
    actions.append(action);

    QJsonArray devices;
    QJsonObject device;
    device["id"] = deviceId;
    device["actions"] = actions;

    devices.append(device);

    root["devices"] = devices;

    return root;
}

QJsonObject YandexLamp::generateAction(LampState lampState)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.on_off";

    QJsonObject state;

    if (lampState == ON) {
        state["instance"] = "on";
        state["value"] = true;
    } else if (lampState == OFF) {
        state["instance"] = "on";
        state["value"] = false;
    } else {
        qDebug() << "Error";
        return QJsonObject();
    }

    action["state"] = state;

    return action;
}

QJsonObject YandexLamp::generateAction(int brightness)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.range";

    QJsonObject state;

    state["instance"] = "brightness";
    state["value"] = brightness;

    action["state"] = state;

    return action;
}

QJsonObject YandexLamp::generateAction(QRgb color)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.color_setting";

    QJsonObject state;

    state["instance"] = "hsv";

    QJsonObject hsv;

    qDebug() << "RGB Color" << QColor::fromRgb(color).toRgb();

    QColor hsvColor = QColor(color).toHsv();

    qDebug() << "HSV Color" << hsvColor;

    hsv["h"] = hsvColor.hue();
    hsv["s"] = (int) (hsvColor.saturation() / 255.0 * 100);
    hsv["v"] = (int) (hsvColor.value() / 255.0 * 100);

    state["value"] = hsv;

    qDebug() << state["value"];

    action["state"] = state;

    return action;
}

void YandexLamp::sendPostRequest(QByteArray data)
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

void YandexLamp::onReply(QNetworkReply *reply) {
    if(reply->error() == QNetworkReply::NoError) {
        QString content = reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(content.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

    } else {
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}
