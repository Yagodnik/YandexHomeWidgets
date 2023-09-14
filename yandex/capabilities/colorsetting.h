#ifndef COLORSETTING_H
#define COLORSETTING_H

#include "basecapability.h"
#include <QRgb>
#include <QColor>
#include "../../3rdparty/constants.h"

class ColorSetting : public BaseCapability
{
public:
    ColorSetting();

    static QJsonObject generate(QRgb targetColor, ColorModel colorModel = HSV);
    static QJsonObject generate(int temperature);
};

#endif // COLORSETTING_H
