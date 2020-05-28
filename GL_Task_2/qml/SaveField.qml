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

        Connections {
            target: adapterList
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
            onCheckedChanged: {
                if (checkState === Qt.Checked){
                    elements.saveStates = elements.saveStates | 1
                }
                else{
                    elements.saveStates = elements.saveStates & 14
                }
            }
        }
        CheckBox{
            anchors.leftMargin: globalMargin*2
            text: "RAM"
            onCheckedChanged: {
                if (checkState === Qt.Checked){
                    elements.saveStates = elements.saveStates | 2
                }
                else{
                    elements.saveStates = elements.saveStates & 13
                }
            }
        }
        CheckBox{
            anchors.leftMargin: globalMargin*2
            text: "VRAM"
            onCheckedChanged: {
                if (checkState == Qt.Checked){
                    elements.saveStates = elements.saveStates | 4
                }
                else{
                    elements.saveStates = elements.saveStates & 11
                }
            }
        }
        CheckBox{
            anchors.leftMargin: globalMargin*2
            text: "NETW"
            onCheckedChanged: {
                if (checkState == Qt.Checked){
                    elements.saveStates = elements.saveStates | 8
                }
                else{
                    elements.saveStates = elements.saveStates & 7
                }
            }
        }

        Rectangle{
            visible:  true
            height:  parent.height
            width: 10
            color: "#584D44"
        }

        Button{
            id: saveButton
            property bool state: true
            property string buttontext: "save"

            height: parent.height
            text: buttontext

            anchors.verticalCenter: parent.Center
            palette{
                button : "#BACCBC"
            }
            onClicked: {
                console.log(elements.saveStates)
                elements.saveProc();
            }
        }
        Column{
            id: sliderCol
            height: parent.height

            Slider{

                id: slider
                snapMode: "SnapAlways"
                stepSize: 1
                from: 1
                to: elements.curTime
                onValueChanged: {
                    sliderText.text = value.toString() + " seconds"
                }

            }
            Text{
                id: sliderText
                text: "0" + " seconds"
            }

        }


    }
}
