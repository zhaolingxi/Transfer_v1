#include "settingdata.h"
#include<QStringList>

QString _serverip="127.0.0.1";
QString _username="";
QString _password="";
int _ipport=8000;

bool SettingData::isLegal(SettingDataType itype, QString &istr)
{
    switch(itype)
    {
    case SettingDataType::SEVERIP:
    {
        QStringList qlist= istr.split(".");
        int count=4;
        for(QString s:qlist)
        {
            int num=s.toInt();
            count--;
            if(num>255 || num<0 || count<0)
            {
                return false;
            }
        }
        break;
    }
    case SettingDataType::USERNAME:
    {
        break;
    }
    case SettingDataType::PASSWORD:
    {
        break;
    }
    case IPPORT:
    {
        int port=istr.toInt();
        if(port<0 || port>65536)
        {
            return false;
        }
        break;
    }
    }
    return true;
}
