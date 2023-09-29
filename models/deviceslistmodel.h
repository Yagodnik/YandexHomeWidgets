#ifndef DEVICESLISTMODEL_H
#define DEVICESLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QDebug>
#include <QStringList>
#include "yandex/yandexlamp.h"
#include "yandex/yandexdevicedata.h"
#include "yandex/yandexdevices.h"

class DevicesListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        TypeRole = Qt::UserRole + 1,
        DataRole = Qt::UserRole + 2
    };

    DevicesListModel(QObject *parent = nullptr);
    ~DevicesListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

private:
    YandexDevices *devices;

private slots:
    void deviceAdded();
    void devicesUpdated();
};

Q_DECLARE_METATYPE(DevicesListModel)

#endif // DEVICESLISTMODEL_H
