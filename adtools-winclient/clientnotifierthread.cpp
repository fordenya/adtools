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
    mUdpSocket_=new QUdpSocket(this);
    mServerAddress_.setAddress(host);
    mServerPort_=port;
    mSendInterval_=interval;
    mIsRunning_=true;
}

ClientNotifierThread::~ClientNotifierThread(){

}

void ClientNotifierThread::process(){
    while(mIsRunning_){
        QByteArray preparedData=transform( {HostInfo::getComputerName(), HostInfo::getUserName()} );
        sendNotify(preparedData);
        QThread::sleep(qAbs(mSendInterval_));
    }
    emit finished();
}

void ClientNotifierThread::sendNotify(QString str){
    //Need to think: if str.length()>512 - do something ))
    mUdpSocket_->writeDatagram(str.toUtf8(), mServerAddress_, mServerPort_);
    qDebug()<<"Sended...  "<<str;
}
