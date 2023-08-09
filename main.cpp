#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "yandex/yandexlamp.h"
#include "models/lampslistmodel.h"
#include "3rdparty/colors.h"
#include <QtNetworkAuth>
#include <QDesktopServices>
#include "yandex/yandexoauth.h"
#include "yandex/yandexhome.h"

// TODO: Fix bug with colors
// TODO: Add OAuth2
// TODO: Make choosing several lamps
// TODO: Settings
// TODO: Ask for current lamp state when focusing
// TODO: Add messages when no internet connection

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    YandexOAuth oauth;
    YandexHome home;
    YandexLamp lamp("9435ff12-0bef-453e-8f85-1c2898c56013", "");
    Colors lampColors;
    LampsListModel lampsListModel;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("lamp", &lamp);
    context->setContextProperty("lampColors", &lampColors);
    context->setContextProperty("lampsListModel", &lampsListModel);
    context->setContextProperty("yandexHome", &home);
    context->setContextProperty("yandexOAuth", &oauth);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
