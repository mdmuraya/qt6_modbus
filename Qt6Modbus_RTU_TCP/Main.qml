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

    ListModel {
            id: availableCOMPorts
            ListElement { displayText: "COM1"; uniqueId: "COM1" }
            ListElement { displayText: "COM2"; uniqueId: "COM2" }
            ListElement { displayText: "COM3"; uniqueId: "COM3" }
        }

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
                model: availableCOMPorts
                textRole: "displayText" // Role used for display text
                valueRole: "uniqueId" // Role used for unique ID (value property)
                onCurrentIndexChanged: {
                    // Access the unique ID using the currentValue property
                    console.log("Selected comboBoxVFDCOMPort.currentValue:", comboBoxVFDCOMPort.currentValue)
                    // or directly from the model
                    console.log("Selected availableCOMPorts.get(currentIndex).uniqueId:", availableCOMPorts.get(currentIndex).uniqueId)
                    console.log("Selected availableCOMPorts.get(currentIndex).displayText:", availableCOMPorts.get(currentIndex).displayText)
                }
            }

        }


        RowLayout {
            Button {
                id: buttonConnectToVFD
                text: qsTr("Connect to VFD")
                onClicked: {
                    console.log("'Connect to VFD' clicked")
                    _Qt6Modbus_RTU_TCP.onConnectToVFD(availableCOMPorts.get(comboBoxVFDCOMPort.currentIndex).uniqueId);
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

