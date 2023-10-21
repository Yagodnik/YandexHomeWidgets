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

private:
    QString repositoryName;
    QNetworkAccessManager networkManager;
    QFile targetFile;

    void checkUpdates();

    void downloadInstaller(QString url);
    bool checkHash(QString original, QString downloaded);

signals:
    void manifestLoaded(QByteArray content);
    void blockLoaded(QByteArray block);

private slots:
    void parseManifest(QByteArray content);
    void readyRead();
    void finished();
    void errorOccurred();
};

#endif // UPDATER_H
