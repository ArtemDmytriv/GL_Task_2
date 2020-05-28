import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: saveField
    visible:  true
    Layout.preferredWidth: elements.width
    Layout.preferredHeight: 70
    Rectangle {
        color: "#F4EBD9"
        anchors.fill: saveField
    }
    Row{
        anchors.fill: saveField
        anchors.margins: globalMargin
        spacing: globalMargin
        function changeText() {
            pauseButton.buttontext = (pauseButton.state)? "start" : "pause"
            pauseButton.state = !pauseButton.state
        }
        
        Button{
            id: pauseButton
            property bool state: true
            property string buttontext: "pause"
            
            height: parent.height
            text: buttontext
            
            anchors.verticalCenter: parent.Center
            palette{
                button : "#BACCBC"
            }
            onClicked: parent.changeText();
        }

        Rectangle{
            visible:  true
            height:  parent.height
            width: 10
            color: "#584D44"
        }

        CheckBox{
            anchors.leftMargin: globalMargin*2
            text: "CPU"
        }
        CheckBox{
            anchors.leftMargin: globalMargin*2
            text: "RAM"
        }
        CheckBox{
            anchors.leftMargin: globalMargin*2
            text: "VRAM"
        }
        CheckBox{
            anchors.leftMargin: globalMargin*2
            text: "NETW"
        }

        Rectangle{
            visible:  true
            height:  parent.height
            width: 10
            color: "#584D44"
        }

    }
}
