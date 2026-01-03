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
               id: labelFirstNameId
               text: qsTr("First Name: ")
            }

            TextField {
                id: textFieldFirstNameId
                placeholderText: qsTr("first name")
            }
        }

        RowLayout {
            Label {
               id: labelLastNameId
               text: qsTr("Last Name: ")
            }

            TextField {
                id: textFieldLastNameId
                placeholderText: qsTr("lastr name")
            }
        }

        RowLayout {
            Label {
               id: busyIndicator1LabelId
               text: qsTr("Busy Indicator: ")
            }

            BusyIndicator {
                id: busyIndicator1Id
                running:  false
                visible: false
            }
        }

        RowLayout {
            Label {
               id: dial1LabelId
               text: qsTr("Set temperature: ")
            }

            Dial {
                   id: dial1Id
                   from: 0
                   to: 100
                }
        }

        RowLayout {
            Label {
               id: comboBox1LabelId
               text: qsTr("Select one: ")
            }
            ComboBox {
                id: comboBox1Id
                model: ["One", "Two", "Three"]
            }
        }

        RowLayout {
            GroupBox {
                id: radioButtonsGroupbox1Id

                ColumnLayout {
                    Label {
                        Layout.fillWidth: true
                        text: qsTr("Select size:")
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        RadioButton {
                            text: qsTr("Small")
                        }

                        RadioButton {
                            text: qsTr("Medium")
                            checked: true
                        }

                        RadioButton {
                            text: qsTr("Large")
                        }
                    }

                }



            }

        }

        RowLayout {
            Frame {
                id: switchesGroupbox1Id
                ColumnLayout {
                    spacing: 20

                    Label {
                        Layout.fillWidth: true
                        text: qsTr("What do you want?")
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Switch {
                            id: switchWiFi
                            text: qsTr("Wi-Fi")
                            checked: true
                        }

                        Switch {
                            id: switchBluetooth
                            text: qsTr("Bluetooth")
                        }

                        Switch {
                            id: switchNFC
                            text: qsTr("NFC")
                            enabled: false
                        }
                    }
                }
            }
        }

        RowLayout {
            Button {
                id: button1Id
                text: qsTr("Running...")
                onClicked: {
                    console.log("Button 1 clicked")
                    busyIndicator1Id.running = true
                    busyIndicator1Id.visible = true
                }
            }

            Button {
                id: button2Id
                text: qsTr("Not running...")
                onClicked: {
                    console.log("Button 2 clicked")
                    busyIndicator1Id.running = false
                    busyIndicator1Id.visible = false
                }
            }

            Button {
                id: button3Id
                text: qsTr("Click me...")
                onClicked: {
                    console.log("Button 3 clicked")
                    messageDialog1Id.text = "Your names are: " + textFieldFirstNameId.text + " " + textFieldLastNameId.text
                    messageDialog1Id.open()
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
