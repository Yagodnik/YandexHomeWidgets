#ifndef DESKTOPFEATURES_H
#define DESKTOPFEATURES_H

#include <QObject>
#include <QApplication>
#include <QScreen>
#include <QRect>

class DesktopFeatures : public QObject
{
    Q_OBJECT
public:
    explicit DesktopFeatures(QObject *parent = nullptr);

    Q_INVOKABLE QRect getTaskbarPosition();
};

#endif // DESKTOPFEATURES_H
