#ifndef YANDEXDEVICEDATA_H
#define YANDEXDEVICEDATA_H

#include <QString>

class YandexDeviceData
{
public:
    explicit YandexDeviceData(const QString id,
                              const QString name);

    QString getId();
    QString getName();

private:
    const QString id;
    const QString name;
};


#endif // YANDEXDEVICEDATA_H
