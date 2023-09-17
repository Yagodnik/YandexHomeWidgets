#ifndef YANDEXDEVICE_H
#define YANDEXDEVICE_H

#include <QObject>
#include <QDebug>
#include <QMap>
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
    ~YandexDevice();

    QString getName();
    QString getId();
    bool isOnline();

    virtual QJsonObject getDeviceData() = 0;
    virtual void update() = 0;

    bool isUpdated();
    bool isChanged();
    void markAsUpdated();
    void markAsUnupdated();

    QString getDeviceType();

signals:
    void actionFinished();

protected:
    QString deviceType;
    QString deviceId;
    QString deviceName;
    bool deviceOnline;
    bool haveChanges;
    bool updated;

    QMap<QString, QVariant> values;
    QMap<QString, bool> capabilities;

    QNetworkAccessManager networkManager;    

    void sendPostRequest(QByteArray data);
    void getFullInfo();
    void generateRequest(QJsonObject action);

    void addCapability(QString name, bool live);

signals:
    void infoReady(QJsonArray capabilities);
    void updateFinished(QString deviceId);

protected slots:
    void onInfoReady(QJsonArray deviceCapabilities);
};

#endif // YANDEXDEVICE_H
