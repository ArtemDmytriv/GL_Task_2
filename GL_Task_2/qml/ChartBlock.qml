import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.3


Component{

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
            z: 2
        }

        function add()
        {
            var line = myChart.createSeries(ChartView.SeriesTypeLine, "Line series", axisX, axisY);

            line.append(model.data);

            axisX.min = 0;
            axisX.max = 5;

            axisY.min = 0;
            axisY.max = 5;
        }

        ChartView{

            id: chartView
            antialiasing: true
            width: chartBlock.width
            height: chartBlock.height

            ValueAxis {
                id: axisY
                gridVisible: true
                tickCount: 5
                min: 0
                max: 1
            }

            ValueAxis {
                id: axisX
                min: 0
                max: 1
                gridVisible: true
                tickCount: 5
            }
        }

    }
}
