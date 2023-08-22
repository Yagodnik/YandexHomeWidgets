#ifndef YANDEXHOME_H
#define YANDEXHOME_H

#include <QObject>
#include <QList>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "yandex/yandexlamp.h"
#include "models/lampslistmodel.h"

class YandexHome : public QObject
{
    Q_OBJECT
public:
    explicit YandexHome(QObject *parent = nullptr);

    // Sends api request for all devices
    Q_INVOKABLE void getAllDevices(QVariant model);

    // Reloads info about devices that are already saved in the list (lamps)
    Q_INVOKABLE void reloadInfo();

    Q_INVOKABLE void on(QString deviceId);
    Q_INVOKABLE void off(QString deviceId);
    Q_INVOKABLE void setBrightness(QString deviceId, int brightness);

signals:
    void devicesLoaded(int result);
    void lampError(QString deviceId);

private:
    QList<YandexLamp*> lamps;
    QNetworkAccessManager *networkAccessManager;

    YandexLamp *withId(QString id);
};

#endif // YANDEXHOME_H
