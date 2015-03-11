#ifndef HOSTINFO_H
#define HOSTINFO_H
#include <QString>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

class HostInfo{
private:
    HostInfo();                     //User can't create any HostInfo objects.
    static QString mComputerName;
    static QString mUserName;
public:
    static QString getComputerName();
    static QString getUserName();
    ~HostInfo();
};

#endif // HOSTINFO_H
