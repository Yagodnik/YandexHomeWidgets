#include "yandexdevicedata.h"

YandexDeviceData::YandexDeviceData(
    const QString id,
    const QString name
) : id(id), name(name)
{

}

QString YandexDeviceData::getId()
{
    return id;
}

QString YandexDeviceData::getName()
{
    return name;
}
