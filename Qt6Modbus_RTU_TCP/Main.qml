import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs



Window {
    id: mainWindowId
    width: 1024
    height: 768
    visible: true
    title: qsTr("Qt6Modbus_RTU_TCP")

    ColumnLayout {
        anchors.margins: 10
        anchors.fill: parent
        spacing: 20

        RowLayout {
            Label {
               id: labelVFDCOMPort
               text: qsTr("VFD COM Port: ")
            }
            ComboBox {
                id: comboBoxVFDCOMPort
                model: ["COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "COM10", "COM11", "COM12"]
            }

        }


        RowLayout {
            Button {
                id: buttonConnectToVFD
                text: qsTr("Connect to VFD")
                onClicked: {
                    console.log("'Connect to VFD' clicked")
                    _Qt6Modbus_RTU_TCP.onConnectToVFD();
                }
            }

            Button {
                id: buttonClearVFDFaults
                text: qsTr("Clear VFD Faults")
                onClicked: {
                    console.log("'Clear VFD Faults' clicked")
                    _Qt6Modbus_RTU_TCP.onClearVFDFaults();
                }
            }

            Button {
                id: buttonStartMotorFWD
                text: qsTr("Start Motor FWD")
                onClicked: {
                    console.log("'Start Motor FWD' clicked")
                    _Qt6Modbus_RTU_TCP.onStartMotorFWD();
                }
            }

            Button {
                id: buttonStartMotorREV
                text: qsTr("Start Motor REV")
                onClicked: {
                    console.log("'Start Motor REV' clicked")
                    _Qt6Modbus_RTU_TCP.onStartMotorREV();
                }
            }

            Button {
                id: buttonStopMotor
                text: qsTr("Stop Motor")
                onClicked: {
                    console.log("'Stop Motor' clicked")
                    _Qt6Modbus_RTU_TCP.onStopMotor();
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }


    MessageDialog {
        id: messageDialog1Id
        title: "My message dialog"
        text: "Hey you"
        buttons: MessageDialog.Ok | MessageDialog.Cancel
    }
}

