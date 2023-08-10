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

    Q_INVOKABLE void getAllDevices(QVariant model);

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
