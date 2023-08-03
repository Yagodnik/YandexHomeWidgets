#ifndef LAMPSLISTMODEL_H
#define LAMPSLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QDebug>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "yandex/yandexdevicedata.h"

class LampsListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString oauthToken MEMBER oauthToken WRITE setOAuthToken)
public:
    enum Roles {
        TextRole = Qt::UserRole + 1,
        IdRole
    };

    LampsListModel(QObject *parent = nullptr);
    ~LampsListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void reload();
    Q_INVOKABLE void setOAuthToken(QVariant text);

signals:
    void devicesLoaded(int count);

private:
    QList<YandexDeviceData*> lamps;
    QString oauthToken;
    QNetworkAccessManager *networkAccessManager;
};

#endif // LAMPSLISTMODEL_H
