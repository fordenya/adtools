#include "settingsdata.h"

SettingsData::SettingsData()
    : minCorrectPort(1025)
    , maxCorrectPort(65534)
    , minCorrectInterval(10)
    , serverIp_("127.0.0.1")
    , serverPort_(0)
    , interval_(minCorrectInterval)
    , notificationStatus_(false){
}

SettingsData::SettingsData(QString ip, int port, int interval, bool notificationStatus)
    : minCorrectPort(1025)
    , maxCorrectPort(65534)
    , minCorrectInterval(10){
    setServerIp(ip);
    setServerPort(port);
    setInterval(interval);
    setNotificationStatus(notificationStatus);
}

SettingsData::~SettingsData(){

}

void SettingsData::setNotificationStatus(const bool status){
    notificationStatus_=status;
}

QString SettingsData::getServerIp() const{
    return serverIp_.toString();
}

void SettingsData::setServerIp(const QString& strAddress){
    bool result=serverIp_.setAddress(strAddress);
    if (!result){
        throw BadInputData("Mistyped Ip address");
    }
}

int SettingsData::getServerPort() const{
    return serverPort_;
}

void SettingsData::setServerPort(const int port){
    if (port<minCorrectPort || port >maxCorrectPort){
        QString strError="Mistyped port number. It must be Integer number between "
                +QString::number(minCorrectPort)+" and "+QString::number(maxCorrectPort);
        throw BadInputData(strError.toStdString());
    }
    serverPort_=port;
}

int SettingsData::getInterval() const{
    return interval_;
}

void SettingsData::setInterval(const int interval){
    if (interval<minCorrectInterval){
        QString strError="Mistyped sending interval. It must be Integer number grater than "
                +QString::number(minCorrectInterval);
        throw BadInputData(strError.toStdString());
    }
    interval_=interval;
}

bool SettingsData::getNotificationStatus() const{
    return notificationStatus_;
}
