import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Popup {
    closePolicy: "CloseOnEscape"
    width: parent.width * 5 / 6
    height: parent.height * 5 / 6
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    modal: true

    property alias popupCancel: cancelButton
    property alias saveParameters: saveButton
    property alias loadXButton: loadXButton
    property alias loadDButton: loadDButton
    property alias lText: lTextField
    property alias alphaText: alphaTextField

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
            Layout.minimumWidth: 150
            text: qsTr("From file...")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Label {
            id: dLabel
            text: qsTr("Wektor próbek sygnału wzorcowego d:")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: loadDButton
            Layout.minimumWidth: 150
            text: qsTr("From file...")
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
            Layout.minimumWidth: 150
            text: qsTr("Cancel")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: saveButton
            Layout.minimumWidth: 150
            text: qsTr("Save")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }
}
