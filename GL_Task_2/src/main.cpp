#include "include/head.h"
#include "include/widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    std::string str;

    str.push_back('4');

    printf("%s\n", str.c_str());

    w.show();
    return a.exec();
}
