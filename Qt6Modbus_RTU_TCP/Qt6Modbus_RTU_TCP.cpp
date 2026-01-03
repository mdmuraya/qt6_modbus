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

    _modbusDevice = std::make_unique<QModbusRtuSerialClient>();
    _getVFDStatusTimer = std::make_unique<QTimer>();

    // setup signal and slot
    QObject::connect(_getVFDStatusTimer.get(), SIGNAL(timeout()),this, SLOT(onGetVFDStatus()));

    _getVFDStatusTimer->start(1000); //1 second

}

void Qt6Modbus_RTU_TCP::onConnectToVFD(QString port)
{
    qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port;

    if(_modbusDevice == nullptr)
    {
        _modbusDevice = std::make_unique<QModbusRtuSerialClient>();
    }

    //_modbusDevice = new QModbusRtuSerialClient(this);

    if (_modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, port);
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::EvenParity);
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);

        _modbusDevice->setTimeout(10000);
        _modbusDevice->setNumberOfRetries(3);

        // Connect to signals to handle connection status and errors
        QObject::connect(_modbusDevice.get(), &QModbusDevice::stateChanged, this, [&](QModbusDevice::State state){
            qDebug() << "State changed:" << state;
        });

        QObject::connect(_modbusDevice.get(), &QModbusDevice::errorOccurred, this, [&](QModbusDevice::Error error){
            if (error == QModbusDevice::TimeoutError) {
                qDebug() << "Modbus Timeout Error occurred:" << _modbusDevice->errorString();
            }
        });


        if (!_modbusDevice->connectDevice()) {
            //statusBar()->showMessage(tr("Connect failed: %1").arg(_modbusDevice->errorString()), 5000);
            qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port + " FAILED";
        } else {
            //ui->actionConnect->setEnabled(false);
            //ui->actionDisconnect->setEnabled(true);
            qDebug() << "Qt6Modbus_RTU_TCP::onConnectToVFD() on COM port: " + port + " SUCCESS";

            int _modbusDeviceId = 45;
            int addressToWrite = 8193;

            QVector<quint16> dataToWrite;
            dataToWrite.append(5000); // Speed of the motor (Hz)

            QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

            for (int i = 0 ; i < dataToWrite.size() ; i++)
            {
                writeHoldingRegisters.setValue(i, dataToWrite.at(i));
            }

            if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDeviceId))
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
}

void Qt6Modbus_RTU_TCP::onClearVFDFaults()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onClearVFDFaults()";

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int _modbusDeviceId = 45;
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(8); // Clear VFD Faults

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDeviceId))
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

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int _modbusDeviceId = 45;
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(18); // Start Motor FWD

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDeviceId))
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

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int _modbusDeviceId = 45;
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(34); // Start Motor REV

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDeviceId))
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

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int _modbusDeviceId = 45;
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(1); // Staop Motor

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDeviceId))
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

void Qt6Modbus_RTU_TCP::onGetVFDStatus()
{
    qDebug() << "Qt6Modbus_RTU_TCP::onGetVFDStatus()";

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        QModbusDataUnit readHoldingRegisters(QModbusDataUnit::HoldingRegisters, 0, 10);
        int _modbusDeviceId = 45;

        if (auto *reply = _modbusDevice->sendReadRequest(readHoldingRegisters, _modbusDeviceId))
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

                                QVariantList  listOfAvailableData;

                                for (int i = 0 ; i < units.valueCount() ; i++)
                                {
                                    QString entry = "Address : " + QString::number(units.startAddress() + i) + " Values : " + QString::number(units.value(i), 16) + " | " + QString::number(units.value(i));
                                    //ui->listWidget_Holding_Data->addItem(Entry);
                                    qDebug() << "Data read sucessfully: " + entry;

                                    QVariantMap  availableData;

                                    availableData["address"] = QString::number(units.startAddress() + i);
                                    QString label = "Unknown label";

                                    switch (i)
                                    {
                                        case 0: //base address relative to 4xxxx
                                            break;
                                        case 1: //1st 16-bit register relative to 4xxxx
                                            label = "Frequency command (0.01 Hz)";
                                            break;
                                        case 2:
                                            label = "Frequency output (0.01 Hz)";
                                            break;
                                        case 3:
                                            label = "Current output (0.0 A)";
                                        case 4:
                                            label = "DC bus output voltage (V)";
                                            break;
                                        case 5:
                                            label = "Output voltage (0.1 V)";
                                            break;
                                        default:
                                            availableData["Label"] = "Unknown label";
                                            break;

                                    }

                                    availableData["Label"] = label;
                                    availableData["HexValue"] = QString::number(units.value(i), 16);
                                    availableData["DecimalValue"] =  QString::number(units.value(i));

                                    listOfAvailableData.append(availableData);
                                    qDebug() << availableData;
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

        availableCOMPorts.push_back(availableCOMPort);
    }
    //qDebug() << availableCOMPorts;

    return availableCOMPorts;

}

Qt6Modbus_RTU_TCP::~Qt6Modbus_RTU_TCP()
{
    qDebug() << "Qt6Modbus_RTU_TCP::~Qt6Modbus_RTU_TCP()";
}


