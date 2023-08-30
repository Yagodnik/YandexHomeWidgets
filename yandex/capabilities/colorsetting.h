#ifndef COLORSETTING_H
#define COLORSETTING_H

#include "basecapability.h"
#include <QRgb>
#include <QColor>

class ColorSetting : public BaseCapability
{
public:
    ColorSetting();

    static QJsonObject generate(QRgb color);
    static QJsonObject generate(int temperature);
};

#endif // COLORSETTING_H
