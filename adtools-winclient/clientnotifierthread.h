#ifndef CLIENTNOTIFIERTHREAD_H
#define CLIENTNOTIFIERTHREAD_H
#include<QThread>
#include<QtCore>
#include<QUdpSocket>
#include<QString>

class ClientNotifierThread: QThread{
    Q_OBJECT
public:
    ClientNotifierThread(QString host, int port, QObject *parent=0);
    ~ClientNotifierThread();
    void run();
private:
    void sendNotify(QString str);
    QUdpSocket* mUdpSocket;
    QHostAddress mServerAddress;
    qint16 mServerPort;
    int mSendInterval;
    //need to protect with mutex
    bool mIsRunning;
};

#endif // CLIENTNOTIFIERTHREAD_H
