import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.3
import MyModel 1.0

Item{
    property alias my_model: backgroundCharts.my_model

    Rectangle{
        id: backgroundCharts
        objectName: "backgroundChartsObj"
        anchors.fill : chartsItem
        color: "#F4EBD9"

        property alias my_model: grid.model

        GridView{
            signal updateGraphs
            onUpdateGraphs: delegate.add()

            id: grid
            objectName: "gridObj"
            cellWidth: backgroundCharts.width / 2 - globalMargin
            cellHeight: backgroundCharts.height / 2 - globalMargin

            anchors.fill : backgroundCharts
            anchors.margins: globalMargin
            clip: true

            model: model

            AdapterModel {
                id: model
                list: adapterList
            }

            delegate: delegate


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
                        text: model.name
                        font{
                            styleName: "Calibri"
                            pointSize: 10
                        }
                        z: 2
                    }

                    ChartView{

                        id: chartView
                        antialiasing: true
                        width: chartBlock.width
                        height: chartBlock.height

                        legend.visible : false

                        Connections {
                            target: adapterList
                            onItemUpdated: {

                               console.log("ItemUpdated")
                               var lst = model.data;

                               lineSeries.append(lst.length - 1, lst[lst.length - 1]);

                               axisX.min = 0;
                               axisX.max = 100;

                               axisY.min = 0;
                               axisY.max = model.max;
                            }
                        }

                        LineSeries{
                            id: lineSeries
                            axisX: axisX
                            axisY: axisY
                        }

                        ValueAxis {
                            id: axisY
                        }
                        ValueAxis {
                            id: axisX
                        }
                    }

                }
            }

        }
    }
}
