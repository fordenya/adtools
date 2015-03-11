#include "hostinfo.h"

QString HostInfo::mComputerName="";
QString HostInfo::mUserName="";

HostInfo::HostInfo(){

}

QString HostInfo::getComputerName(){
    #ifdef Q_OS_WIN
    if (mComputerName==""){
        wchar_t buffer[31+1];
        DWORD size;
        size=sizeof(buffer);
        GetComputerName(buffer, &size);
        mComputerName=QString::fromWCharArray(buffer);
    }
    #endif
    return mComputerName;
}

QString HostInfo::getUserName(){
    #ifdef Q_OS_WIN
    if (mUserName==""){
        wchar_t buffer[31+1];
        DWORD size;
        size=sizeof(buffer);
        GetUserName(buffer, &size);
        mUserName=QString::fromWCharArray(buffer);
    }
    #endif
    return mUserName;
}

HostInfo::~HostInfo(){

}

