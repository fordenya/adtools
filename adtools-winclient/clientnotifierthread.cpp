#include "clientnotifierthread.h"
#include "hostinfo.h"
#include <QThread>
#include <QtGlobal>
#include <iostream>
#include <initializer_list>
#include <QDebug>


QByteArray transform(QStringList strList){
    const QString separator="%%";
    return strList.join(separator).toUtf8();
}


ClientNotifierThread::ClientNotifierThread(QString host, int port, int interval, QObject *parent)
    :QObject(parent){
    changeInterval(interval);
    udpSocket_=new QUdpSocket(this);
    serverAddress_.setAddress(host);
    serverPort_=port;
    dataProtectionMutex_.lock();
    isRunning_=true;
    dataProtectionMutex_.unlock();
}

ClientNotifierThread::~ClientNotifierThread(){

}

void ClientNotifierThread::process(){
    dataProtectionMutex_.lock();
    bool isRunning=isRunning_;
    dataProtectionMutex_.unlock();
    int interval=0;
    while(isRunning){
        QByteArray preparedData=transform( {HostInfo::getComputerName(), HostInfo::getUserName()} );
        sendNotify(preparedData);
        dataProtectionMutex_.lock();
        interval=sendInterval_;
        dataProtectionMutex_.unlock();
        QThread::sleep(interval);
    }
    emit finished();
}

void ClientNotifierThread::finish(){
    dataProtectionMutex_.lock();
    isRunning_=false;
    dataProtectionMutex_.unlock();
    emit finished();
    quit();
}

void ClientNotifierThread::changeInterval(int interval){
    dataProtectionMutex_.lock();
    sendInterval_=interval;
    dataProtectionMutex_.unlock();
}

void ClientNotifierThread::sendNotify(QString str){
    //Need to think: if str.length()>512 - do something ))
    udpSocket_->writeDatagram(str.toUtf8(), serverAddress_, serverPort_);
    qDebug()<<"Sended...  "<<str;
}
