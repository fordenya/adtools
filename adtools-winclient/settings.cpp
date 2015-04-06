#include "settings.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Settings::Settings(): ui_(new Ui::SettingsDialog)
                    , settingsFileName_("settings2.txt"){
    uiDialog=new QDialog;
    ui_->setupUi(uiDialog);
    readFromFile();
}

Settings::~Settings(){
    delete ui_;
}

bool Settings::readFromFile(){
    QFile settingsFile(settingsFileName_);
    if (settingsFile.exists()){
        if (!settingsFile.open(QIODevice::ReadOnly)){
            QMessageBox::warning(0, "Read file error!", "Error reading the configuration file. Do you have correct permissions? "
                                    "Please set correct settings (using tray menu) or contact your system administrator!");
            return false;
        }
        QTextStream in(&settingsFile);
        int notifiesStatus=0;
        in>>notifiesStatus;
        notifiesStatus ? notifiesIsEnabled_=true : notifiesIsEnabled_=false;
        in>>notifyInterval_;
        in>>ip_;
        in>>port_;
        settingsFile.close();
        return true;
    }
    return false;
}

bool Settings::writeToFile(){
    QFile settingsFile(settingsFileName_);
    if (!settingsFile.open(QIODevice::WriteOnly)){
        QMessageBox::warning(0, "Write file error!", "Error writing the configuration to the file. Do you have correct permissions? "
                                "Please, remember this message and contact your system administrator!");
        return false;
    }
    QTextStream out(&settingsFile);
    notifiesIsEnabled_ ? out<<1<<"\n" : out<<0<<"\n";
    out<<notifyInterval_<<"\n";
    out<<ip_<<"\n";
    out<<port_<<"\n";
    settingsFile.close();
    return true;
}
