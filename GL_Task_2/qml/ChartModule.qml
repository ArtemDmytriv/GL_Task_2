import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtCharts 2.0

Window {
    id: root
    height: 600
    width: 800
    color: "lightgrey"
    visible: true

    ColumnLayout{
        id: col

        Rectangle{
            color: "blue"
            Layout.preferredHeight: col.height / 2
            Layout.preferredWidth: col.width
        }

        Rectangle{
            color: "blue"
            Layout.preferredHeight: col.height / 2
            Layout.preferredWidth: col.width
        }


//        ChartView {
//            id: chart
//            title: "Line"
//            height: col.height / 2
//            width: col.width

//            antialiasing: true

//            LineSeries {
//                name: "LineSeries"
//                XYPoint { x: 0; y: 0 }
//                XYPoint { x: 1.1; y: 2.1 }
//                XYPoint { x: 1.9; y: 3.3 }
//                XYPoint { x: 2.1; y: 2.1 }
//                XYPoint { x: 2.9; y: 4.9 }
//                XYPoint { x: 3.4; y: 3.0 }
//                XYPoint { x: 4.1; y: 3.3 }
//            }
//        }
    }
}
