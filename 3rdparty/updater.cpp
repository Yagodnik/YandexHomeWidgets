#include "updater.h"

Updater::Updater(QString repositoryName, QObject *parent)
    : QObject{parent}
{
    this->repositoryName = repositoryName;

    checkUpdates();

    connect(this, &Updater::manifestLoaded, this, &Updater::parseManifest);
}

void Updater::checkUpdates()
{
    QUrl url = QUrl("https://raw.githubusercontent.com/" + repositoryName + "/main/manifest.json");
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit manifestLoaded(reply->readAll());
        } else {
            qDebug() << "Cant get manifest file!";
        }

        reply->deleteLater();
    });
}

void Updater::downloadInstaller(QString url)
{
    qDebug() << "Downloading" << url;

    QDir tempDirectory(QGuiApplication::applicationDirPath() + "/temp");
    if (!tempDirectory.exists())
        tempDirectory.mkpath(".");

    // TODO: Check formats

    targetFile.setFileName(QGuiApplication::applicationDirPath() + "/temp/installer.exe");
    if (!targetFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Cant create file for downloading!";
        return;
    }

    QUrl requestUrl = QUrl(url);
    QNetworkRequest request(requestUrl);
    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::readyRead, this, &Updater::readyRead);
    connect(reply, &QNetworkReply::finished, this, &Updater::finished);
    connect(reply, &QNetworkReply::errorOccurred, this, &Updater::errorOccurred);

    reply->waitForReadyRead(1000);
}

bool Updater::checkHash(QString original, QString downloaded)
{
    return true;
}

int Updater::getCurrentVersion()
{
    Secrets *secrets = Secrets::getInstance();
    return secrets->appVersion();
}

void Updater::parseManifest(QByteArray content)
{
    QJsonDocument document = QJsonDocument::fromJson(content);
    QJsonArray versions = document.array();

    Secrets *secrets = Secrets::getInstance();
    int currentVersion = secrets->appVersion();

#ifdef Q_OS_WIN32
    qDebug() << versions.last()["win-installer"].toString();

    downloadInstaller("https://github.com/" + repositoryName + "/releases/download/" + versions.last()["win-installer"].toString());
#endif

    if (currentVersion < versions.last()["version"].toString().toInt())
        emit updateAvaliable(versions.last().toVariant());
}

void Updater::readyRead()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    qDebug() << "Received" << reply->size();

    targetFile.write(reply->readAll());
}

void Updater::finished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    targetFile.write(reply->readAll());

    qDebug() << "Received" << reply->size();
    qDebug() << "Downloading finished!";

    reply->deleteLater();

    targetFile.close();

    QProcess process;

    process.start("F:\\installer.exe");

    if (!process.waitForStarted()) {
        qDebug() << "Cant start installer!";
        return;
    }

    process.waitForFinished(-1);

    // TODO: Add different checks and etc.

    qDebug() << process.exitStatus();

    // TODO: Restart if some problems

    targetFile.remove();
}

void Updater::errorOccurred()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    qDebug() << "Error occurred during downloading file:" << reply->errorString() << reply->error();

    reply->deleteLater();

    targetFile.close();
    targetFile.remove();
}
