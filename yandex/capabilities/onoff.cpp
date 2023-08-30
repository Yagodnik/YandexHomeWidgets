#include "onoff.h"

OnOff::OnOff(): BaseCapability()
{

}

QJsonObject OnOff::generate(bool value)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.on_off";

    QJsonObject state;

    state["instance"] = "on";
    state["value"] = value;

    action["state"] = state;

    return action;
}
