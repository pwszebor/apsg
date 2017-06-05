import QtQuick 2.7
import Plot 1.0

Item {
    height: parent.height * 4 / 5
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.margins: margin

    property alias title: title
    property alias plot: plot

    Text {
        id: title
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: margin
        horizontalAlignment: Text.AlignHCenter
        z: 100
    }

    Plot {
        id: plot
        anchors.top: title.bottom
        anchors.topMargin: margin
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
