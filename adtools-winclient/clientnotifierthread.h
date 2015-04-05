#ifndef CLIENTNOTIFIERTHREAD_H
#define CLIENTNOTIFIERTHREAD_H
#include<QtCore>
#include<QUdpSocket>
#include<QString>

class ClientNotifierThread: public QObject{
    Q_OBJECT
public:
    ClientNotifierThread(QString host, int port, int interval=10, QObject *parent=0);
    ~ClientNotifierThread();
public slots:
    void process();
signals:
    void finished();
private:
    void sendNotify(QString str);
    QUdpSocket* mUdpSocket_;
    QHostAddress mServerAddress_;
    qint16 mServerPort_;
    int mSendInterval_;
    // need to protect with mutex,
    // if other thread will can change current thread state (stop, pause, ...)
    bool mIsRunning_;
};

#endif // CLIENTNOTIFIERTHREAD_H
