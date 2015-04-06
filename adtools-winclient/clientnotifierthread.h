#ifndef CLIENTNOTIFIERTHREAD_H
#define CLIENTNOTIFIERTHREAD_H
#include<QtCore>
#include<QUdpSocket>
#include<QString>
#include<QMutex>

class ClientNotifierThread: public QObject{
    Q_OBJECT
public:
    ClientNotifierThread(QString host, int port, int interval=10, QObject *parent=0);
    ~ClientNotifierThread();
public slots:
    void process();
    void finish();
    void changeInterval(int interval);
signals:
    void finished();
private:
    void sendNotify(QString str);
    QUdpSocket* udpSocket_;
    QHostAddress serverAddress_;
    qint16 serverPort_;
    int sendInterval_;
    // need to protect with mutex,
    // if other thread will can change current thread state (stop, pause, ...)
    bool isRunning_;
    QMutex dataProtectionMutex_;
};

#endif // CLIENTNOTIFIERTHREAD_H
