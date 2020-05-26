#include "include/head.h"
#include "UtilClass.h"
#include "cpuinfo.h"
#include "raminfo.h"
#include "networkinfo.h"

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

//    int i = 5;
//    cout << "RAM total\t" << ram.getTotalMB() << endl;

//    while (i--){
//        cout << "CPU: "<< cpu.getUsage() << endl;
//        cout << "RAM: "<< ram.getUsage() << endl;
//        Sleep(1000);
//    }

    CPUInfo * cpu = new CPUInfo;
    RAMInfo * ram = new RAMInfo;
    NetworkInfo * ntw = new NetworkInfo;

    cout << cpu->getThreads() << endl;
    cout << cpu->getArch() << endl;
    cout << cpu->getCpuName() << endl;
    cout << endl;

    cout << ram->getUsage() << endl;
    cout << endl;

    cout << ntw->getUsage() << endl;
    cout << endl;

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                        if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
                    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

