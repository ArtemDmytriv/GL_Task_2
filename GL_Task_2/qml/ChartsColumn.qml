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
            cellHeight: backgroundCharts.height / 3 - globalMargin

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
                    property real last : 0

                    Item{
                        anchors.left: parent.left
                        anchors.leftMargin: globalMargin
                        Text{
                            anchors.fill: parent
                            text: model.name
                            font{
                                styleName: "Calibri"
                                pointSize: 10
                            }

                        }
                        z: 2
                    }

                    Item {
                        anchors.right: parent.right
                        anchors.rightMargin: (Boolean(model.type))? globalMargin * 8 : globalMargin * 12
                        Text{
                            color: Qt.darker("Green", 1.5)
                            anchors.fill: parent
                            text: (Boolean(model.type))? ((last / model.max) * 100).toFixed(2).toString() + "%": last.toFixed(2).toString() + "kb/s"
                            font{
                                bold: true
                                styleName: "Light Calibri"
                                pointSize: 10
                            }

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

                               //console.log("ItemUpdated")
                               var lst = model.data;

                               lineSeries.append(lst.length - 1, lst[lst.length - 1]);
                               elements.curTime = lst.length - 1
                               chartBlock.last = lst[lst.length - 1]

                               axisX.min = elements.curTime - 40;
                               axisX.max = elements.curTime;

                               axisY.min = 0;
                               axisY.max = Math.round(model.max);
                            }
                        }

                        AreaSeries{
                            id: areaSeries
                            axisX: axisX
                            axisY: axisY
                            color: "#8EA8C3"
                            borderWidth: 2
                            borderColor: Qt.darker(color, 2)
                            upperSeries: LineSeries{
                                id: lineSeries
                            }
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
