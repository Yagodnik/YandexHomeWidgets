#ifndef TEMPERATURES_H
#define TEMPERATURES_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QColor>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class Temperatures : public QObject
{
    Q_OBJECT
public:
    explicit Temperatures(QObject *parent = nullptr);

    QString getDisplayColor(int index);
    int getTemperature(int index);
    int getTemperaturesCount();
    void configure(int min, int max);

private:
    QList<QPair<int, QColor>> temperatures;
};

#endif // TEMPERATURES_H
