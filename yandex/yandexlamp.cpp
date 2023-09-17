#include "yandexlamp.h"

YandexLamp::YandexLamp(QString deviceId,
                       QString deviceName,
                       int tMin,
                       int tMax,
                       ColorModel colorModel) : YandexDevice(deviceId, deviceName, nullptr)
{
    temperatureMin = tMin;
    temperatureMax = tMax;
    this->colorModel = colorModel;
    deviceType = "devices.types.light";

    addCapability("devices.capabilities.on_off", true);
    addCapability("devices.capabilities.range", true);
}

QJsonObject YandexLamp::getDeviceData()
{
    QJsonObject data;

    data["id"] = deviceId;
    data["name"] = deviceName;
    data["state"] = getState();
    data["brightness"] = getBrightness();
    data["online"] = isOnline();

    return data;
}

void YandexLamp::update()
{
    getFullInfo();
}

bool YandexLamp::getState()
{
    return values["on"].toBool();
}

int YandexLamp::getBrightness()
{
    return values["brightness"].toInt();
}

void YandexLamp::setState(bool state)
{
    generateRequest(OnOff::generate(state));
}

void YandexLamp::setBrightness(int brightness)
{
    if (brightness == 0)
        brightness = 1;

    generateRequest(Range::generate(brightness));
}

void YandexLamp::setColor(QString color)
{
    generateRequest(ColorSetting::generate(QColor(color).rgb()));
}

void YandexLamp::setTemperature(int temperature)
{
    generateRequest(ColorSetting::generate(temperature));
}

int YandexLamp::getMinTemperature()
{
    return temperatureMin;
}

int YandexLamp::getMaxTemperature()
{
    return temperatureMax;
}
