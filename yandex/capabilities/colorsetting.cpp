#include "colorsetting.h"

ColorSetting::ColorSetting()
{

}

QJsonObject ColorSetting::generate(QRgb targetColor, ColorModel colorModel)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.color_setting";

    QJsonObject state;
    QJsonObject color;

//    qDebug() << (QColor(targetColor).toRgb().red() << 16) + (QColor(targetColor).toRgb().green() << 8)  + QColor(targetColor).toRgb().blue();

    switch (colorModel) {
    case HSV: {
        state["instance"] = "hsv";
        QColor _color = QColor(targetColor).toHsv();

        color["h"] = (int) (_color.hue());
        color["s"] = (int) (_color.saturation() / 255.0 * 100);
        color["v"] = (int) (_color.value() / 255.0 * 100);

        state["value"] = color;

        break;
    } case RGB: {
        QColor _color = QColor(targetColor).toRgb();

        state["instance"] = "rgb";
        state["value"] = (_color.red() << 16) + (_color.green() << 8)  + _color.blue();

        break;
    } default:
        return QJsonObject();
    }

    action["state"] = state;

    return action;
}

QJsonObject ColorSetting::generate(int temperature)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.color_setting";

    QJsonObject state;

    state["instance"] = "temperature_k";
    state["value"] = temperature;

    action["state"] = state;

    return action;
}
