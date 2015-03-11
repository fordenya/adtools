#include "datagramreceiver.h"
#include <iostream>
#include <string>

DatagramReceiver::DatagramReceiver(int port, QObject *parent)
    :QObject(parent){
    mUdpSocket=new QUdpSocket(this);
    mLocalPort=port;
    mUdpSocket->bind(mLocalPort);
    connect(mUdpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void DatagramReceiver::readPendingDatagrams(){
    while (mUdpSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(mUdpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mUdpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        emit datagramReseived(sender.toString(), QString(datagram));
    }
}

DatagramReceiver::~DatagramReceiver(){

}
