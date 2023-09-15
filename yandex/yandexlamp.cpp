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

    connect(this, &YandexDevice::infoReady, this, &YandexLamp::onInfoReady);
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
    return state;
}

int YandexLamp::getBrightness()
{
    return brightness;
}

void YandexLamp::setState(bool state)
{
    generateRequest(OnOff::generate(state));
}

void YandexLamp::setBrightness(int brightness)
{
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

void YandexLamp::onInfoReady(QJsonArray capabilities)
{
    foreach (QJsonValueRef ref, capabilities) {
        QJsonObject capability = ref.toObject();

        // TODO: Create a generelisation method for Yandex Device
        if (capability["type"] == "devices.capabilities.on_off") {
            QJsonObject state = capability["state"].toObject();

            if (QVariant(this->state) != state["value"].toVariant())
                haveChanges = true;

            this->state = state["value"].toBool();
        }

        if (capability["type"] == "devices.capabilities.range") {
            QJsonObject state = capability["state"].toObject();

            if (QVariant(this->brightness) != state["value"].toVariant())
                haveChanges = true;

            this->brightness = state["value"].toInt();
        }
    }

    emit updateFinished(getId());
}
