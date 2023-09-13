#include "yandexlamp.h"

YandexLamp::YandexLamp(QString deviceId,
                       QString deviceName) : YandexDevice(deviceId, deviceName, nullptr)
{
    // ASK BASIC INFO SUCH AS COLOR MODEL!

    connect(this, &YandexDevice::infoReady, this, &YandexLamp::onInfoReady);
}

YandexLamp::~YandexLamp()
{
    networkManager->deleteLater();
}

YandexDeviceData YandexLamp::getDeviceData()
{
    return YandexDeviceData {
        .id =  deviceId,
        .name = deviceName,
        .state = getState(),
        .brightness = getBrightness(),
        .online = isOnline()
    };
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

void YandexLamp::setColor(QRgb color)
{
    generateRequest(ColorSetting::generate(color));
}

void YandexLamp::setTemperature(int temperature)
{
    generateRequest(ColorSetting::generate(temperature));
}

void YandexLamp::onInfoReady(QJsonArray capabilities)
{
    foreach (QJsonValueRef ref, capabilities) {
        QJsonObject capability = ref.toObject();

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
