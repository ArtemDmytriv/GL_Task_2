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

        Grid{
            id: grid
            rows: 2
            columns: 2
            anchors.fill : backroundCharts
            anchors.margins: globalMargin
            spacing: globalMargin

            ChartBlock {
                id: chartBlock11
            }
            ChartBlock {
                id: chartBlock12
            }
            ChartBlock {
                id: chartBlock21
            }
            ChartBlock {
                id: chartBlock22
            }

        }
    }
}
