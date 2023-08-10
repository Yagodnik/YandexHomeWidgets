#include "lampslistmodel.h"

LampsListModel::LampsListModel(QObject *parent)
{
    Q_UNUSED(parent);
}

LampsListModel::~LampsListModel()
{
    lamps.clear();
}

int LampsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return lamps.count();
}

QVariant LampsListModel::data(const QModelIndex &index, int role) const
{
    if (lamps.isEmpty())
        return QVariant();

    switch (role) {
    case IdRole:
        return lamps.at(index.row())->getId();
    case TextRole:
        return lamps.at(index.row())->getName();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> LampsListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[TextRole] = "deviceName";
    roles[IdRole] = "deviceId";

    return roles;
}

void LampsListModel::reload()
{

}

void LampsListModel::add(QList<YandexLamp *> loadedLamps)
{
    lamps.clear();

    foreach (YandexLamp *lamp, loadedLamps) {
        YandexDeviceData *data = lamp->getDeviceData();

        lamps.append(data);
    }

    emit layoutChanged();
}

