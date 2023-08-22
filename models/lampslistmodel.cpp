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
        return lamps.at(index.row())->id;
    case TextRole:
        return lamps.at(index.row())->name;
    case StateRole:
        return lamps.at(index.row())->state;
    case BrightnessRole:
        return lamps.at(index.row())->brightness;
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

void LampsListModel::add(QList<YandexLamp *> loadedLamps)
{
    lamps.clear();

    foreach (YandexLamp *lamp, loadedLamps) {
        YandexDeviceData *data = lamp->getDeviceData();

        lamps.append(data);
    }

    emit layoutChanged();
}

void LampsListModel::update(QString id, YandexLamp *lamp)
{
    for (int i = 0;i < lamps.length();i++) {
        YandexDeviceData *data = lamps.at(i);

        if (data->id == id) {
            lamps.replace(i, lamp->getDeviceData());
            emit layoutChanged();
        }
    }
}


