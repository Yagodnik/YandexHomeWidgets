#include "yandexhome.h"

YandexHome::YandexHome(QObject *parent)
    : QObject{parent}
{

}

void YandexHome::checkConnection()
{
    emit connectionChecked(0);
}
