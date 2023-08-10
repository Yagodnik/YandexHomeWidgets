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

typedef enum {
    ON, OFF, UNKNOWN
} LampState;

class YandexLamp : public QObject
{
    Q_OBJECT
public:
    explicit YandexLamp(QString deviceId,
                        QString deviceName,
                        QObject *parent = nullptr);
    ~YandexLamp();

    LampState getState();
    QString getId();
    YandexDeviceData *getDeviceData();

    Q_INVOKABLE void on();
    Q_INVOKABLE void off();
    Q_INVOKABLE void setBrightness(int brightness);
    Q_INVOKABLE void setColor(QRgb color);

private:
    LampState lampState;
    QString deviceId;
    QString deviceName;
    QNetworkAccessManager *networkManager;

    QJsonObject generateRequest(QJsonObject action);
    QJsonObject generateAction(LampState lampState);
    QJsonObject generateAction(int brightness);
    QJsonObject generateAction(QRgb color);

    void sendPostRequest(QByteArray data);

private slots:
    void onReply(QNetworkReply *reply);
};

#endif // YANDEXLAMP_H
