#include "widget.h"
#include <QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;

    if (argc>1){
        w.conf["ModelFile"]=argv[1];
        w.conf["ShaderFile"]=argv[2];
    }

    w.show();

    return a.exec();
}
