#ifndef LAMPSLISTMODEL_H
#define LAMPSLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QDebug>
#include <QStringList>
#include "yandex/yandexlamp.h"
#include "yandex/yandexdevicedata.h"
#include "yandex/yandexdevices.h"

class LampsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        TextRole = Qt::UserRole + 1,
        StateRole = Qt::UserRole + 2,
        BrightnessRole = Qt::UserRole + 3,
        IdRole
    };

    LampsListModel(QObject *parent = nullptr);
    ~LampsListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

private:
    YandexDevices *devices;

private slots:
    void deviceAdded();
    void devicesUpdated();
};

Q_DECLARE_METATYPE(LampsListModel)

#endif // LAMPSLISTMODEL_H
