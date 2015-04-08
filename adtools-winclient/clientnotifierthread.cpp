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


ClientNotifierThread::ClientNotifierThread(QString host, int port, int interval, bool status,  QObject *parent)
    :QObject(parent){
    changeInterval(interval);
    udpSocket_=new QUdpSocket(this);
    //dataProtectionMutex_.lock();
    serverAddress_.setAddress(host);
    serverPort_=port;
    isRunning_=true;
    isSuspended_=!status;
    //dataProtectionMutex_.unlock();
}

ClientNotifierThread::~ClientNotifierThread(){

}

void ClientNotifierThread::process(){
    timer_=new QTimer;
    QObject::connect(timer_, SIGNAL(timeout()), this, SLOT(timerOverflow()));
    connect(this, SIGNAL(finished()), qApp, SLOT(quit()));
    dataProtectionMutex_.lock();
    int interval=sendInterval_;
    dataProtectionMutex_.unlock();
    timer_->start(interval);
}

void ClientNotifierThread::finish(){
    dataProtectionMutex_.lock();
    isRunning_=false;
    dataProtectionMutex_.unlock();
    emit finished();
}

void ClientNotifierThread::changeServerData(QString host, int port){
    dataProtectionMutex_.lock();
    serverAddress_.setAddress(host);
    serverPort_=port;
    dataProtectionMutex_.unlock();
}

void ClientNotifierThread::changeInterval(int interval){
    dataProtectionMutex_.lock();
    sendInterval_=interval;
    dataProtectionMutex_.unlock();
}

void ClientNotifierThread::changeState(bool state){
    dataProtectionMutex_.lock();
    isSuspended_=!state;
    dataProtectionMutex_.unlock();
}

void ClientNotifierThread::timerOverflow(){
    if (!isRunning_){
        emit finished();
        return;
    }
    dataProtectionMutex_.lock();
    bool suspended=isSuspended_;
    dataProtectionMutex_.unlock();
    if (!suspended){
        QByteArray preparedData=transform( {HostInfo::getComputerName(), HostInfo::getUserName()} );
        sendNotify(preparedData);
    }
    dataProtectionMutex_.lock();
    int interval=sendInterval_;
    dataProtectionMutex_.unlock();
    timer_->start(interval*1000);           // *1000 - miliseconds to seconds
}

void ClientNotifierThread::sendNotify(QString str){
    //Need to think: if str.length()>512 - do something ))
    udpSocket_->writeDatagram(str.toUtf8(), serverAddress_, serverPort_);
    qDebug()<<"Sended...  "<<str;
}
