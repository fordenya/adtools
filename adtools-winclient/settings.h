#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDialog>
#include "ui_settings_dialog.h"

namespace Ui{
    class SettingsDialog;
}

class Settings: public QObject{
    Q_OBJECT
public:
    Settings();
    ~Settings();
public slots:
    bool readFromFile();
    bool writeToFile();
private:
    QDialog* uiDialog;
    Ui::SettingsDialog *ui_;
    bool uiWasChanged_;
    const QString settingsFileName_;
    bool notifiesIsEnabled_=true;
    int notifyInterval_=10;
    QString ip_="192.168.10.100";
    int port_=1001;
};

#endif // SETTINGS_H
