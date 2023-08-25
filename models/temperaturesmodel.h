#ifndef TEMPERATURESMODEL_H
#define TEMPERATURESMODEL_H

#include <QAbstractListModel>
#include "3rdparty/temperatures.h"

class TemperaturesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        TemperatureRole = Qt::UserRole + 1,
        DisplayColor = Qt::UserRole + 2,
        IdRole
    };

    explicit TemperaturesModel(QObject *parent = nullptr);
    ~TemperaturesModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    Temperatures *temperatures;
};

#endif // TEMPERATURESMODEL_H
