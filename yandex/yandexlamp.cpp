#include "yandexlamp.h"

YandexLamp::YandexLamp(QString deviceId,
                       QString deviceName) : YandexDevice(deviceId, deviceName, nullptr)
{
    test = 70;
}

YandexLamp::~YandexLamp()
{
    networkManager->deleteLater();
}

YandexDeviceData *YandexLamp::getDeviceData()
{
    return new YandexDeviceData {
        .id =  deviceId,
        .name = deviceName,
        .state = getState(),
        .brightness = getBrightness()
    };
}

bool YandexLamp::getState()
{
    QJsonObject capability = getCapability("devices.capabilities.on_off");

    if (capability.empty())
        return false;

    QJsonObject state = capability["state"].toObject();
    return state["value"].toBool();
}

int YandexLamp::getBrightness()
{
    return test;
}

void YandexLamp::setState(bool state)
{
    QJsonObject action = generateAction(state);
    QJsonObject baseRequest = generateRequest(action);

    QJsonDocument document(baseRequest);
    sendPostRequest(document.toJson());
}

void YandexLamp::setBrightness(int brightness)
{
    QJsonObject action = generateAction(brightness);
    QJsonObject baseRequest = generateRequest(action);

    test = 100;

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

QJsonObject YandexLamp::generateAction(bool lampState)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.on_off";

    QJsonObject state;

    state["instance"] = "on";
    state["value"] = lampState;

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
