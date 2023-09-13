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
#include "yandex/yandexdevices.h"
#include "yandex/yandexwatcher.h"

class YandexHome : public QObject
{
    Q_OBJECT
public:
    explicit YandexHome(QObject *parent = nullptr);
    ~YandexHome();

    Q_INVOKABLE void clearDevices();
    Q_INVOKABLE void loadDevices();
    Q_INVOKABLE void setWatcherState(bool state);

    Q_INVOKABLE void setState(QString deviceId, bool state);
    Q_INVOKABLE void setBrightness(QString deviceId, int brightness);
    Q_INVOKABLE void setColor(QString deviceId, QString color);
    Q_INVOKABLE void setTemperature(QString deviceId, int temperature);

    Q_INVOKABLE void getSupportedColors(){}

signals:
    void devicesLoaded(int result);
    void lampError(QString deviceId);
    void devicesUpdated();

private:
    QNetworkAccessManager *networkAccessManager;
    YandexDevices *devices;
    YandexWatcher *watcher;

private slots:
    void onActionFinished();
};

#endif // YANDEXHOME_H
