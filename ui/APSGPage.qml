import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    anchors.margins: margin

    property alias parametersButton: parametersButton
    property alias graphSelect: graphSelect
    property alias graphButton: graphButton
    property alias graph: graph
    property alias graphButtonBackground: graphButtonBackground
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
        anchors.bottom: graph.top
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

    PlotView {
        id: graph
    }
}
