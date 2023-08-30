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

    YandexLamp *lamp = (YandexLamp*) devices->at(index.row());
    YandexDeviceData *data = lamp->getDeviceData();

    switch (role) {
    case IdRole:
        return data->id;
    case TextRole:
        return data->name;
    case StateRole:
        return data->state;
    case BrightnessRole:
        return data->brightness;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> LampsListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();

    roles[TextRole] = "deviceName";
    roles[IdRole] = "deviceId";
    roles[StateRole] = "deviceState";
    roles[BrightnessRole] = "deviceBrightness";

    return roles;
}

void LampsListModel::deviceAdded()
{
    emit layoutChanged();
}

void LampsListModel::devicesUpdated()
{
    YandexLamp *lamp = (YandexLamp*) devices->at(0);
    YandexDeviceData *data = lamp->getDeviceData();
    qDebug() <<  "Update received!" << data->state;

    emit layoutChanged();
}
