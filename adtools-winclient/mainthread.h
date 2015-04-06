#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QThread>
#include "systemtray.h"
#include "settings.h"
#include "clientnotifierthread.h"

class MainThread: public QObject{
public:
    MainThread(QObject* parent=0);
    ~MainThread();
private:
    SystemTray* trayIconMenu_;
    Settings* programSettings_;
    QThread* notifyThreadObject_;
    ClientNotifierThread* clientNotifierThread_;
};

#endif // MAINTHREAD_H
