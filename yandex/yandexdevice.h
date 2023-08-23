#ifndef YANDEXDEVICE_H
#define YANDEXDEVICE_H

#include <QObject>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "3rdparty/secrets.h"
#include "3rdparty/constants.h"

class YandexDevice : public QObject
{
    Q_OBJECT
public:
    explicit YandexDevice(QString deviceId, QString deviceName, QObject *parent = nullptr);

    QString getName();
    QString getId();

    virtual void update() = 0;

protected:
    QString deviceId;
    QString deviceName;
    QNetworkAccessManager *networkManager;

    void sendPostRequest(QByteArray data);
    void getCapability(QString targetCapability);

signals:
    void getCapabilitySignal(QString capabilityName, QJsonObject capability);
};

#endif // YANDEXDEVICE_H
