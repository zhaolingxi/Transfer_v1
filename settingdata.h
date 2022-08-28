#ifndef SETTINGDATA_H
#define SETTINGDATA_H
#include<QString>

enum SettingDataType
{
    SEVERIP=0,
    USERNAME,
    PASSWORD,
    IPPORT
};

extern QString _serverip;
extern QString _username;
extern QString _password;
extern int _ipport;

class SettingData
{
public:
//    static QString _serverip;
//    static QString _username;
//    static QString _password;

    static bool isLegal(SettingDataType itype,QString &istr);
};


#endif // SETTINGDATA_H
