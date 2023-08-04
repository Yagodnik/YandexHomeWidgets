#ifndef SECRETS_H
#define SECRETS_H

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class Secrets
{
public:
    static Secrets *getInstance();

    QString get(QString key);

private:
    QMap<QString, QString> data;

    Secrets() {}
    Secrets( const Secrets& );
    Secrets& operator=( Secrets& );
};

#endif // SECRETS_H
