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

    modbusDevice = std::make_unique<QModbusRtuSerialClient>();

    //modbusDevice = new QModbusRtuSerialClient(this);

    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, port);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::Parity::EvenParity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::BaudRate::Baud9600);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::DataBits::Data8);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::StopBits::OneStop);

        modbusDevice->setTimeout(10000);
        modbusDevice->setNumberOfRetries(3);

        if (!modbusDevice->connectDevice()) {
            //statusBar()->showMessage(tr("Connect failed: %1").arg(modbusDevice->errorString()), 5000);
            qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port + " FAILED";
        } else {
            //ui->actionConnect->setEnabled(false);
            //ui->actionDisconnect->setEnabled(true);
            qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port + " SUCCESS";
        }

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
    qDebug() << "Available ports count:" << serialPortInfos.count();

    QVariantList  availableCOMPorts;

    for (const QSerialPortInfo &info : serialPortInfos)
    {
        qDebug() << "Port Name:" << info.portName();
        qDebug() << "System Location:" << info.systemLocation();
        qDebug() << "Description:" << info.description();
        qDebug() << "Manufacturer:" << info.manufacturer();
        qDebug() << "Vendor ID:" << info.vendorIdentifier();
        qDebug() << "Product ID:" << info.productIdentifier();
        qDebug() << "-----------------------------------";

        QVariantMap  availableCOMPort;

        availableCOMPort["uniqueId"] = info.portName();
        availableCOMPort["displayText"] = info.portName() + " (" + info.manufacturer() + " - " + info.description() + ")";

        availableCOMPorts.append(availableCOMPort);
    }
    //qDebug() << availableCOMPorts;

    return availableCOMPorts;

}

Qt6Modbus_RTU_TCP::~Qt6Modbus_RTU_TCP()
{
    qDebug() << "Qt6Modbus_RTU_TCP::~Qt6Modbus_RTU_TCP()";
}


