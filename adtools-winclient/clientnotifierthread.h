#ifndef CLIENTNOTIFIERTHREAD_H
#define CLIENTNOTIFIERTHREAD_H
#include<QtCore>
#include<QUdpSocket>
#include<QString>
#include<QMutex>

class ClientNotifierThread: public QObject{
    Q_OBJECT
public:
    ClientNotifierThread(QString host, int port, int interval, bool status, QObject *parent=0);
    ~ClientNotifierThread();
public slots:
    void process();
    void finish();
    void changeServerData(QString host, int port);
    void changeInterval(int interval);
    void changeState(bool);
    void timerOverflow();
signals:
    void finished();
private:
    void sendNotify(QString str);
    QTimer* timer_;
    QUdpSocket* udpSocket_;
    QHostAddress serverAddress_;
    qint16 serverPort_;
    int sendInterval_;
    bool isRunning_;
    bool isSuspended_;
    QMutex dataProtectionMutex_;
};

#endif // CLIENTNOTIFIERTHREAD_H
