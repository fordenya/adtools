#include "clientnotifierthread.h"
#include "hostinfo.h"
#include <QtGlobal>
#include <iostream>
#include <initializer_list>


QByteArray transform(QStringList strList){
    const QString separator="%%";
    return strList.join(separator).toUtf8();
}


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
        QByteArray preparedData=transform( {HostInfo::getComputerName(), HostInfo::getUserName()} );
        sendNotify(preparedData);
        sleep(qAbs(mSendInterval));
    }
}

void ClientNotifierThread::sendNotify(QString str){
    //Need to think: if str.length()>512 - do somethink ))
    mUdpSocket->writeDatagram(str.toUtf8(), mServerAddress, mServerPort);
    std::cout<<"Sended..."<<std::endl;
}
