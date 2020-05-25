import QtQuick 2.12
import QtQuick.Window 2.12

Item {
    id: background
    width: root.width
    height: root.height
    Rectangle{
        width: parent.width - globalmargin
        height:  parent.height - globalmargin
        anchors.left: parent.left
        anchors.top: parent.top
        color: "#F4EBD9"
    }
    
    Rectangle{
        opacity: 0.5
        width: parent.width - globalmargin
        height:  parent.height - globalmargin
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#BACCBC"
    }
}
