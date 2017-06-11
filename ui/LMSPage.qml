import QtQuick 2.7
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

APSGPage {
    id: lmsPage

    property alias lmsPopup: lmsPopup

    property var parameters: ({})

    function changeParameters() {
        parameters = { "fileX": lmsPopup.xUrl, "fileD": lmsPopup.dUrl, "L": lmsPopup.lValue, "alpha": lmsPopup.alpha }
        console.log(JSON.stringify(parameters))
    }

    parametersButton.onReleased: {
        lmsPopup.open()
    }

    FileDialog {
        id: fileDialogX
        visible: false
        nameFilters: "*.txt"
        folder: shortcuts.home
        onAccepted: {
            console.log("file chosen:", fileUrl)
            lmsPopup.loadXButton.text = fileUrl.toString()
        }
    }

    FileDialog {
        id: fileDialogD
        visible: false
        nameFilters: "*.txt"
        folder: shortcuts.home
        onAccepted: {
            console.log("file chosen:", fileUrl)
            lmsPopup.loadDButton.text = fileUrl.toString()
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

    LMSPopup {
        id: lmsPopup

        property string xUrl: fileDialogX.fileUrl.toString()
        property string dUrl: fileDialogD.fileUrl.toString()
        property string lValue: lText.text
        property string alpha: alphaText.text

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
                    alphaText.text.length > 0) {
                changeParameters()
                lmsPopup.close()
            } else {
                errorDialog.open()
            }
        }

        popupCancel.onReleased: {
            lmsPopup.close()
        }
    }
}
