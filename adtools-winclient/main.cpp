#include <QApplication>
#include "clientnotifierthread.h"
//#include "commandmonitor.h"
#include<QThread>
#include<QDebug>

void connectToThreadAndStart(QObject* object, QThread* thread){
    object->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), object, SLOT(process()));
    QObject::connect(object, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect(object, SIGNAL(finished()), object, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

int main(int argc, char** argv){
    QApplication app(argc, argv);

    QThread* thread = new QThread;
    ClientNotifierThread notifyTask("192.168.56.1", 9054, 1);
    connectToThreadAndStart(&notifyTask, thread);

    //CommandMonitor monitor;
    return app.exec();
}
