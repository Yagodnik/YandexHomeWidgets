#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QProcess>
#include "3rdparty/secrets.h"

class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QString repositoryUrl, QObject *parent = nullptr);

    Q_INVOKABLE int getCurrentVersion();

signals:
    void updateAvaliable(QVariant data);
    void downloadProgress(int bytesReaded, int bytesTotal);

private:
    QString repositoryName;
    QNetworkAccessManager networkManager;
    QFile targetFile;

    void checkUpdates();

    void downloadInstaller(QString url);
    bool checkHash(QString original, QString downloaded);

    void copyApp(QString source, QString destination);

signals:
    void manifestLoaded(QByteArray content);
    void blockLoaded(QByteArray block);
    void readyForUpdate();

private slots:
    void parseManifest(QByteArray content);
    void readyRead();
    void finished();
    void networkErrorOccurred();
    void onReadyForUpdate();
};

#endif // UPDATER_H
