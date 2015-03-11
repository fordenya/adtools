#ifndef CLIENTNOTIFYMONITOR_H
#define CLIENTNOTIFYMONITOR_H
#include <QThread>
#include <QString>
#include "datagramreceiver.h"

class ClientNotifyMonitor: public QObject{
    Q_OBJECT
public:
    ClientNotifyMonitor(QObject* parent=0);
    ~ClientNotifyMonitor();
public slots:
    void processDatagram(QString addr, QString data);
private:
    DatagramReceiver* mReceiver;
};

#endif // CLIENTNOTIFYMONITOR_H
