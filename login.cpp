#include "login.h"
#include "ui_login.h"

login::login(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_btn_login_setting_clicked()
{
   this->hide();
   string type="QMainWindow";
   Settings *settingplane= new Settings(this);
   settingplane->show();
}

