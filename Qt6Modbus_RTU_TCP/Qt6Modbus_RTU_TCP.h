#ifndef QT6MODBUS_RTU_TCP_H
#define QT6MODBUS_RTU_TCP_H

#include <QObject>
#include <QModbusClient>
#include <QSerialPortInfo>
#include <QVariantList>
#include <QTimer>


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

    private slots:
        void onGetVFDStatus();

    private:
        //QModbusClient *modbusDevice = nullptr;
        //QTimer *timer = nullptr;
        std::unique_ptr<QModbusClient> _modbusDevice; // Default initialized to nullptr
        std::unique_ptr<QTimer> _getVFDStatusTimer; // Default initialized to nullptr
};

#endif // QT6MODBUS_RTU_TCP_H
