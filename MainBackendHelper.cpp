#include <QDebug>
#include <QModbusRtuSerialClient>
#include <QModbusTcpClient>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVariantList>

#include "MainBackendHelper.h"


MainBackendHelper::MainBackendHelper(QObject *parent)
    : QObject{parent}
{
    qDebug() << "MainBackendHelper::MainBackendHelper()";

    _modbusDevice = std::make_unique<QModbusRtuSerialClient>();
    _GetVFDStatusTimer = std::make_unique<QTimer>();

    // setup signals and slots
    connect(_GetVFDStatusTimer.get(), &QTimer::timeout, [this](){
        emit requestVFDStatus();
    });

    connect(this, &MainBackendHelper::requestVFDStatus, this, &MainBackendHelper::onRequestVFDStatus);

    _GetVFDStatusTimer->start(1000); //1 second

}

void MainBackendHelper::onConnectToVFD(QString port)
{
    qDebug() << "MainBackendHelper::onConnectToVFD() on COM port: " + port;

    if(_modbusDevice == nullptr)
    {
        _modbusDevice = std::make_unique<QModbusRtuSerialClient>();
    }

    if (_modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, port);
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::EvenParity);
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
        _modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);

        int _modbusDeviceId = 45;
        _modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter,_modbusDeviceId);

        _modbusDevice->setTimeout(1000);
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
            qDebug() << "MainBackendHelper::onConnectToVFD() on COM port: " + port + " FAILED";
        } else {
            //ui->actionConnect->setEnabled(false);
            //ui->actionDisconnect->setEnabled(true);
            qDebug() << "MainBackendHelper::onConnectToVFD() on COM port: " + port + " SUCCESS";

            int addressToWrite = 8193;

            QVector<quint16> dataToWrite;
            dataToWrite.append(5000); // Speed of the motor (0.01 Hz)

            QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

            for (int i = 0 ; i < dataToWrite.size() ; i++)
            {
                writeHoldingRegisters.setValue(i, dataToWrite.at(i));
            }

            if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDevice->connectionParameter(QModbusDevice::NetworkAddressParameter).toInt()))
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

void MainBackendHelper::onClearVFDFaults()
{
    qDebug() << "MainBackendHelper::onClearVFDFaults()";

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(8); // Clear VFD Faults

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDevice->connectionParameter(QModbusDevice::NetworkAddressParameter).toInt()))
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

void MainBackendHelper::onStartMotorFWD()
{
    qDebug() << "MainBackendHelper::onStartMotorFWD()";

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(18); // Start Motor FWD

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDevice->connectionParameter(QModbusDevice::NetworkAddressParameter).toInt()))
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

void MainBackendHelper::onStartMotorREV()
{
    qDebug() << "MainBackendHelper::onStartMotorREV()";

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(34); // Start Motor REV

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDevice->connectionParameter(QModbusDevice::NetworkAddressParameter).toInt()))
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

void MainBackendHelper::onStopMotor()
{
    qDebug() << "MainBackendHelper::onStopMotor()";

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        int addressToWrite = 8192;

        QVector<quint16> dataToWrite;
        dataToWrite.append(1); // Staop Motor

        QModbusDataUnit writeHoldingRegisters(QModbusDataUnit::HoldingRegisters, addressToWrite, dataToWrite.size());

        for (int i = 0 ; i < dataToWrite.size() ; i++)
        {
            writeHoldingRegisters.setValue(i, dataToWrite.at(i));
        }

        if (auto *reply = _modbusDevice->sendWriteRequest(writeHoldingRegisters, _modbusDevice->connectionParameter(QModbusDevice::NetworkAddressParameter).toInt()))
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

void MainBackendHelper::onRequestVFDStatus()
{
    QDateTime dateTimeUTC = QDateTime::currentDateTimeUtc();
    qDebug() << "C++ MainBackendHelper::onRequestVFDStatus()";

    QTimeZone timeZoneAmericaToronto("America/Toronto"); // Specify target time zone

    QDateTime dateTimeAmericaToronto = dateTimeUTC.toTimeZone(timeZoneAmericaToronto);

    qDebug() << "UTC:" << dateTimeUTC.toString();
    qDebug() << "Toronto:" << dateTimeAmericaToronto.toString();

    if (_modbusDevice->state() == QModbusDevice::ConnectedState)
    {
        QModbusDataUnit readHoldingRegisters(QModbusDataUnit::HoldingRegisters, 0, 10);

        if (auto *reply = _modbusDevice->sendReadRequest(readHoldingRegisters, _modbusDevice->connectionParameter(QModbusDevice::NetworkAddressParameter).toInt()))
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


QVariantList  MainBackendHelper::getAvailableCOMPorts()
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

MainBackendHelper::~MainBackendHelper()
{
    qDebug() << "MainBackendHelper::~MainBackendHelper()";
}


