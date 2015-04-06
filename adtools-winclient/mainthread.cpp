#include "mainthread.h"
#include "systemtray.h"

MainThread::MainThread(QObject* parent)
    :QObject(parent){
    trayIconMenu_=new SystemTray(this);
    programSettings_=new Settings(this);
    notifyThreadObject_=new QThread(this);

}

MainThread::~MainThread(){

}

