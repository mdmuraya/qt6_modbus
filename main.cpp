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

    //engine.rootContext()->setContextProperty("_MainBackendHelper", &_MainBackendHelper);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    QQuickStyle::setStyle("Material");
    engine.loadFromModule("Qt6ModbusVFDController", "Main");

    return app.exec();
}

