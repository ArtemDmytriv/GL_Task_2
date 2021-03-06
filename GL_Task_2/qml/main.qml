import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    id: root
    width: 1200
    height: 600
    minimumWidth: 900
    minimumHeight: 400

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

        SaveField {
            id: saveField
        }

        property bool isRun: true
        property int curTime: 0
        property int saveStates: 0

        function saveProc(){
            console.log("In save func");
            my_model.saveToFile(curTime, saveStates,"");
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

        property alias my_model: chartsItem.my_model

        ChartsColumn {
            id: chartsItem
            objectName: "chartsItemObj"
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
        }
    }
}

