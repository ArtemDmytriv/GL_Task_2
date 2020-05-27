import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.3
import MyModel 1.0

Item{
    id: chartsItem

    Rectangle{
        id: backgroundCharts
        objectName: "backgroundChartsObj"
        anchors.fill : chartsItem
        color: "#F4EBD9"

        GridView{
            id: grid
            objectName: "gridObj"
            cellWidth: backgroundCharts.width / 2 - globalMargin
            cellHeight: backgroundCharts.height / 2

            anchors.fill : backgroundCharts
            anchors.margins: globalMargin

            model: UtilModel {}
            delegate: delegate

            ChartBlock{
                id: delegate
            }

        }
    }
}
