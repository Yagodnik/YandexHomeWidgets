#include "yandexdevices.h"

YandexDevices::YandexDevices() {}

YandexDevices *YandexDevices::getInstance()
{
    static YandexDevices instance;

    return &instance;
}

void YandexDevices::add(YandexDevice *device)
{
    if (device == nullptr)
        return;

    devices.append(device);
    emit deviceAdded();
}

YandexDevice *YandexDevices::at(int index)
{
    if (index > count())
        return nullptr;

    return devices.at(index);
}

YandexDevice *YandexDevices::withId(QString id)
{
    foreach(YandexDevice *device, devices) {
        if (device == nullptr)
            continue;

        if (device->getId() == id)
            return device;
    }

    return nullptr;
}

int YandexDevices::count()
{
    return devices.count();
}

bool YandexDevices::isEmpty()
{
    return count() == 0;
}

void YandexDevices::clear()
{
    devices.clear();
}

void YandexDevices::update()
{
    emit devicesUpdated();
}

