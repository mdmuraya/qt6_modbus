#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include "Qt6Modbus_RTU_TCP.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Qt6Modbus_RTU_TCP _Qt6Modbus_RTU_TCP;

    engine.rootContext()->setContextProperty("_Qt6Modbus_RTU_TCP", &_Qt6Modbus_RTU_TCP);

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

