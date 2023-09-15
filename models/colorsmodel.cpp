#include "colorsmodel.h"

ColorsModel::ColorsModel(QObject *parent)
    : QAbstractListModel{parent}
{
    colors = new Colors(this);
}

ColorsModel::~ColorsModel()
{
    colors->deleteLater();
}

int ColorsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return colors->getColorsCount();
}

QVariant ColorsModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case IdRole:
        return index.row();
    case ColorRole:
        return colors->getColorHex(index.row());
    }

    return QVariant();
}

QHash<int, QByteArray> ColorsModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();

    roles[ColorRole] = "colorValue";
    roles[IdRole] = "colorId";

    return roles;
}
