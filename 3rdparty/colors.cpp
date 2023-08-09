#include "colors.h"

Colors::Colors(QObject *parent) : QObject(parent)
{
    QFile colorsFile(":/assets/colors.json");

    if (!colorsFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Cant read colors file!";
        colorsFile.close();
        return;
    }

    QString content = colorsFile.readAll();
    colorsFile.close();

    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());

    QJsonArray root = document.array();

    foreach(QJsonValueRef colorRef, root) {
        QJsonObject color = colorRef.toObject();

        colors.push_back(QColor(
            color["r"].toInteger(),
            color["g"].toInteger(),
            color["b"].toInteger()
        ));
    }
}

QString Colors::getColorHex(int index)
{
    if (index >= colors.length())
        return "000";

    return colors.at(index).name();
}

QRgb Colors::getColorRgb(int index)
{
    if (index >= colors.length())
        return QRgb();

    return colors.at(index).rgb();
}

int Colors::getColorsCount()
{
    return colors.length();
}
