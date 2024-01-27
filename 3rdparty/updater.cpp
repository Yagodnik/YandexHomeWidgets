#include "updater.h"

Updater::Updater(QString repositoryName, QObject *parent)
    : QObject{parent}
{
    this->repositoryName = repositoryName;
    installerProcess = new QProcess(this);

    checkUpdates();

    connect(this, &Updater::manifestLoaded, this, &Updater::parseManifest);

    connect(installerProcess, &QProcess::readyReadStandardOutput, [script=installerProcess](){
        qDebug() << "[EXEC] DATA: " << script->readAll();
    });

    connect(installerProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [script = installerProcess](int exitCode, QProcess::ExitStatus exitStatus)
    {
        qDebug() << "[EXEC] FINISHED: " << exitCode << exitStatus;
        if(script->bytesAvailable() > 0)
            qDebug() << "[EXEC] buffered DATA:" << script->readAll();
    });

    connect(installerProcess, &QProcess::errorOccurred, [script=installerProcess](QProcess::ProcessError error){
        qDebug() << "[EXEC] error on execution: " << error << script->errorString();
    });
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

    QDir tempDirectory(QDir::tempPath() + "/yandexhomewidgets/");
    if (!tempDirectory.exists())
        tempDirectory.mkpath(".");

    // TODO: Check formats

    targetFile.setFileName(QDir::tempPath() + "/yandexhomewidgets/" + "installer.exe");
    if (!targetFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Cant create file for downloading!";
        return;
    }

    QUrl requestUrl = QUrl(url);
    QNetworkRequest request(requestUrl);
    QNetworkReply *reply = networkManager.get(request);

    connect(reply, &QNetworkReply::readyRead, this, &Updater::readyRead);
    connect(reply, &QNetworkReply::finished, this, &Updater::finished);
    connect(reply, &QNetworkReply::errorOccurred, this, &Updater::networkErrorOccurred);
    connect(this, &Updater::readyForUpdate, this, &Updater::onReadyForUpdate);

    reply->waitForReadyRead(1000);
}

bool Updater::checkHash(QString original, QString downloaded)
{
    return true;
}

void Updater::copyApp(QString source, QString destination)
{
    QDir rootDirectory(QGuiApplication::applicationDirPath());

    qDebug() << "Copying from" << source << "to" << destination;

    foreach (QString name, rootDirectory.entryList()) {
        if (name == "temp") {
            qDebug() << "skipping" << name;
            continue;
        }

        QString sourcePath = source + name;
        QString destinationPath = destination + name;

        qDebug() << sourcePath << "->" << destinationPath;

        if (QFile::exists(destinationPath))
            QFile::remove(destinationPath);

        bool ret = QFile::copy(sourcePath, destinationPath);

        if (!ret) {
            qDebug() << "Cant copy" << name;
        } else {
            QFile::remove(sourcePath);
        }
    }

    qDebug() << "Copying from" << source << "to" << destination << "finished!";
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

    copyApp(QGuiApplication::applicationDirPath() + "/",
            QDir::tempPath() + "/yandexhomewidgets/");

    QGuiApplication::exit(0);

    emit readyForUpdate();
}

void Updater::networkErrorOccurred()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    qDebug() << "Error occurred during downloading file:" << reply->errorString() << reply->error();

    reply->deleteLater();

    targetFile.close();
    targetFile.remove();
}

void Updater::onReadyForUpdate()
{
    qDebug() << "Staring updater at" << QGuiApplication::applicationDirPath() + "/";

    QStringList arguments;
    arguments << "-t" << QGuiApplication::applicationDirPath();
    arguments << "--accept-licenses";
    arguments << "--confirm-command";
    arguments << "install";

    installerProcess->setProgram(QDir::tempPath() + "/yandexhomewidgets/" + "installer.exe");
    installerProcess->setArguments(arguments);
    installerProcess->setProcessChannelMode(QProcess::MergedChannels);
    installerProcess->start();


//    targetFile.remove();

    // TODO: Copy files to one level up
//    copyApp(QDir::tempPath() + "/yandexhomewidgets/",
//            QGuiApplication::applicationDirPath() + "/");

//    QDir tempDirectory(QDir::tempPath() + "/yandexhomewidgets/");
//    tempDirectory.removeRecursively();
}
