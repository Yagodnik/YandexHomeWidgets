#include "yandexsocket.h"

YandexSocket::YandexSocket(QString deviceId, QString deviceName)
    : YandexDevice(deviceId, deviceName, nullptr)
{
    setType("devices.types.socket");
    addCapability("devices.capabilities.on_off", true);
}

QJsonObject YandexSocket::getDeviceData()
{
    QJsonObject data;

    data["id"] = deviceId;
    data["name"] = deviceName.length() <= 10 ? deviceName : deviceName.mid(0, 10) + "...";
    data["fullName"] = deviceName;
    data["state"] = getState();
    data["online"] = isOnline();

    return data;
}

bool YandexSocket::getState()
{
    return values["on"].toBool();
}

void YandexSocket::setState(bool state)
{
    generateRequest(OnOff::generate(state));
}
