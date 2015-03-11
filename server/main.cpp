#include <QApplication>
#include "clientnotifymonitor.h"
#include "datagramreceiver.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    ClientNotifyMonitor monitor;
    app.exec();
}
