import QtQuick 2.7
import Plot 1.0

Item {
    height: parent.height * 4 / 5
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.margins: margin

    property alias plot: plot

    Plot {
        id: plot
        anchors.fill: parent
    }
}
