#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "models/lampslistmodel.h"
#include "models/colorsmodel.h"
#include <QtNetworkAuth>
#include <QDesktopServices>
#include "yandex/yandexoauth.h"
#include "yandex/yandexhome.h"
#include "yandex/yandexaccount.h"
#include "3rdparty/desktopfeatures.h"

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
    ColorsModel colorModel;
    DesktopFeatures desktopFeatures;

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();

    qmlRegisterType<YandexHome>("Yandex", 1, 0, "YandexHome");
    qmlRegisterType<LampsListModel>("Yandex", 1, 0, "DevicesModel");

    context->setContextProperty("colorModel", &colorModel);
    context->setContextProperty("yandexOAuth", &oauth);
    context->setContextProperty("yandexAccount", &account);
    context->setContextProperty("desktopFeatures", &desktopFeatures);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
