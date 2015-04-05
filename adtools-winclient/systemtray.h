#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QMenu>
#include <QSystemTrayIcon>

class SystemTray : public QObject{
    Q_OBJECT
public:
    SystemTray(QWidget* wgt=0);
    ~SystemTray();
private:
    QSystemTrayIcon* mTrayIcon_;
    QMenu* mTrayMenu_;
    QIcon mIcon_;
};

#endif // SYSTEMTRAY_H
