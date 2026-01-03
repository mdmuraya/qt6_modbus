#ifndef QT6MODBUS_RTU_TCP_H
#define QT6MODBUS_RTU_TCP_H

#include <QObject>
#include <QModbusClient>

class Qt6Modbus_RTU_TCP : public QObject
{
    Q_OBJECT
    public:
        explicit Qt6Modbus_RTU_TCP(QObject *parent = nullptr);
        ~Qt6Modbus_RTU_TCP();

    signals:

    public slots:
        void onConnectToVFD(QString port);
        void onClearVFDFaults();
        void onStartMotorFWD();
        void onStartMotorREV();
        void onStopMotor();

    private:
        QModbusClient *modbusDevice = nullptr;
};

#endif // QT6MODBUS_RTU_TCP_H
