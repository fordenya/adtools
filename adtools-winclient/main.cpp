#include <QApplication>
#include "mainthread.h"
#include<QDebug>

int main(int argc, char** argv){
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    MainThread mainThread;
    return app.exec();
}
