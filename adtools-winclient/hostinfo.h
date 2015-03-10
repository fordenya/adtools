#ifndef HOSTINFO_H
#define HOSTINFO_H
#include <QString>
#ifdef Q_OS_WIN
#include <windows.h>
//#elif defined(Q_WS_X11)
#endif
class HostInfo{
private:
    HostInfo();
    static QString mComputerName;
public:
    static QString getComputerName();
    static QString getUserName();
    ~HostInfo();
};

#endif // HOSTINFO_H
