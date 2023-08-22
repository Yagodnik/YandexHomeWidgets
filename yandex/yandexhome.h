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
    Q_PROPERTY(QVariant devicesModel WRITE setModel)
public:
    explicit YandexHome(QObject *parent = nullptr);

    Q_INVOKABLE void loadDevices();
    Q_INVOKABLE void updateDevices();

    Q_INVOKABLE void setState(QString deviceId, bool state);
    Q_INVOKABLE void setBrightness(QString deviceId, int brightness);

    void setModel(QVariant model);

signals:
    void devicesLoaded(int result);
    void lampError(QString deviceId);

private:
    QList<YandexLamp*> lamps;
    QNetworkAccessManager *networkAccessManager;
    LampsListModel *model;

    YandexLamp *withId(QString id);
};

#endif // YANDEXHOME_H
