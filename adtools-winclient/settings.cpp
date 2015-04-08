#include "settings.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QDebug>

Settings::Settings(QObject* parent): QObject(parent)
     ,ui_(new Ui::SettingsDialog)
     , settingsFileName_("settings.txt"){
    readFromFile();
    uiDialog=new QDialog;
    ui_->setupUi(uiDialog);
    Qt::CheckState currentState=data_.getNotificationStatus() ? Qt::Checked : Qt::Unchecked;
    ui_->notifyStateCheckBox->setCheckState(currentState);
    ui_->serverIpLine->setText(data_.getServerIp());
    ui_->serverPortLine->setText(QString::number(data_.getServerPort()));
    ui_->intervalLine->setText(QString::number(data_.getInterval()));
    connectAllSignalsAndSlots();
}

Settings::~Settings(){
    delete ui_;
}

SettingsData Settings::getSettingsData(){
    return data_;
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
        try{
            QString serverIp;
            in>>serverIp;
            data_.setServerIp(serverIp);

            int serverPort;
            in>>serverPort;
            data_.setServerPort(serverPort);

            int interval;
            in>>interval;
            data_.setInterval(interval);

            int notificationStatus;
            in>>notificationStatus;
            data_.setNotificationStatus(notificationStatus);
        }
        catch (SettingsData::BadInputData& e){
            QMessageBox::warning(0, "Read file error!", "Error reading settings from configuration file. File may be broken."
                                    "Please contact your system administrator!");
            return false;
        }
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
    out<<data_.getServerIp()<<"\n";
    out<<data_.getServerPort()<<"\n";
    out<<data_.getInterval()<<"\n";
    // ? need convert to int?
    out<<data_.getNotificationStatus()<<"\n";
    settingsFile.close();
    return true;
}

void Settings::uiDataIsChanged(QString){
    uiDataIsChanged_=true;
}

void Settings::checkChangedData(){
    bool notifyStateUi=ui_->notifyStateCheckBox->checkState();
    QString ipUi=ui_->serverIpLine->text();
    int portUi=ui_->serverPortLine->text().toInt();
    int intervalUi=ui_->intervalLine->text().toInt();
    // Need check, if user input is correct.
    if (notifyStateUi!=data_.getNotificationStatus()){
        data_.setNotificationStatus(notifyStateUi);
        emit threadStateIsChanged(data_.getNotificationStatus());
    }
    if (intervalUi!=data_.getInterval()){
        try{
            data_.setInterval(intervalUi);
        }
        catch (SettingsData::BadInputData& e){
            QMessageBox::warning(0, "Read file error!", QString(e.what()));
            return;
        }
        emit threadDataIsChanged(data_);
    }
    if ((ipUi!=data_.getServerIp()) || (portUi!=data_.getServerPort())){
        try{
            data_.setServerIp(ipUi);
            data_.setServerPort(portUi);
        }
        catch (SettingsData::BadInputData& e){
            QMessageBox::warning(0, "Read file error!", QString(e.what()));
            return;
        }
        emit serverDataIsChanged(data_);
    }
    uiDialog->hide();
    writeToFile();
}

void Settings::showUi(){
    uiDialog->show();
}

void Settings::threadStateIsChangedSlot(int stateInt){
    bool state=stateInt;
    emit threadStateIsChanged(state);
}

void Settings::connectAllSignalsAndSlots(){
    connect(ui_->notifyStateCheckBox, SIGNAL(stateChanged(int)), SLOT(threadStateIsChangedSlot(int)));
    connect(ui_->serverIpLine, SIGNAL(textChanged(QString)), this, SLOT(uiDataIsChanged(QString)));
    connect(ui_->serverPortLine, SIGNAL(textChanged(QString)), this, SLOT(uiDataIsChanged(QString)));
    connect(ui_->intervalLine, SIGNAL(textChanged(QString)), this, SLOT(uiDataIsChanged(QString)));
    connect(ui_->saveButton, SIGNAL(clicked()), this, SLOT(checkChangedData()));
    connect(ui_->closeButton, SIGNAL(clicked()), uiDialog, SLOT(hide()));
}
