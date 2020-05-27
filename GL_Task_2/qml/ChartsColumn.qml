import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.3

Item{
    id: chartsItem

    Rectangle{
        id: backroundCharts
        anchors.fill : chartsItem
        color: "#F4EBD9"

        GridView{
            id: grid
            cellWidth: backroundCharts.width / 2 - globalMargin
            cellHeight: backroundCharts.height / 2

            anchors.fill : backroundCharts
            anchors.margins: globalMargin

            model: model
            delegate: delegate

            ChartBlock{
                id: delegate
            }

            UtilityModel {
                id: model
            }
        }
    }
}
