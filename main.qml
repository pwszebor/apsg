import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import APSG 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    property int margin: 10
    minimumWidth: mainLayout.implicitWidth + 2 * margin
    minimumHeight: mainLayout.implicitHeight + 2 * margin
    title: qsTr("APSG")
    property APSG apsg: APSG

    GridLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 0
        SwipeView {
            id: swipeView
            anchors.fill: parent
            currentIndex: tabBar.currentIndex

            LMSPage {
                id: lmsPage
            }

            RLSPage {
                id: rlsPage
            }

            onCurrentIndexChanged: {
                APSG.algorithm = currentIndex == 0 ? APSG.LMS : APSG.RLS
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("LMS")
        }
        TabButton {
            text: qsTr("RLS")
        }
    }

//    ActionHandler {
//
//    }
}
