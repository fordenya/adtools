#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QMenu>
#include <QSystemTrayIcon>

class SystemTray : public QObject{
    Q_OBJECT
public:
    SystemTray(QObject* wgt=0);
    ~SystemTray();
signals:
    void showSettings();
    void quit();
private:
    QSystemTrayIcon* trayIcon_;
    QMenu* trayMenu_;
    QIcon icon_;
};

#endif // SYSTEMTRAY_H
