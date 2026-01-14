import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs
import Qt6ModbusVFDController

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
                implicitContentWidthPolicy: ComboBox.WidestText
                textRole: "displayText" // Role used for display text
                valueRole: "uniqueId" // Role used for unique ID (value property)
                onCurrentIndexChanged: {
                    // Access the unique ID directly from the model
                    console.log("Selected availableCOMPorts.get(currentIndex).uniqueId:", comboBoxVFDCOMPort.model[currentIndex].uniqueId)
                    console.log("Selected availableCOMPorts.get(currentIndex).displayText:", comboBoxVFDCOMPort.model[currentIndex].displayText)
                }
            }
            Button {
                id: buttonAvailableCOMPorts
                text: qsTr("Refresh")
                onClicked: {
                    console.log("'Refresh COM ports' clicked")
                    console.log("Available COM ports: " + comboBoxVFDCOMPort.model)
                    comboBoxVFDCOMPort.model = MainBackendHelper.getAvailableCOMPorts()
                }
            }

        }

        RowLayout {
            Label {
               id: labelVFDSpeed
               text: qsTr("VFD Speed: ")
            }

            Dial {
                   id: dialVFDSpeed
                   from: 0
                   to: 100
                }
        }

        RowLayout {
            Label { text: "Manual" }
                Switch {
                    checked: false
                    onToggled: saveSetting(checked)
                }
                Label { text: "Auto" }
        }

        RowLayout {
            Button {
                id: buttonConnectToVFD
                text: qsTr("Connect to VFD")
                onClicked: {
                    console.log("'Connect to VFD' clicked")
                    MainBackendHelper.onConnectToVFD(comboBoxVFDCOMPort.model[comboBoxVFDCOMPort.currentIndex].uniqueId);
                }
            }

            Button {
                id: buttonClearVFDFaults
                text: qsTr("Clear VFD Faults")
                onClicked: {
                    console.log("'Clear VFD Faults' clicked")
                    MainBackendHelper.onClearVFDFaults();
                }
            }

            Button {
                id: buttonStartMotorFWD
                text: qsTr("Start Motor FWD")
                onClicked: {
                    console.log("'Start Motor FWD' clicked")
                    MainBackendHelper.onStartMotorFWD();
                }
            }

            Button {
                id: buttonStartMotorREV
                text: qsTr("Start Motor REV")
                onClicked: {
                    console.log("'Start Motor REV' clicked")
                    MainBackendHelper.onStartMotorREV();
                }
            }

            Button {
                id: buttonStopMotor
                text: qsTr("Stop Motor")
                onClicked: {
                    console.log("'Stop Motor' clicked")
                    MainBackendHelper.onStopMotor();
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

    Component.onCompleted: {
        comboBoxVFDCOMPort.model = MainBackendHelper.getAvailableCOMPorts()
    }


    Connections {
        target: MainBackendHelper
        function onRequestVFDStatus () {
            console.log("QML MainBackendHelper.onRequestVFDStatus ==>> BLAH BLAH BLAH!!!")
        }
    }

}

