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

    virtual void reload() = 0;

protected:
    QString deviceId;
    QString deviceName;
    QNetworkAccessManager *networkManager;

    void sendPostRequest(QByteArray data);
    QJsonObject getCapability(QString targetCapability);

    QJsonObject temp;
};

#endif // YANDEXDEVICE_H
