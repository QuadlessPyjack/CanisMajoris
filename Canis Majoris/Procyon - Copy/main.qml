import QtQuick 2.1
import QtQuick.Window 2.0

Window {
    visible: true
    width: 360
    height: 360

    property string dbg_log:"Debug Log"

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Procyon_DBGScrollTextComponent{
        label: dbgLog.text
    }

    Text {
        text: qsTr(dbgLog.text())
        anchors.centerIn: parent
    }
}
