#include "Qt6Modbus_RTU_TCP.h"
#include <QDebug>


Qt6Modbus_RTU_TCP::Qt6Modbus_RTU_TCP(QObject *parent)
    : QObject{parent}
{
    qDebug() << "Qt6Modbus_RTU_TCP::Qt6Modbus_RTU_TCP()";
}

void Qt6Modbus_RTU_TCP::onConnectToVFD(QString port)
{
    qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port;
}

void Qt6Modbus_RTU_TCP::onClearVFDFaults()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onClearVFDFaults()";
}

void Qt6Modbus_RTU_TCP::onStartMotorFWD()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onStartMotorFWD()";
}

void Qt6Modbus_RTU_TCP::onStartMotorREV()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onStartMotorREV()";
}

void Qt6Modbus_RTU_TCP::onStopMotor()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onStopMotor()";
}


