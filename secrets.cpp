#include "secrets.h"

Secrets *Secrets::getInstance()
{
    static Secrets instance;

    QFile secrets(":/assets/secrets.json");

    if (!secrets.open(QIODevice::ReadOnly)) {
        qDebug() << "Cant open file with secrets!";
        return nullptr;
    }

    QString content = secrets.readAll();
    secrets.close();

    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject root = document.object();

    foreach(const QString& key, root.keys()) {
        QJsonValue value = root.value(key);

        instance.data.insert(key, value.toString());
    }

    return &instance;
}

QString Secrets::get(QString key)
{
    return data.value(key);
}
