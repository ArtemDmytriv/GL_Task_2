import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.3

Component{
    id: delegate
    Rectangle {
        id: chartBlock
        color: "#f1d59d"
        width: grid.cellWidth - globalMargin
        height: grid.cellHeight - globalMargin
        border.color: "#c4a972"
        border.width: 2

        Text{
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: name + ":"
            font.pointSize: 10
        }
    //    ChartView{
    //        antialiasing: true
    //        width: grid.width / 2 - globalMargin
    //        height: grid.height / 3 - globalMargin
    //    }
    }
}
