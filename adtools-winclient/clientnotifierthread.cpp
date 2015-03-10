#include "clientnotifierthread.h"
#include "hostinfo.h"
#include <QtGlobal>
#include <iostream>

ClientNotifierThread::ClientNotifierThread(QString host, int port, QObject *parent)
    :QThread(parent){
    mUdpSocket=new QUdpSocket(this);
    mServerAddress.setAddress(host);
    mServerPort=port;
    mSendInterval=10;
}

ClientNotifierThread::~ClientNotifierThread(){

}

void ClientNotifierThread::run(){
    while(mIsRunning){
        sendNotify(HostInfo::getComputerName());
        sleep(qAbs(mSendInterval));
    }
}

void ClientNotifierThread::sendNotify(QString str){
    //Need to think: if str.length()>512 - do somethink))
    //startCriticalSection
    //lock a mutex
    mUdpSocket->writeDatagram(str.toUtf8(), mServerAddress, mServerPort);
    std::cout<<"Sended..."<<std::endl;
    //unlock a mutex
    //end critical section
}

