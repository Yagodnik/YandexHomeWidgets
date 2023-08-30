#ifndef YANDEXDEVICES_H
#define YANDEXDEVICES_H

#include <QString>
#include <QList>
#include "yandexdevice.h"

class YandexDevices: public QObject
{
    Q_OBJECT
public:
    static YandexDevices *getInstance();

    void add(YandexDevice *device);
    YandexDevice *at(int index);
    YandexDevice *withId(QString id);
    int count();
    bool isEmpty();
    void clear();
    void update();

signals:
    void deviceAdded();
    void devicesUpdated();

private:
    QList<YandexDevice*> devices;

    YandexDevices();
    YandexDevices(const YandexDevices&);
    YandexDevices& operator=(const YandexDevices&);

private slots:
    void onUpdateFinished(QString deviceId);
};

#endif // YANDEXDEVICES_H
