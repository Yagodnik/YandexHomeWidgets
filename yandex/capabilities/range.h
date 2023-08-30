#ifndef RANGE_H
#define RANGE_H

#include "basecapability.h"

class Range : public BaseCapability
{
public:
    Range();

    static QJsonObject generate(int value);
};

#endif // RANGE_H
