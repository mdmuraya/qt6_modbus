#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include "MainBackendHelper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //MainBackendHelper _MainBackendHelper;

    //engine.rootContext()->setContextProperty("_Qt6Modbus_RTU_TCP", &_Qt6Modbus_RTU_TCP);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    QQuickStyle::setStyle("Material");
    engine.loadFromModule("Qt6Modbus_RTU_TCP", "Main");

    return app.exec();
}

