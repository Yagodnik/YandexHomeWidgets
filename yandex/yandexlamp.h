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
    typedef enum {
        HSV, RGB, TEMPERATURES
    } ColorModel;

    explicit YandexLamp(QString deviceId,
                        QString deviceName);
    ~YandexLamp();

    YandexDeviceData *getDeviceData();
    void update();

    bool getState();
    int getBrightness();

    void setState(bool state);
    void setBrightness(int brightness);
    void setColor(QRgb color);
    void setTemperature(int temperature);
private:
    bool state;
    int brightness;
    ColorModel colorModel;

    QJsonObject generateRequest(QJsonObject action);
    QJsonObject generateAction(bool lampState);
    QJsonObject generateAction(int brightness);
    QJsonObject generateAction(QRgb color);

private slots:
    void gotCapability(QString capabilityName, QJsonObject capability);
};

#endif // YANDEXLAMP_H
