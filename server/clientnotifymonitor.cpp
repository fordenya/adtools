#include "clientnotifymonitor.h"

#include <iostream>
#include <string>
#include <iostream>

ClientNotifyMonitor::ClientNotifyMonitor(QObject* parent)
    : QObject(parent){
    mReceiver=new DatagramReceiver(9054, this);
    connect(mReceiver, SIGNAL(datagramReseived(QString, QString)),
            this, SLOT(processDatagram(QString, QString)));
}

ClientNotifyMonitor::~ClientNotifyMonitor(){

}

void ClientNotifyMonitor::processDatagram(QString address, QString data){
    std::wcout<<L"From "<<address.toStdWString()<<" : "<<data.toStdWString()<<std::endl;
}


