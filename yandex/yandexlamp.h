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
#include "yandexdevice.h"
#include "capabilities/onoff.h"
#include "capabilities/range.h"
#include "capabilities/colorsetting.h"

class YandexLamp : public YandexDevice
{
    Q_OBJECT
    Q_PROPERTY(QString deviceId MEMBER deviceId)
public:
    explicit YandexLamp(QString deviceId,
                        QString deviceName,
                        int tMin = 1500,
                        int tMax = 6500,
                        ColorModel colorModel = HSV);

    QJsonObject getDeviceData();
    void update();

    bool getState();
    int getBrightness();

    Q_INVOKABLE void setState(bool state);
    Q_INVOKABLE void setBrightness(int brightness);
    Q_INVOKABLE void setColor(QString color);
    Q_INVOKABLE void setTemperature(int temperature);
    Q_INVOKABLE int getMinTemperature();
    Q_INVOKABLE int getMaxTemperature();

private:
    int temperatureMin;
    int temperatureMax;
    ColorModel colorModel;
};

Q_DECLARE_METATYPE(YandexLamp)

#endif // YANDEXLAMP_H
