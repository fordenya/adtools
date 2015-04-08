#include "mainthread.h"


void connectToThreadAndStart(QObject* object, QThread* thread){
    object->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), object, SLOT(process()));
    QObject::connect(object, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect(object, SIGNAL(finished()), object, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}


MainThread::MainThread(QObject* parent)
    :QObject(parent){
    programSettings_=new Settings(this);
    trayIconMenu_=new SystemTray(this);
    notifyThreadObject_=new QThread();
    SettingsData settingsData=programSettings_->getSettingsData();
    clientNotifierThread_=new ClientNotifierThread(
                settingsData.getServerIp(),
                settingsData.getServerPort(),
                settingsData.getInterval(),
                settingsData.getNotificationStatus());
    connectAllSignalsAndSlots();
}

MainThread::~MainThread(){

}

void MainThread::changeThreadData(SettingsData newData){
    clientNotifierThread_->changeInterval(newData.getInterval());
}

void MainThread::changeServerData(SettingsData newData){
    clientNotifierThread_->changeServerData(newData.getServerIp(), newData.getServerPort());
}

void MainThread::exit(){
    clientNotifierThread_->finish();
}

void MainThread::connectAllSignalsAndSlots(){
    connectToThreadAndStart(clientNotifierThread_, notifyThreadObject_);
    connect(trayIconMenu_, SIGNAL(quit()), clientNotifierThread_, SLOT(finish()));
    connect(trayIconMenu_, SIGNAL(showSettings()), programSettings_, SLOT(showUi()));
    connect(programSettings_, SIGNAL(threadStateIsChanged(bool)), clientNotifierThread_, SLOT(changeState(bool)));
    connect(programSettings_, SIGNAL(threadDataIsChanged(SettingsData)), this, SLOT(changeThreadData(SettingsData)));
    connect(programSettings_, SIGNAL(serverDataIsChanged(SettingsData)), this, SLOT(changeServerData(SettingsData)));
    connect(this, SIGNAL(finishThread()), clientNotifierThread_, SLOT(finish()));
    connect(clientNotifierThread_, SIGNAL(finished()), qApp, SLOT(quit()));
}
