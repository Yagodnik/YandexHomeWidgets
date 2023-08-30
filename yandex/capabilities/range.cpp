#include "range.h"

Range::Range()
{

}

QJsonObject Range::generate(int value)
{
    QJsonObject action;
    action["type"] = "devices.capabilities.range";

    QJsonObject state;

    state["instance"] = "brightness";
    state["value"] = value;

    action["state"] = state;

    return action;
}
