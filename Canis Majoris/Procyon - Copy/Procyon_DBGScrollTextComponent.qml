import QtQuick 2.1

Item {id:container
    width:360
    height:800

    property string wrap:"Text.WordWrap"
    property real topwidth:30
    property string label:
"
==============================
Canis Lupus - Codename Procyon
Debug Logger and Editor
11/03/2015 - Bogdan Vitel
==============================

"
    property color paint

    Rectangle {
        id:background
        width: 360
        anchors.fill:parent
        color:"#000000"
        radius:2
        border.color: "#4f4747"
        antialiasing:true
        border{
            width:3
        }
    }

    TextEdit{
        id:template
        width: 360
        height: 800
        color: "#ebc400"
        text: label

        font.pointSize:12
        wrapMode:TextEdit.Wrap
        readOnly: true
        textFormat: Text.PlainText
        clip: false
        cursorVisible: false
        anchors.top: parent.top
        anchors.topMargin: 9
        anchors.leftMargin: 4
        horizontalAlignment: Text.AlignLeft

    }
}
