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

    bool isUpdated();
    bool isChanged();
    void markAsUpdated();
    void markAsUnupdated();

signals:
    void actionFinished();

protected:
    QString deviceId;
    QString deviceName;
    QNetworkAccessManager *networkManager;

    bool updated;
    bool haveChanges;

    void sendPostRequest(QByteArray data);
    void getFullInfo();
    void generateRequest(QJsonObject action);

signals:
    void infoReady(QJsonArray capabilities);
    void updateFinished(QString deviceId);
};

#endif // YANDEXDEVICE_H
