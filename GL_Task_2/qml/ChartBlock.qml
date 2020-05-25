import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.3

Rectangle {
    id: chartBlock
    color: "#f1d59d"
    width: (grid.width - globalMargin) / grid.rows
    height: (grid.height - globalMargin) / grid.columns

//    ChartView{
//        antialiasing: true
//        width: grid.width / 2 - globalMargin
//        height: grid.height / 3 - globalMargin
//    }
}
