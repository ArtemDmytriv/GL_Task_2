#include "include/head.h"

#include "cpuinfo.h"
#include "raminfo.h"
#include "networkinfo.h"

#include "adaptermodel.h"
#include "adapterlist.h"
#include "UtilClass.h"

//#include <QIcon>
#include <QtCore>
#include <QApplication>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    //app.setWindowIcon(QIcon("icon.png"));

    qmlRegisterType<AdapterModel>("MyModel", 1, 0, "AdapterModel");
    qmlRegisterUncreatableType<AdapterList>("MyModel", 1, 0, "AdapterList", "should not created");


    UtilClass* ram = new RAMInfo;
    UtilClass* vram = new RAMInfo(hwType::VRAM);
    UtilClass* cpu = new CPUInfo;
    UtilClass* netw = new NetworkInfo;

    AdapterList adapterList;
    adapterList.appendItem(cpu);
    adapterList.appendItem(ram);
    adapterList.appendItem(vram);   
    adapterList.appendItem(netw);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("adapterList", &adapterList);

    //list.debugPrintData();
    //    for(int i = 0; i < 5; i++){
    //        Sleep(1000);
    //        list.updateAllItems();
    //    }
    //list.debugPrintData();

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
        if (engine.rootObjects().isEmpty())
            return -1;

    std::cout << "Wait For Update1\n";
    Sleep(2000);
    adapterList.updateAllItems();

    return app.exec();
}

