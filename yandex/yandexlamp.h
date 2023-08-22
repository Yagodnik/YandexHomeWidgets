#ifndef YANDEXLAMP_H
#define YANDEXLAMP_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QColor>
#include <QRgb>
#include "3rdparty/constants.h"
#include "3rdparty/secrets.h"
#include "yandex/yandexdevicedata.h"
#include "yandexdevice.h"

typedef enum {
    ON, OFF, UNKNOWN
} LampState;

class YandexLamp : public YandexDevice
{
public:
    explicit YandexLamp(QString deviceId,
                        QString deviceName);
    ~YandexLamp();

    YandexDeviceData *getDeviceData();
    QString getId();

    LampState getState();
    int getBrightness();

    Q_INVOKABLE void on();
    Q_INVOKABLE void off();
    Q_INVOKABLE void setBrightness(int brightness);
    Q_INVOKABLE void setColor(QRgb color);

private:
    LampState lampState;

    QJsonObject generateRequest(QJsonObject action);
    QJsonObject generateAction(LampState lampState);
    QJsonObject generateAction(int brightness);
    QJsonObject generateAction(QRgb color);
};

#endif // YANDEXLAMP_H
