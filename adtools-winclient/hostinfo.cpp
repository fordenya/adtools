#include "hostinfo.h"

QString HostInfo::mComputerName="";

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

HostInfo::~HostInfo(){

}

