#ifndef SETTINGSDATA_H
#define SETTINGSDATA_H
#include <QString>
#include <QHostAddress>
#include <exception>


class SettingsData{
public:
    class BadInputData: public std::invalid_argument{
    public:
        BadInputData(const std::string& what_arg): std::invalid_argument(what_arg){}
        BadInputData(const char* what_arg): std::invalid_argument(what_arg){}
    };
    SettingsData();
    SettingsData(QString, int, int, bool);
    ~SettingsData();
    QString getServerIp() const;
    void setServerIp(const QString&);
    int getServerPort() const;
    void setServerPort(const int);
    int getInterval() const;
    void setInterval(const int);
    bool getNotificationStatus() const;
    void setNotificationStatus(const bool);
private:
    const int minCorrectPort;
    const int maxCorrectPort;
    const int minCorrectInterval;
    QHostAddress serverIp_;
    int serverPort_;
    int interval_;
    bool notificationStatus_;
};

#endif // SETTINGSDATA_H
