import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    anchors.margins: margin

    property alias parametersButton: parametersButton
    property alias graphSelect: graphSelect
    property alias graphButton: graphButton
    property alias graphButtonBackground: graphButtonBackground
    property alias lmsPopup: lmsPopup
    property alias popupCancel: cancelButton
    property alias saveParameters: saveButton
    property alias loadXButton: loadXButton
    property alias loadDButton: loadDButton
    property alias lText: lTextField
    property alias alphaText: alphaTextField
    property alias simulateButton: simulateButton
    property alias simulateButtonBackground: simulateButtonBackground
    property string greenColor: "#148e73"
    property string grayColor: "#aaaaaa"
    property string redColor: "#ad0725"

    GroupBox {
        id: controls
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: graphFrame.top
        anchors.margins: margin

        Button {
            id: parametersButton
            text: qsTr("Parameters")
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            id: simulateButton
            text: qsTr("Simulate")
            background: Rectangle {
                id: simulateButtonBackground
                radius: 4
                color: grayColor
            }
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            id: graphButton
            text: "Draw graph"
            background: Rectangle {
                id: graphButtonBackground
                radius: 4
                color: grayColor
            }
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: margin
            anchors.right: graphSelect.left
        }

        ComboBox {
            id: graphSelect
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            model: ["x", "d", "y", "e", "f"]
            onCountChanged: displayText = model[currentIndex]
        }
    }

    Frame {
        id: graphFrame
        height: parent.height * 4 / 5
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.margins: margin
    }

    Popup {
        id: lmsPopup
        closePolicy: "CloseOnEscape"
        width: parent.width * 5 / 6
        height: parent.height * 5 / 6
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        modal: true

        GridLayout {
            id: gridLayout
            columns: 2
            flow: GridLayout.LeftToRight
            anchors.margins: margin
            anchors.fill: parent

            Label {
                id: xLabel
                text: qsTr("Wektor próbek sygnału wejściowego x:")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Button {
                id: loadXButton
                text: qsTr("From file...")
                Layout.maximumWidth: width
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Label {
                id: dLabel
                text: qsTr("Wektor próbek sygnału wzorcowego d:")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Button {
                id: loadDButton
                text: qsTr("From file...")
                Layout.maximumWidth: width
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Label {
                id: lLabel
                text: qsTr("Rząd filtru L:")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            TextField {
                id: lTextField
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                validator: IntValidator {
                    bottom: 1
                    locale: "en_US"
                }
            }

            Label {
                id: alphaLabel
                text: qsTr("Stała adaptacji α:")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            TextField {
                id: alphaTextField
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                validator: DoubleValidator {
                    bottom: 0
                    locale: "en_US"
                    notation: "ScientificNotation"
                }
            }

            Button {
                id: cancelButton
                text: qsTr("Cancel")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Button {
                id: saveButton
                text: qsTr("Save")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        }
    }
}
