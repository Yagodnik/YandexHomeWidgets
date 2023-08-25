#include "yandexlamp.h"

YandexLamp::YandexLamp(QString deviceId,
                       QString deviceName) : YandexDevice(deviceId, deviceName, nullptr)
{
    // ASK BASIC INFO SUCH AS COLOR MODEL!

    connect(this, &YandexLamp::getCapabilitySignal, this, &YandexLamp::gotCapability);
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

void YandexLamp::update()
{
    getCapability("devices.capabilities.on_off");
}

bool YandexLamp::getState()
{
    return state;
}

int YandexLamp::getBrightness()
{
    return brightness;
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

void YandexLamp::setTemperature(int temperature)
{

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

    QColor _color = QColor(color);

    qDebug() << _color;
    qDebug() << _color.red() << _color.green() << _color.blue();
    _color = _color.toHsv();
    qDebug() << (int) _color.hue() << (int) (_color.saturation() / 255.0 * 100) << (int) (_color.value() / 255.0 * 100);

    hsv["h"] = (int) (_color.hue());
    hsv["s"] = (int) (_color.saturation() / 255.0 * 100);
    hsv["v"] = (int) (_color.value() / 255.0 * 100);

    state["value"] = hsv;

    qDebug() << state["value"];

    action["state"] = state;

    return action;
}

void YandexLamp::gotCapability(QString capabilityName, QJsonObject capability)
{
    if (capabilityName == "devices.capabilities.on_off") {
        if (capability.empty())
            return;

        QJsonObject state = capability["state"].toObject();
        this->state = state["value"].toBool();
    }
}
