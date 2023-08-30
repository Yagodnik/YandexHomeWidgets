#ifndef ONOFF_H
#define ONOFF_H

#include "basecapability.h"

class OnOff : public BaseCapability
{
public:
    OnOff();

    static QJsonObject generate(bool value);
};

#endif // ONOFF_H
