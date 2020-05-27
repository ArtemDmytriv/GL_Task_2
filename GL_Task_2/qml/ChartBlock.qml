import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.3


Component{
    id: delegate
    Rectangle {
        id: chartBlock
        color: "#fff6e2"
        width: grid.cellWidth - globalMargin
        height: grid.cellHeight - globalMargin * 2
        border.color: Qt.darker("#fff6e2", 1.5)
        border.width: 2

        Text{
            anchors.left: parent.left
            anchors.leftMargin: globalMargin
            text: name
            font{
                styleName: "Calibri"
                pointSize: 10
            }
        }



    //    ChartView{
    //        antialiasing: true
    //        width: grid.width / 2 - globalMargin
    //        height: grid.height / 3 - globalMargin
    //    }
    }
}
