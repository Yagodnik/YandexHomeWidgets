#ifndef BASECAPABILITY_H
#define BASECAPABILITY_H

#include <QObject>
#include <QJsonObject>

class BaseCapability
{
public:
    explicit BaseCapability();

    static QJsonObject generate(QVariant value);
};

#endif // BASECAPABILITY_H
