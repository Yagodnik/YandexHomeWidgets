#include "desktopfeatures.h"

DesktopFeatures::DesktopFeatures(QObject *parent)
    : QObject{parent}
{

}

QRect DesktopFeatures::getTaskbarPosition()
{
    QRect entireRect = QApplication::primaryScreen()->geometry();
    QRect availRect = QApplication::primaryScreen()->availableGeometry();

    QRegion availRgn(availRect);
    QRegion entireRgn(entireRect);
    QRect taskbar = entireRgn.subtracted(availRgn).boundingRect();

    return taskbar;
}
