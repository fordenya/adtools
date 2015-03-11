#include <QApplication>
#include "clientnotifierthread.h"
//#include "hostinfo.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    ClientNotifierThread thread("192.168.0.192", 9054);
    thread.run();
    return app.exec();
//    qDebug()<<"Computer name: "<<HostInfo::getComputerName();
//    qDebug()<<"User name: "<<HostInfo::getUserName();
//    return 0;
}
