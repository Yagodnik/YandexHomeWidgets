#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "models/deviceslistmodel.h"
#include "models/colorsmodel.h"
#include "models/temperaturesmodel.h"
#include <QtNetworkAuth>
#include <QDesktopServices>
#include "yandex/yandexoauth.h"
#include "yandex/yandexhome.h"
#include "yandex/yandexaccount.h"
#include "3rdparty/desktopfeatures.h"
#include "3rdparty/updater.h"

// TODO: Fix seg fault when sending requests without internet

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    // I dont know what this key means but ok
    QGuiApplication app(argc, argv);

    if (!QGuiApplication::arguments().contains("-allow-several-instances")) {
        QSharedMemory shared("62d60669-bb94-4a94-88bb-b964890a7e04");
        if(!shared.create(512, QSharedMemory::ReadWrite)) {
            qDebug() << "Cant run several instances! (run with -allow-several-instances if you need)";
            exit(0);
        }
    }

    #ifdef Q_OS_WIN32
        QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.setValue("YandexHomeWidgets", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
        settings.sync();
    #endif

    #ifdef Q_OS_LINUX
        qWarning() << "Sorry guys, you should add program to autostart yourself... "
                      "But I think it is like everyday routine for you ¯\_(ツ)_/¯";
    #endif

    YandexAccount account;
    YandexOAuth oauth;
    ColorsModel colorModel;
    DesktopFeatures desktopFeatures;

    // TODO: Move to special thread
    Updater updater("Yagodnik/TestRepo");

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    qmlRegisterType<YandexHome>("Yandex", 1, 0, "YandexHome");
    qmlRegisterType<DevicesListModel>("Yandex", 1, 0, "DevicesModel");
    qmlRegisterType<TemperaturesModel>("Yandex", 1, 0, "TemperaturesModel");

    context->setContextProperty("updater", &updater);
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
