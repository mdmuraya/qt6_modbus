#include "Qt6Modbus_RTU_TCP.h"
#include <QDebug>
#include <QModbusRtuSerialClient>
#include <QModbusTcpClient>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVariantList>

Qt6Modbus_RTU_TCP::Qt6Modbus_RTU_TCP(QObject *parent)
    : QObject{parent}
{
    qDebug() << "Qt6Modbus_RTU_TCP::Qt6Modbus_RTU_TCP()";
}

void Qt6Modbus_RTU_TCP::onConnectToVFD(QString port)
{
    qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port;

    QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
    qDebug() << "Available ports count:" << serialPortInfos.count();

    for (const QSerialPortInfo &info : serialPortInfos) {
        qDebug() << "Port Name:" << info.portName();
        qDebug() << "System Location:" << info.systemLocation();
        qDebug() << "Description:" << info.description();
        qDebug() << "Manufacturer:" << info.manufacturer();
        qDebug() << "Vendor ID:" << info.vendorIdentifier();
        qDebug() << "Product ID:" << info.productIdentifier();
        qDebug() << "-----------------------------------";
    }
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



QVariantList  Qt6Modbus_RTU_TCP::getAvailableCOMPorts()
{
    QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

    QVariantList  availableCOMPorts;

    for (const QSerialPortInfo &info : serialPortInfos)
    {
        QVariantMap  availableCOMPort;

        //availableCOMPort.insert("uniqueId", info.portName());
        //availableCOMPort.insert("displayText", info.portName() + " (" + info.description() + ")");

        //QVariantMap availableCOMPort;
        availableCOMPort["uniqueId"] = info.portName();
        availableCOMPort["displayText"] = info.portName() + " (" + info.description() + ")";


        availableCOMPorts.append(availableCOMPort);

    }

    qDebug() << availableCOMPorts;

    return availableCOMPorts;

}

Qt6Modbus_RTU_TCP::~Qt6Modbus_RTU_TCP()
{
    qDebug() << "Qt6Modbus_RTU_TCP::~Qt6Modbus_RTU_TCP()";
}


