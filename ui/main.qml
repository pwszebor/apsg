import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.0
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
    property int simulation: APSG.simulation

    onSimulationChanged: {
        var page = APSG.algorithm === APSG.LMS ? lmsPage : rlsPage
        if (simulation === 1) { // running
            console.log("simulation running")
            page.simulationRunning()
            tabBar.enabled = false
        } else if (page.parametersReady) { // not running, but ready to run
            console.log("simulation stopped and ready")
            page.readyForSimulation()
            tabBar.enabled = true
        } else { // not running and not ready to run
            console.log("simulation stopped and not ready")
            page.notReadyForSimulation()
            tabBar.enabled = true
        }
    }

    function error(title, errorCode, buttons) {
        errorDialog.title = title
        errorDialog.text = APSG.errorString(errorCode)
        errorDialog.standardButtons = buttons
        errorDialog.visible = true
    }

    GridLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 0
        SwipeView {
            id: swipeView
            interactive: false
            anchors.fill: parent
            currentIndex: tabBar.currentIndex

            LMSPage {
                id: lmsPage
                property bool initializing: true

                function simulationRunning() {
                    simulateButtonBackground.color = redColor
                    graphButtonBackground.color = grayColor
                    simulateButton.text = "Stop simulation"
                    busyIndicator.running = true
                    parametersButton.enabled = false
                    graphSelect.enabled = false
                    graphButton.enabled = false
                }

                function readyForSimulation() {
                    simulateButtonBackground.color = greenColor
                    graphButtonBackground.color = simulation === 3 ? grayColor : greenColor
                    simulateButton.text = "Simulate"
                    busyIndicator.running = false
                    parametersButton.enabled = true
                    graphSelect.enabled = true
                    graphButton.enabled = true
                }

                function notReadyForSimulation() {
                    simulateButtonBackground.color = grayColor
                    graphButtonBackground.color = grayColor
                    simulateButton.text = "Simulate"
                    busyIndicator.running = false
                    parametersButton.enabled = true
                    graphSelect.enabled = true
                    graphButton.enabled = true
                }

                property bool parametersReady: false
                property bool readyToGraph: simulation === 2

                onParametersChanged: {
                    if (initializing) {
                        initializing = false
                        return
                    }
                    var errorCode = APSG.changeParameters(parameters)
                    if (errorCode !== 0) {
                        error("Error", errorCode, "Ok")
                        simulateButtonBackground.color = grayColor
                        parametersReady = false
                    } else {
                        simulateButtonBackground.color = greenColor
                        parametersReady = true
                    }
                }
                simulateButton.onReleased: {
                    console.log(simulation)
                    if (simulation === 1) {
                        APSG.stopSimulation()
                        return
                    }
                    if (parametersReady) {
                        APSG.simulate()
                    }
                }
                graphButton.onReleased: {
                    var title = (function () {
                        if (!readyToGraph) {
                            return ""
                        }
                        switch (graphSelect.currentIndex) {
                        case 0:
                            return "Wykres danych wejściowych x"
                        case 1:
                            return "Wykres wektora wzorcowego d"
                        case 2:
                            return "Wykres wektora wyjściowego y"
                        case 3:
                            return "Wykres modułu błędu e"
                        case 4:
                            return "Wykres współczynników filtru f"
                        default:
                            return ""
                        }
                    })()
                    if (readyToGraph) {
                        APSG.setDataForPlotter(graph.plot, graphSelect.currentText, title, "nr próbki", graphSelect.currentText, graphSelect.currentIndex === 3)
                        graph.plot.plot()
                    }
                }

                BusyIndicator {
                    id: busyIndicator
                    running: false
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            RLSPage {
                id: rlsPage

                property bool initializing: true

                function simulationRunning() {
                    simulateButtonBackground.color = redColor
                    graphButtonBackground.color = grayColor
                    simulateButton.text = "Stop simulation"
                    busyIndicator.running = true
                    parametersButton.enabled = false
                    graphSelect.enabled = false
                    graphButton.enabled = false
                }

                function readyForSimulation() {
                    simulateButtonBackground.color = greenColor
                    graphButtonBackground.color = simulation === 3 ? grayColor : greenColor
                    simulateButton.text = "Simulate"
                    busyIndicator.running = false
                    parametersButton.enabled = true
                    graphSelect.enabled = true
                    graphButton.enabled = true
                }

                function notReadyForSimulation() {
                    simulateButtonBackground.color = grayColor
                    graphButtonBackground.color = grayColor
                    simulateButton.text = "Simulate"
                    busyIndicator.running = false
                    parametersButton.enabled = true
                    graphSelect.enabled = true
                    graphButton.enabled = true
                }

                property bool parametersReady: false
                property bool readyToGraph: simulation === 2

                onParametersChanged: {
                    if (initializing) {
                        initializing = false
                        return
                    }
                    var errorCode = APSG.changeParameters(parameters)
                    if (errorCode !== 0) {
                        error("Error", errorCode, "Ok")
                        simulateButtonBackground.color = grayColor
                        parametersReady = false
                    } else {
                        simulateButtonBackground.color = greenColor
                        parametersReady = true
                    }
                }
                simulateButton.onReleased: {
                    console.log(simulation)
                    if (simulation === 1) {
                        APSG.stopSimulation()
                        return
                    }
                    if (parametersReady) {
                        APSG.simulate()
                    }
                }
                graphButton.onReleased: {
                    var title = (function () {
                        if (!readyToGraph) {
                            return ""
                        }
                        switch (graphSelect.currentIndex) {
                        case 0:
                            return "Wykres danych wejściowych x"
                        case 1:
                            return "Wykres wektora wzorcowego d"
                        case 2:
                            return "Wykres wektora wyjściowego y"
                        case 3:
                            return "Wykres modułu błędu e"
                        case 4:
                            return "Wykres współczynników filtru f"
                        default:
                            return ""
                        }
                    })()
                    if (readyToGraph) {
                        APSG.setDataForPlotter(graph.plot, graphSelect.currentText, title, "nr próbki", graphSelect.currentText, graphSelect.currentIndex === 3)
                        graph.plot.plot()
                    }
                }

                BusyIndicator {
                    id: rlsBusyIndicator
                    running: false
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
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
            text: qsTr("Lms")
        }
        TabButton {
            text: qsTr("RLS")
        }
    }

    MessageDialog {
        id: errorDialog
        modality: "ApplicationModal"
        visible: false
    }
}
