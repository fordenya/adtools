#include "systemtray.h"
#include <QAction>
#include <QApplication>


SystemTray::SystemTray(QWidget* wgt): QObject(wgt){
    QAction* actShowSettings = new QAction("Settings", this);
    connect(actShowSettings, SIGNAL(triggered()), SIGNAL(showSettings()));
    QAction* actQuit = new QAction("Quit", this);
    connect(actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    icon_=QIcon(":/icons/res/netIcon.ico");
    trayIcon_=new QSystemTrayIcon(icon_, this);
    trayMenu_=new QMenu();
    trayMenu_->addAction(actQuit);
    trayIcon_->setContextMenu(trayMenu_);
    trayIcon_->setToolTip("Adtools Winclient application.");
    trayIcon_->show();
}

SystemTray::~SystemTray(){
    delete trayMenu_;
}
