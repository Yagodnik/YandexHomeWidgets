#ifndef YANDEXSOCKET_H
#define YANDEXSOCKET_H

#include "yandexdevice.h"
#include "yandex/capabilities/onoff.h"

class YandexSocket : public YandexDevice
{
    Q_OBJECT
    Q_PROPERTY(QString deviceId MEMBER deviceId)
public:
    explicit YandexSocket(QString deviceId, QString deviceName);

    QJsonObject getDeviceData();

    bool getState();

    Q_INVOKABLE void setState(bool state);
};

#endif // YANDEXSOCKET_H
