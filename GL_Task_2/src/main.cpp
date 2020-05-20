#include "include/head.h"
#include "include/widget.h"

#include <QApplication>

CPUCounter cpu;
RAMCounter ram;

using namespace std;

int main(int argc, char *argv[])
{
    //   QApplication a(argc, argv);
    //    Widget w;

    int i = 10;

    cout << "RAM total\t" << ram.getTotalMB() << endl;

    while (i--){
        cout << "CPU: "<< cpu.getUsage() << endl;
        cout << "RAM: "<< ram.getUsage() << endl;
        Sleep(1000);
    }
    //    w.show();
    //    return a.exec();
    return  1;
}

