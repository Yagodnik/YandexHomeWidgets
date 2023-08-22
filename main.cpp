#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "models/lampslistmodel.h"
#include "3rdparty/colors.h"
#include <QtNetworkAuth>
#include <QDesktopServices>
#include "yandex/yandexoauth.h"
#include "yandex/yandexhome.h"
#include "yandex/yandexaccount.h"

// TODO: Fix bug with colors
// TODO: Ask for current lamp state when focusing
// TODO: Check for memory leaks
// TODO: Create base class for all yandex devices
// TODO: Add capabilities classes

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    YandexAccount account;
    YandexOAuth oauth;
    YandexHome home;
    Colors lampColors;
    LampsListModel lampsListModel;

    home.getAllDevices(QVariant());

    QObject::connect(&home, &YandexHome::devicesLoaded, [&home](int result) {
        home.reloadInfo();
    });

    return app.exec();

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("lampColors", &lampColors);
    context->setContextProperty("lampsListModel", &lampsListModel);
    context->setContextProperty("yandexHome", &home);
    context->setContextProperty("yandexOAuth", &oauth);
    context->setContextProperty("yandexAccount", &account);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
