import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    GridLayout {
        anchors.fill: parent

        ColumnLayout {
            id: menu
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: parent.width / 3
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400
            spacing: 20

            Button {
                id: openButton
                width: 100
                text: qsTr("Open file")
            }

            Button {
                id: saveButton
                width: 100
                text: qsTr("Save file")
            }
        }

        Button {
            id: button
            text: qsTr("Ok")
            anchors.left: menu.right
        }

        TextField {
            id: textField
            placeholderText: qsTr("bla bla")
        }
    }
}
