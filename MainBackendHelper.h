#ifndef MAINBACKENDHELPER_H
#define MAINBACKENDHELPER_H

#include <QObject>
#include <QModbusClient>
#include <QSerialPortInfo>
#include <QVariantList>
#include <QTimer>
#include <QQmlEngine>


class MainBackendHelper : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    public:
        explicit MainBackendHelper(QObject *parent = nullptr);
        ~MainBackendHelper();

    signals:
        void requestVFDStatus();

    public slots:
        QVariantList  getAvailableCOMPorts();
        void onConnectToVFD(QString port);
        void onClearVFDFaults();
        void onStartMotorFWD();
        void onStartMotorREV();
        void onStopMotor();
        void handleVFDStatusRequest();

    private:
        //QModbusClient *modbusDevice = nullptr;
        //QTimer *timer = nullptr;
        std::unique_ptr<QModbusClient> _modbusDevice; // Default initialized to nullptr
        std::unique_ptr<QTimer> _GetVFDStatusTimer; // Default initialized to nullptr
        QDateTime _dateTimeOnApplicationStart = QDateTime::currentDateTime();
};

#endif // MAINBACKENDHELPER_H
