#ifndef YANDEXHOME_H
#define YANDEXHOME_H

#include <QObject>
#include <QList>
#include "yandexlamp.h"

class YandexHome : public QObject
{
    Q_OBJECT
public:
    explicit YandexHome(QObject *parent = nullptr);

    Q_INVOKABLE void checkConnection();

    void getAllDevices();

signals:
    void connectionChecked(int result);

private:
    // YandexLamp -> YandexDevice
    QList<YandexLamp*> devices;
};

#endif // YANDEXHOME_H
