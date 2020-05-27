#include "include/head.h"

#include "cpuinfo.h"
#include "raminfo.h"
#include "networkinfo.h"

#include "AdapterUtil.h"
#include "UtilClass.h"

#include <QIcon>
#include <QApplication>
#include <QQmlApplicationEngine>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    //app.setWindowIcon(QIcon("icon.png"));
    QQmlApplicationEngine engine;

    UtilClass* ram = new RAMInfo;
    UtilClass* cpu = new CPUInfo;
    UtilClass* netw = new NetworkInfo;

    vector<AdapterUtil*> utils;
    utils.push_back( new AdapterUtil(0, cpu, TIME) );
    utils.push_back( new AdapterUtil(0, ram, TIME) );
    utils.push_back( new AdapterUtil(0, netw, TIME) );

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

