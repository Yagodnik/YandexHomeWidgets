#include "secrets.h"

Secrets::Secrets(): settings("ArtemYagodnik", "YandexLampTray") {
}

Secrets *Secrets::getInstance()
{
    static Secrets instance;

    QFile secrets(":/assets/secrets.json");

    if (!secrets.open(QIODevice::ReadOnly)) {
        qDebug() << "Cant open file with secrets!";
        exit(-1);
    }

    QString content = secrets.readAll();
    secrets.close();

    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject root = document.object();

    foreach(const QString& key, root.keys()) {
        QJsonValue value = root.value(key);

        instance.data.insert(key, value.toString());
    }

    QFile version(":/assets/version.txt");

    if (!version.open(QIODevice::ReadOnly)) {
        qDebug() << "Cant open file with secrets!";
        exit(-1);
    }

    instance.data.insert(APP_VERSION, version.readAll().trimmed());
    version.close();

    return &instance;
}

QString Secrets::get(QString key)
{
    if (data.contains(key))
        return data.value(key);
    else
        return settings.value(key).toString();
}

void Secrets::saveToSettings(QString key, QString value)
{
    settings.setValue(key, value);
}

void Secrets::clearValue(QString key)
{
    settings.remove(key);
}

int Secrets::appVersion()
{
    return data.value(APP_VERSION).toInt();
}

