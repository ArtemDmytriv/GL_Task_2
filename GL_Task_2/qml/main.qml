import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    id: root
    width: 900
    height: 600
    minimumWidth: 450
    minimumHeight: 300

    visible: true
    title: "Loadability manager"
    property int globalMargin: 10

    Background {
        id: background
    }

    ColumnLayout {
        id: elements
        objectName: "elementsObj"
        anchors.fill: parent
        anchors.margins: 2 * globalMargin
        //anchors.verticalCenterOffset: 100
        anchors.verticalCenter: parent.verticalCenter
        spacing: globalMargin

        Item {
            id: header
            visible:  true
            Layout.preferredWidth: elements.width
            Layout.preferredHeight: 70
            Rectangle {
                color: "#F4EBD9"
                anchors.fill: header
            }
            Row{
                anchors.fill: header
                anchors.margins: globalMargin

                Button{
                    property bool launched: true
                    height: parent.height
                    text: "pause"
                    anchors.left: parent.left
                    palette{
                        button : "#BACCBC"
                    }
                    onClicked: {
                        text : launched? "start" : "pause"
                        launched : !launched
                    }
                }
            }
        }

        Item {
            id: lineSep
            visible:  true
            Layout.preferredWidth:  elements.width
            Layout.preferredHeight: 10
            Rectangle {
                color: "#584D44"
                anchors.fill: lineSep
            }
        }

        ChartsColumn {
            id: chartsItem
            objectName: "chartsItemObj"
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
        }
    }
}

