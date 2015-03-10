#include <iostream>
#include <QApplication>
#include "clientnotifierthread.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    ClientNotifierThread thread("192.168.0.192", 1000);
    thread.run();
    return app.exec();
}
