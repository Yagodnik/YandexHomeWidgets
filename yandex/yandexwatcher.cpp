#include "yandexwatcher.h"

YandexWatcher::YandexWatcher(QObject *parent): QObject(parent) {
    timer.setInterval(300);
    devices = YandexDevices::getInstance();
    blocked = false;

    // MEMORY LEAK HERE!
//    connect(&timer, &QTimer::timeout, this, &YandexWatcher::onTriggered);
}

void YandexWatcher::pause()
{
    blocked = true;
    timer.stop();
}

void YandexWatcher::resume()
{
    timer.start();
    blocked = false;
}

bool YandexWatcher::isBlocked()
{
    return blocked;
}

void YandexWatcher::onTriggered()
{
    for (int i = 0;i < devices->count();i++) {
        YandexDevice *device = devices->at(i);
        YandexLamp *lamp = (YandexLamp*) device;

        if (isBlocked())
            return;

        lamp->update();
    }
}
