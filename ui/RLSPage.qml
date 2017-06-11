import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

APSGPage {
    id: rlsPage

    property alias rlsPopup: rlsPopup

    property var parameters: ({})

    function changeParameters() {
        parameters = { "fileX": rlsPopup.xUrl, "fileD": rlsPopup.dUrl, "L": rlsPopup.lValue, "lambda": rlsPopup.lambda, "gamma": rlsPopup.gamma }
        console.log(JSON.stringify(parameters))
    }

    parametersButton.onReleased: {
        rlsPopup.open()
    }

    FileDialog {
        id: fileDialogX
        visible: false
        nameFilters: "*.txt"
        folder: shortcuts.home
        onAccepted: {
            console.log("file chosen:", fileUrl)
            rlsPopup.loadXButton.text = fileUrl.toString()
        }
    }

    FileDialog {
        id: fileDialogD
        visible: false
        nameFilters: "*.txt"
        folder: shortcuts.home
        onAccepted: {
            console.log("file chosen:", fileUrl)
            rlsPopup.loadDButton.text = fileUrl.toString()
        }
    }

    MessageDialog {
        id: errorDialog
        visible: false
        modality: "ApplicationModal"
        title: "Error"
        text: "Not all parameters were given"
        standardButtons: "Ok"
    }

    RLSPopup {
        id: rlsPopup

        property string xUrl: fileDialogX.fileUrl.toString()
        property string dUrl: fileDialogD.fileUrl.toString()
        property string lValue: lText.text
        property string lambda: lambdaText.text
        property string gamma: gammaText.text

        loadXButton.onReleased: {
            fileDialogX.title = "Load x data"
            fileDialogX.visible = true
        }

        loadDButton.onReleased: {
            fileDialogD.title = "Load d data"
            fileDialogD.visible = true
        }

        saveParameters.onReleased: {
            if (xUrl.length > 0 &&
                    dUrl.length > 0 &&
                    lText.text.length > 0 &&
                    lambdaText.text.length > 0 &&
                    gammaText.text.length > 0) {
                changeParameters()
                rlsPopup.close()
            } else {
                errorDialog.open()
            }
        }

        popupCancel.onReleased: {
            rlsPopup.close()
        }
    }
}
