#include "deviceslistmodel.h"

DevicesListModel::DevicesListModel(QObject *parent)
{
    Q_UNUSED(parent);

    devices = YandexDevices::getInstance();

    connect(devices, &::YandexDevices::deviceAdded, this, &DevicesListModel::deviceAdded);
    connect(devices, &::YandexDevices::devicesUpdated, this, &DevicesListModel::devicesUpdated);
}

DevicesListModel::~DevicesListModel()
{
    devices->clear();
}

int DevicesListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return devices->count();
}

QVariant DevicesListModel::data(const QModelIndex &index, int role) const
{
    if (devices->isEmpty())
        return QVariant();

    YandexDevice *device = devices->at(index.row());

    switch (role) {
    case TypeRole:
        return device->getDeviceType();
    case DataRole:
        return device->getDeviceData();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DevicesListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();

    roles[TypeRole] = "deviceType";
    roles[DataRole] = "deviceData";

    return roles;
}

void DevicesListModel::deviceAdded()
{
    emit layoutChanged();
}

void DevicesListModel::devicesUpdated()
{
    emit dataChanged(index(0), index(devices->count() - 1));
}
