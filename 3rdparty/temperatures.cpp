#include "temperatures.h"

Temperatures::Temperatures(QObject *parent)
    : QObject{parent}
{
    QFile temperaturesFile(":/assets/temperatures.json");

    if (!temperaturesFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Cant read temperatures file!";
        temperaturesFile.close();
        return;
    }

    QString content = temperaturesFile.readAll();
    temperaturesFile.close();

    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());

    QJsonArray root = document.array();

    foreach(QJsonValueRef ref, root) {
        QJsonObject element = ref.toObject();
        QPair<int, QColor> pair;

        pair.first = element["temperature_k"].toInt();
        pair.second = QColor(
            element["r"].toInt(),
            element["g"].toInt(),
            element["b"].toInt()
        );

        temperatures.push_back(pair);
    }
}

QString Temperatures::getDisplayColor(int index)
{
    if (index > getTemperaturesCount())
        return "000";

    return temperatures.at(index).second.name();
}

int Temperatures::getTemperature(int index)
{
    if (index > getTemperaturesCount())
        return 0;

    return temperatures.at(index).first;
}

int Temperatures::getTemperaturesCount()
{
    return temperatures.count();
}
