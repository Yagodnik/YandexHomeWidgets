#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "models/lampslistmodel.h"
#include "models/colorsmodel.h"
#include "models/temperaturesmodel.h"
#include <QtNetworkAuth>
#include <QDesktopServices>
#include "yandex/yandexoauth.h"
#include "yandex/yandexhome.h"
#include "yandex/yandexaccount.h"
#include "3rdparty/desktopfeatures.h"

// TODO: Check for memory leaks
// TODO: Refactor yandex home class.
// Just withId method and then working only with what it will return
// TODO: Check if port is free in YandexOAuth class

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
    qmlRegisterType<TemperaturesModel>("Yandex", 1, 0, "TemperaturesModel");

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
