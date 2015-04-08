#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDialog>
#include "settingsdata.h"
#include "ui_settings_dialog.h"

namespace Ui{
    class SettingsDialog;
}

class Settings: public QObject{
    Q_OBJECT
public:
    Settings(QObject* parent=0);
    ~Settings();
    SettingsData getSettingsData();
public slots:
    bool readFromFile();
    bool writeToFile();
    void uiDataIsChanged(QString);
    void checkChangedData();
    void showUi();
    void threadStateIsChangedSlot(int);
signals:
    void serverDataIsChanged(SettingsData);
    void threadDataIsChanged(SettingsData);
    void threadStateIsChanged(bool);
private:
    void connectAllSignalsAndSlots();
    QDialog* uiDialog;
    Ui::SettingsDialog *ui_;
    bool uiDataIsChanged_;
    const QString settingsFileName_;
    //bool notifiesIsEnabled_=true;
    SettingsData data_;
};

#endif // SETTINGS_H
