#include "colorsetting.h"

ColorSetting::ColorSetting()
{

}

QJsonObject ColorSetting::generate(QRgb color)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.color_setting";

    QJsonObject state;

    state["instance"] = "hsv";

    QJsonObject hsv;

    QColor _color = QColor(color);

    _color = _color.toHsv();

    hsv["h"] = (int) (_color.hue());
    hsv["s"] = (int) (_color.saturation() / 255.0 * 100);
    hsv["v"] = (int) (_color.value() / 255.0 * 100);

    state["value"] = hsv;

    qDebug() << state["value"];

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
