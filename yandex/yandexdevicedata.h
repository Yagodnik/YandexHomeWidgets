#ifndef YANDEXDEVICEDATA_H
#define YANDEXDEVICEDATA_H

#include <QString>

typedef struct {
    QString id;
    QString name;
    bool state;
    int brightness;
} YandexDeviceData;

#endif // YANDEXDEVICEDATA_H
