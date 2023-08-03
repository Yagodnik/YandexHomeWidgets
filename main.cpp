#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "yandex/yandexlamp.h"
#include "models/lampslistmodel.h"
#include "colors.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    YandexLamp lamp("9435ff12-0bef-453e-8f85-1c2898c56013", "y0_AgAAAABoWWAXAAkYVAAAAADbapjdlX9c2HyXS-60YHmLVZJj8AhQmtM");
    Colors lampColors;
    LampsListModel lampsListModel;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("lamp", &lamp);
    context->setContextProperty("lampColors", &lampColors);
    context->setContextProperty("lampsListModel", &lampsListModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
