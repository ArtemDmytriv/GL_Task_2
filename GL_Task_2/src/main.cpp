#include "include/head.h"

#include "cpuinfo.h"
#include "raminfo.h"
#include "networkinfo.h"

#include "adaptermodel.h"
#include "adapterlist.h"
#include "UtilClass.h"

//#include <QIcon>
#include <QtCore>
#include <QMetaObject>
#include <QApplication>
#include <QQmlComponent>
#include <QQmlApplicationEngine>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    //app.setWindowIcon(QIcon("icon.png"));

    QQmlApplicationEngine engine;

    /*
    QQmlComponent comp(&engine, QUrl("qrc:/qml/main.qml"));
    QObject * pobj = comp.create();
    pobj->setProperty("visible", "true");
    */

    qmlRegisterType<AdapterModel>("MyModel", 1, 0, "UtilModel");

    UtilClass* ram = new RAMInfo;
    UtilClass* cpu = new CPUInfo;
    UtilClass* netw = new NetworkInfo;

    vector<UtilClass*> utils;
    utils.push_back(ram);
    utils.push_back(cpu);
    utils.push_back(netw);

    for(auto elem : utils){
        cout << elem->getName() << endl;
    }

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                        if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
                    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

