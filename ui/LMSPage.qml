import QtQuick 2.7
import QtQuick.Dialogs 1.2
import APSG 1.0

LMSPageForm {
    id: lmsPage

    property var parameters: ({})

    function changeParameters() {
        parameters = { "fileX": fileDialogX.fileUrl.toString(), "fileD": fileDialogD.fileUrl.toString(), "L": lText.text, "alpha": alphaText.text }
        console.log(JSON.stringify(parameters))
    }

    parametersButton.onReleased: {
        lmsPopup.open()
    }

    popupCancel.onReleased: {
        lmsPopup.close()
    }

    loadXButton.onReleased: {
        fileDialogX.title = "Load x data"
        fileDialogX.visible = true
    }

    loadDButton.onReleased: {
        fileDialogD.title = "Load d data"
        fileDialogD.visible = true
    }

    saveParameters.onReleased: {
        if (fileDialogX.fileUrl.toString().length > 0 &&
                fileDialogD.fileUrl.toString().length > 0 &&
                lText.text.length > 0 &&
                alphaText.text.length > 0) {
            changeParameters()
            lmsPopup.close()
        } else {
            errorDialog.open()
        }
    }

    FileDialog {
        id: fileDialogX
        visible: false
        nameFilters: "*.txt"
        folder: shortcuts.home
        onAccepted: {
            console.log("file chosen:", fileUrl)
            loadXButton.text = fileUrl.toString()
        }
    }

    FileDialog {
        id: fileDialogD
        visible: false
        nameFilters: "*.txt"
        folder: shortcuts.home
        onAccepted: {
            console.log("file chosen:", fileUrl)
            loadDButton.text = fileUrl.toString()
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
}
