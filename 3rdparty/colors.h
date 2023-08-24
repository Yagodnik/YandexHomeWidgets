#ifndef COLORS_H
#define COLORS_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QColor>
#include <QDebug>
#include <QRgb>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class Colors : public QObject
{
    Q_OBJECT
public:
    explicit Colors(QObject *parent = nullptr);

    QString getColorHex(int index);
    QRgb getColorRgb(int index);
    int getColorsCount();

private:
    QList<QColor> colors;
};

#endif // COLORS_H
