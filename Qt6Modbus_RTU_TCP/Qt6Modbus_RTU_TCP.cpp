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

    if(modbusDevice == nullptr)
    {
        modbusDevice = new QModbusRtuSerialClient(this);
    }

    //modbusDevice = new QModbusRtuSerialClient(this);

    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, port);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::EvenParity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);

        modbusDevice->setTimeout(10000);
        modbusDevice->setNumberOfRetries(3);

        // Connect to signals to handle connection status and errors
        connect(modbusDevice, &QModbusDevice::stateChanged, this, [&](QModbusDevice::State state){
            qDebug() << "State changed:" << state;
        });

        connect(modbusDevice, &QModbusDevice::errorOccurred, this, [&](QModbusDevice::Error error){
            if (error == QModbusDevice::TimeoutError) {
                qDebug() << "Modbus Timeout Error occurred:" << modbusDevice->errorString();
            }
        });


        if (!modbusDevice->connectDevice()) {
            //statusBar()->showMessage(tr("Connect failed: %1").arg(modbusDevice->errorString()), 5000);
            qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port + " FAILED";
        } else {
            //ui->actionConnect->setEnabled(false);
            //ui->actionDisconnect->setEnabled(true);
            qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port + " SUCCESS";

            if (modbusDevice->state() == QModbusDevice::ConnectedState)
            {
                QModbusDataUnit readHoldingRegisters(QModbusDataUnit::HoldingRegisters, 0, 10);
                int modbusDeviceId = 45;

                //QModbusDataUnit ReadUnit(QModbusDataUnit::HoldingRegisters, 0, 10);

                if (auto *reply = modbusDevice->sendReadRequest(readHoldingRegisters, modbusDeviceId))
                {
                    if (!reply->isFinished())
                    {
                        connect(reply, &QModbusReply::finished, this, [this, reply]()
                            {
                                auto reply_1 =  qobject_cast<QModbusReply*>(sender());
                                if (!reply_1) return;

                                if (reply_1->error() == QModbusDevice::NoError)
                                {
                                    qDebug() << "Data read sucessfully";
                                    //statusBar()->showMessage("Data read sucessfully");

                                    const QModbusDataUnit units = reply_1->result();
                                    //ui->listWidget_Holding_Data->clear();
                                    for (int i = 0 ; i < units.valueCount() ; i++)
                                    {
                                        QString entry = "Address : " + QString::number(units.startAddress() + i) + " Values : " + QString::number(units.value(i), 16) + " | " + QString::number(units.value(i));
                                        //ui->listWidget_Holding_Data->addItem(Entry);
                                        qDebug() << "Data read sucessfully: " + entry;
                                    }
                                }
                                else
                                {
                                    qDebug() << "Data read failed";
                                   // statusBar()->showMessage("Data read failed : " + reply_1->errorString());
                                }
                            reply->deleteLater(); // Clean up the reply object
                        });
                    }
                }


            }

        }

    }
}

void Qt6Modbus_RTU_TCP::onClearVFDFaults()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onClearVFDFaults()";

    if (modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int modbusDeviceId = 45;
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(8); // Clear VFD Faults

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = modbusDevice->sendWriteRequest(writeHoldingRegisters, modbusDeviceId))
        {
            if (!reply->isFinished())
            {
                connect(reply, &QModbusReply::finished, this, [this, reply]()
                {
                    if (reply->error() == QModbusDevice::NoError)
                    {
                        qDebug() << "Data is write sucessfully";
                        //statusBar()->showMessage("Data is write sucessfully");
                    }
                    else
                    {
                        qDebug() << "Data is write failed";
                        //statusBar()->showMessage("Data is write failed : " + reply->errorString());
                    }
                    reply->deleteLater(); // Clean up the reply object
                });
            }
        }
    }
}

void Qt6Modbus_RTU_TCP::onStartMotorFWD()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onStartMotorFWD()";

    if (modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int modbusDeviceId = 45;
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(18); // Start Motor FWD

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = modbusDevice->sendWriteRequest(writeHoldingRegisters, modbusDeviceId))
        {
            if (!reply->isFinished())
            {
                connect(reply, &QModbusReply::finished, this, [this, reply]()
                {
                    if (reply->error() == QModbusDevice::NoError)
                    {
                        qDebug() << "Data is write sucessfully";
                        //statusBar()->showMessage("Data is write sucessfully");
                    }
                    else
                    {
                        qDebug() << "Data is write failed";
                        //statusBar()->showMessage("Data is write failed : " + reply->errorString());
                    }
                    reply->deleteLater(); // Clean up the reply object
                });
            }
        }
    }
}

void Qt6Modbus_RTU_TCP::onStartMotorREV()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onStartMotorREV()";

    if (modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int modbusDeviceId = 45;
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(34); // Start Motor REV

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = modbusDevice->sendWriteRequest(writeHoldingRegisters, modbusDeviceId))
        {
            if (!reply->isFinished())
            {
                connect(reply, &QModbusReply::finished, this, [this, reply]()
                {
                    if (reply->error() == QModbusDevice::NoError)
                    {
                        qDebug() << "Data is write sucessfully";
                        //statusBar()->showMessage("Data is write sucessfully");
                    }
                    else
                    {
                        qDebug() << "Data is write failed";
                        //statusBar()->showMessage("Data is write failed : " + reply->errorString());
                    }
                    reply->deleteLater(); // Clean up the reply object
                });
            }
        }
    }
}

void Qt6Modbus_RTU_TCP::onStopMotor()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onStopMotor()";

    if (modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int modbusDeviceId = 45;
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(1); // Staop Motor

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = modbusDevice->sendWriteRequest(writeHoldingRegisters, modbusDeviceId))
        {
            if (!reply->isFinished())
            {
                connect(reply, &QModbusReply::finished, this, [this, reply]()
                {
                    if (reply->error() == QModbusDevice::NoError)
                    {
                        qDebug() << "Data is write sucessfully";
                        //statusBar()->showMessage("Data is write sucessfully");
                    }
                    else
                    {
                        qDebug() << "Data is write failed";
                        //statusBar()->showMessage("Data is write failed : " + reply->errorString());
                    }
                    reply->deleteLater(); // Clean up the reply object
                });
            }
        }
    }
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

    if(modbusDevice != nullptr)
    {
        delete modbusDevice;
        modbusDevice = nullptr;
    }
}


