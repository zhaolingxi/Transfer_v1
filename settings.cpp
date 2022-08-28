#include "settings.h"
#include "ui_settings.h"
#include<QMessageBox>

template <class T>
Settings::Settings(T prepanel,string type,QWidget *parent):
    QWidget(parent),
    ui(new Ui::Settings)
{
    if(type=="QWidget")
    {
        m_prepanel=prepanel;
    }
    else if(type=="QMainWindow")
    {
        m_prepanel1=prepanel;
    }
    ui->setupUi(this);
}

Settings::Settings(QMainWindow* prepanel,QWidget *parent):
    QWidget(parent),
    ui(new Ui::Settings)
{
    m_prepanel1=prepanel;
    ui->setupUi(this);
    InitPanel();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::InitPanel()
{
    QString strip=_serverip;
    int ipport=_ipport;
    QString port=QString::number(ipport);
    ui->Edt_serverip->setText(strip);

    ui->Edt_serverport->setText(port);
}

void Settings::on_btn_back_clicked()
{
    this->hide();
    if (m_prepanel)
    {
        m_prepanel->show();
    }
    else if(m_prepanel1)
    {
        m_prepanel1->show();
    }

}


void Settings::on_Edt_serverip_editingFinished()
{
    //QString serverip=ui->Edt_serverip->text();
}


void Settings::on_btn_confirm_clicked()
{
    QString serverip=ui->Edt_serverip->text();
    QString serverport=ui->Edt_serverport->text();
    bool flag=SettingData::isLegal(SettingDataType::SEVERIP,serverip);
    if(!flag)
    {
        QMessageBox::warning(this, "警告", "服务器IP设置违法");
    }
    flag=SettingData::isLegal(SettingDataType::IPPORT,serverport);
    if(!flag)
    {
        QMessageBox::warning(this, "警告", "服务器port设置违法");
    }
    if(flag)
    {
         _serverip=serverip;
         _ipport=serverport.toInt();
         on_btn_back_clicked();
    }
}

