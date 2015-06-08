import QtQuick 2.0
Item{
id: toolBoxButtonContainer

property string icon: "undefined"
property color btnColor: "grey"

Rectangle {
    id: toolBoxButton
    color: btnColor
    width: 50; height: 50
    border.color: "#4f4747"
    border{
        width: 2
    }

    Image{
         id: tbBtnIcon
         anchors.fill: parent
         source: icon
    }

    MouseArea{
        id: tbBtnMouseArea
        anchors.fill: parent
    }
}
}
