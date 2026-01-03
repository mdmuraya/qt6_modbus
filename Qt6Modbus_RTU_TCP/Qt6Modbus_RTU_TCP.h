#ifndef QT6MODBUS_RTU_TCP_H
#define QT6MODBUS_RTU_TCP_H

#include <QObject>
#include <QModbusClient>
#include <QSerialPortInfo>
#include <QVariantList>


class Qt6Modbus_RTU_TCP : public QObject
{
    Q_OBJECT
    public:
        explicit Qt6Modbus_RTU_TCP(QObject *parent = nullptr);
        ~Qt6Modbus_RTU_TCP();

    signals:

    public slots:
        QVariantList  getAvailableCOMPorts();
        void onConnectToVFD(QString port);
        void onClearVFDFaults();
        void onStartMotorFWD();
        void onStartMotorREV();
        void onStopMotor();

    private:
        QModbusClient *modbusDevice = nullptr;
        //std::unique_ptr<QModbusClient> modbusDevice; // Default initialized to nullptr
};

#endif // QT6MODBUS_RTU_TCP_H
