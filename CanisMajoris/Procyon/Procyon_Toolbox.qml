import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    flags: Qt.Tool | Qt.CustomizeWindowHint | Qt.WindowTitleHint
    id: toolBox
    title: "Tools"
    visible: true
    width: 50
    height: 250

    signal toolBoxSelectionEnabled()
    signal toolBoxMoveEnabled()
    signal toolBoxRotateEnabled()

    onToolBoxSelectionEnabled: {
        tbSelectBtn.btnColor = "#acabab"
        tbMoveBtn.btnColor = "grey"
        tbRotateBtn.btnColor = "grey"
    }

    onToolBoxMoveEnabled: {
        tbMoveBtn.btnColor = "#acabab"
        tbSelectBtn.btnColor = "grey"
        tbRotateBtn.btnColor = "grey"
    }

    onToolBoxRotateEnabled: {
        tbRotateBtn.btnColor = "#acabab"
        tbSelectBtn.btnColor = "grey"
        tbMoveBtn.btnColor = "grey"
    }

    Column{
        id: tbButtonsCollection
        anchors.fill: parent
        spacing: 1
        height: 180

        Procyon_ToolBoxBtn{
            width: 50; height:50
            id: tbSelectBtn
            icon: "tbSelectBtn.png"
            MouseArea{
                id: tbSelectMouseArea
                anchors.fill: parent
                onClicked: toolBoxSelectionEnabled()
            }
        }

        Procyon_ToolBoxBtn{
            width: 50; height: 50
            id: tbMoveBtn
            icon: "tbMoveBtn.png"
            MouseArea{
                id: tbMoveMouseArea
                anchors.fill: parent
                onClicked: toolBoxMoveEnabled()
            }
        }

        Procyon_ToolBoxBtn{
            width: 50; height: 50
            id: tbRotateBtn
            icon: "tbRotateBtn.png"
            MouseArea{
                id: tbRotateMouseArea
                anchors.fill: parent
                onClicked: toolBoxRotateEnabled()
            }
        }
    }
}

