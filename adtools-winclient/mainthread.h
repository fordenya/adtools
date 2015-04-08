#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QObject>
#include <QThread>
#include "systemtray.h"
#include "settings.h"
#include "settingsdata.h"
#include "clientnotifierthread.h"

class MainThread: public QObject{
    Q_OBJECT
public:
    MainThread(QObject* parent=0);
    ~MainThread();
public slots:
    void changeThreadData(SettingsData newData);
    void changeServerData(SettingsData newData);
    void exit();
signals:
    void finishThread();
private:
    SystemTray* trayIconMenu_;
    Settings* programSettings_;
    QThread* notifyThreadObject_;
    ClientNotifierThread* clientNotifierThread_;
    void connectAllSignalsAndSlots();
};

#endif // MAINTHREAD_H
