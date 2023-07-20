#include "login.h"
#include<QSettings>

#include "ui_login.h"
#include "function_select.h"
#include "about_me.h"

login::login(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    QSettings setting("./config.ini",QSettings::IniFormat);
    QString user_name= setting.value("username").toString();
    ui->lineEdit->setText(user_name);

}

login::~login()
{
    QSettings setting("./config.ini",QSettings::IniFormat);
    setting.setValue("username",_username);
    delete ui;
}


void login::on_btn_login_setting_clicked()
{
   this->hide();
   string type="QMainWindow";
   Settings *settingplane= new Settings(this);
   settingplane->show();
}


void login::on_pushButton_clicked()
{
    _username=ui->lineEdit->text();
    this->hide();
    Function_Select *function_select_plane= new Function_Select(this);
    function_select_plane->show();
}


void login::on_btn_about_me_clicked()
{
    //this->hide();
    About_me *About_me_plane= new About_me(this);
    About_me_plane->show();
}

