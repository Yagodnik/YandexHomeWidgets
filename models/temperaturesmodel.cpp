#include "temperaturesmodel.h"

TemperaturesModel::TemperaturesModel(QObject *parent)
    : QAbstractListModel{parent}
{
    temperatures = new Temperatures();
}

TemperaturesModel::~TemperaturesModel()
{
    temperatures->deleteLater();
}

int TemperaturesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return temperatures->getTemperaturesCount();
}

QVariant TemperaturesModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case IdRole:
        return index.row();
    case TemperatureRole:
        return temperatures->getTemperature(index.row());
    case DisplayColor:
        return temperatures->getDisplayColor(index.row());
    }

    return QVariant();
}

QHash<int, QByteArray> TemperaturesModel::roleNames() const
{    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();

    roles[TemperatureRole] = "temperatureValue";
    roles[DisplayColor] = "displayColor";
    roles[IdRole] = "colorId";

    return roles;}

void TemperaturesModel::setLimits(int min, int max)
{
    qDebug() << "Min:" << min << "; Max:" << max;
}
