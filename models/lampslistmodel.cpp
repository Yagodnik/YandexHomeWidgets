#include "lampslistmodel.h"

LampsListModel::LampsListModel(QObject *parent)
{
    Q_UNUSED(parent);

    devices = YandexDevices::getInstance();

    connect(devices, &::YandexDevices::deviceAdded, this, &LampsListModel::deviceAdded);
    connect(devices, &::YandexDevices::devicesUpdated, this, &LampsListModel::devicesUpdated);
}

LampsListModel::~LampsListModel()
{
    devices->clear();
}

int LampsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return devices->count();
}

QVariant LampsListModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> LampsListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();

    roles[TypeRole] = "deviceType";
    roles[DataRole] = "deviceData";

    return roles;
}

void LampsListModel::deviceAdded()
{
    emit layoutChanged();
}

void LampsListModel::devicesUpdated()
{
    emit dataChanged(index(0), index(devices->count() - 1));
}
