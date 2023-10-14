#include "updater.h"

Updater::Updater(QString repositoryUrl, QObject *parent)
    : QObject{parent}
{
    this->repositoryUrl = repositoryUrl;

    loadManifest();

    connect(this, &Updater::manifestLoaded, this, &Updater::parseManifest);
}

void Updater::loadManifest()
{
    QUrl url = QUrl(repositoryUrl + "manifest.json");
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

void Updater::parseManifest(QByteArray content)
{
    QJsonDocument document = QJsonDocument::fromJson(content);
    QJsonArray versions = document.array();

    // Get current version

    foreach (QJsonValueRef ref, versions) {
        QJsonObject version = ref.toObject();

        qDebug() << version["version"] << version["description"];
    }

    emit updateAvaliable(versions.last().toVariant());
}
