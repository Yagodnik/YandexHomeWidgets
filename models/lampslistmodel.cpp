#include "lampslistmodel.h"

LampsListModel::LampsListModel(QObject *parent)
{
    Q_UNUSED(parent);

    networkAccessManager = new QNetworkAccessManager();
}

LampsListModel::~LampsListModel()
{
    lamps.clear();
    networkAccessManager->deleteLater();
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
    lamps.clear();

    QString requestUrl = "https://api.iot.yandex.net/v1.0/user/info";
    QString authorizationHeader = QString("Bearer " + oauthToken.trimmed());
    QNetworkRequest request(requestUrl);

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setRawHeader("Authorization", authorizationHeader.toLocal8Bit());

    QNetworkReply *reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();

            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
            QJsonObject jsonObject = jsonResponse.object();

            QJsonArray devices = jsonObject["devices"].toArray();

            for (int i = 0;i < devices.count();i++) {
                QJsonObject currentDevice = devices.at(i).toObject();
                QString deviceType = currentDevice["type"].toString();

                if (deviceType == "devices.types.light") {
                    QString lampId = currentDevice["id"].toString();
                    QString lampName = currentDevice["name"].toString();

                    YandexDeviceData *lamp = new YandexDeviceData(lampId, lampName);

                    lamps.append(lamp);
                }
            }

            if (lamps.isEmpty())
                qDebug() << "No yandex lamps!";

            emit devicesLoaded(lamps.length());
            emit layoutChanged();
        } else {
            qDebug() << "Error occured during getting devices:" << reply->errorString();
        }
    });
}

void LampsListModel::setOAuthToken(QVariant text)
{
    oauthToken = text.toString();
}
