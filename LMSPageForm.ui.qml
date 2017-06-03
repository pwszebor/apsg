import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    anchors.margins: margin

    property alias parametersButton: parametersButton
    property alias lmsPopup: lmsPopup

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
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        ComboBox {
            id: graphSelect
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            displayText: "Choose graph..."
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
        closePolicy: "NoAutoClose"
        width: parent.width * 5 / 6
        height: parent.height * 5 / 6
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        modal: true
    }
}
