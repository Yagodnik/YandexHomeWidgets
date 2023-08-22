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

class YandexLamp : public YandexDevice
{
public:
    explicit YandexLamp(QString deviceId,
                        QString deviceName);
    ~YandexLamp();

    YandexDeviceData *getDeviceData();

    bool getState();
    int getBrightness();

    void setState(bool state);
    void setBrightness(int brightness);
    void setColor(QRgb color);

    int test;
private:
    QJsonObject generateRequest(QJsonObject action);
    QJsonObject generateAction(bool lampState);
    QJsonObject generateAction(int brightness);
    QJsonObject generateAction(QRgb color);


    // YandexDevice interface
public:
    void reload() {

    }
};

#endif // YANDEXLAMP_H
