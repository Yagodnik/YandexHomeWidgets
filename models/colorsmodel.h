#ifndef COLORSMODEL_H
#define COLORSMODEL_H

#include <QAbstractListModel>
#include "3rdparty/colors.h"

class ColorsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        ColorRole = Qt::UserRole + 1,
        IdRole
    };

    explicit ColorsModel(QObject *parent = nullptr);
    ~ColorsModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    Colors *colors;
};

#endif // COLORSMODEL_H
