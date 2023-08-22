#ifndef LAMPSLISTMODEL_H
#define LAMPSLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QDebug>
#include <QStringList>
#include "yandex/yandexlamp.h"
#include "yandex/yandexdevicedata.h"

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

    void add(QList<YandexLamp*> loadedLamps);
    void update(QString id, YandexLamp *lamp);

private:
    QList<YandexDeviceData*> lamps;
};

Q_DECLARE_METATYPE(LampsListModel)

#endif // LAMPSLISTMODEL_H
