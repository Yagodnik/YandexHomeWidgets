#ifndef YANDEXWRAPPER_H
#define YANDEXWRAPPER_H

#include <QObject>
#include <QDebug>
#include <QtNetworkAuth>
#include <QByteArray>
#include <QDesktopServices>

class YandexWrapper : public QObject
{
    Q_OBJECT
public:
    explicit YandexWrapper(QObject *parent = nullptr);

    void grant();

private:
    QOAuth2AuthorizationCodeFlow oauth2;
};

#endif // YANDEXWRAPPER_H
