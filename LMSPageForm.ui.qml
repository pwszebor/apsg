import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    GridLayout {
        columnSpacing: 0
        rowSpacing: 0
        flow: GridLayout.LeftToRight
        anchors.fill: parent

        ColumnLayout {
            id: menu
            spacing: 0
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillHeight: true
            Layout.preferredWidth: 200
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400

            Button {
                id: openButton
                text: qsTr("Open file")
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.minimumHeight: 40
                Layout.minimumWidth: 100
                Layout.preferredHeight: 40
                Layout.preferredWidth: 100
            }

            Button {
                id: saveButton
                text: qsTr("Save file")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.minimumHeight: 40
                Layout.minimumWidth: 100
                Layout.preferredHeight: 40
                Layout.preferredWidth: 100
            }
        }

        Item {
            id: item1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.margins: margin

            TextField {
                id: textField
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.left: parent.left
                placeholderText: qsTr("bla bla")
            }

            Button {
                id: button
                x: 115
                y: 112
                text: qsTr("Ok")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
            }
        }
    }
}
