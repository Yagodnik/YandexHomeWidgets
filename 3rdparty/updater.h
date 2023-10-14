#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QString repositoryUrl, QObject *parent = nullptr);

signals:
    void updateAvaliable(QVariant data);

private:
    QString repositoryUrl;
    QNetworkAccessManager networkManager;

    void loadManifest();

signals:
    void manifestLoaded(QByteArray content);

private slots:
    void parseManifest(QByteArray content);
};

#endif // UPDATER_H
