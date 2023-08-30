#ifndef YANDEXWATCHER_H
#define YANDEXWATCHER_H

#include <QObject>
#include <QTimer>
#include "yandexdevices.h"
#include "yandex/yandexlamp.h"

class YandexWatcher: public QObject
{
    Q_OBJECT
public:
    YandexWatcher(QObject *parent=nullptr);

    void pause();
    void resume();
    bool isBlocked();

private:
    bool blocked;
    QTimer timer;
    YandexDevices *devices;

private slots:
    void onTriggered();
};

#endif // YANDEXWATCHER_H
