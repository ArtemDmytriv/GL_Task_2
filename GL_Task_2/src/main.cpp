#include "include/head.h"

#include "cpuinfo.h"
#include "raminfo.h"
#include "networkinfo.h"

#include "adaptermodel.h"
#include "adapterlist.h"
#include "UtilClass.h"

//#include <QIcon>
#include <QtCore>
#include <QQuickItem>
#include <QApplication>
#include <QQmlProperty>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace std;

void mySleep(int ms){
#ifdef _WIN32
    Sleep(ms);
#elif __linux__
    sleep(ms/1000);
#endif
}

void funcThread(QObject* elems, AdapterList* adap){
    for (;;){
        mySleep(1000);
        if (QQmlProperty::read(elems, "isRun").toBool() && adap)
            adap->updateAllItems();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    //app.setWindowIcon(QIcon("icon.png"));

    qmlRegisterType<AdapterModel>("MyModel", 1, 0, "AdapterModel");
    qmlRegisterUncreatableType<AdapterList>("MyModel", 1, 0, "AdapterList", "should not created");


    UtilClass* ram = new RAMInfo;
    ram->init();
    UtilClass* vram = new RAMInfo(hwType::VRAM);
    vram->init();
    UtilClass* cpu = new CPUInfo;
    cpu->init();
    UtilClass* netw = new NetworkInfo;
    netw->init();

    AdapterList adapterList;
    adapterList.appendItem(cpu);
    adapterList.appendItem(ram);
    adapterList.appendItem(vram);
    adapterList.appendItem(netw);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("adapterList", &adapterList);

//    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    QQmlComponent comp(&engine, QUrl("qrc:/qml/main.qml"));
    QObject* pobj = comp.create();
    QObject* elems = pobj->findChild<QObject*>("elementsObj");

    std::thread th(funcThread, elems, &adapterList);

    return app.exec();
    th.join();
}



