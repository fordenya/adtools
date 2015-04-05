#include "systemtray.h"
#include <QAction>
#include <QApplication>


SystemTray::SystemTray(QWidget* wgt): QObject(wgt){
    QAction* actQuit = new QAction("Quit", this);
    connect(actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    mIcon_=QIcon(":/icons/res/netIcon.ico");
    mTrayIcon_=new QSystemTrayIcon(mIcon_, this);
    mTrayMenu_=new QMenu();
    mTrayMenu_->addAction(actQuit);
    mTrayIcon_->setContextMenu(mTrayMenu_);
    mTrayIcon_->setToolTip("Adtools Winclient application.");
    mTrayIcon_->show();
}

SystemTray::~SystemTray(){
    delete mTrayMenu_;
}
