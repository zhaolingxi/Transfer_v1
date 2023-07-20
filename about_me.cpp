#include "about_me.h"
#include "ui_about_me.h"

#include<QRegularExpression>

QList< std::pair<QString,bool> >strArray;
std::unordered_map<unsigned,int> urlIndex;

About_me::About_me(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_me)
{
    ui->setupUi(this);
    QString str_aboutme;
    str_aboutme+="gitgub url:  https://github.com/zhaolingxi/Transfer_v1    \t\n";
    str_aboutme+="e-mail :zhaolingxi628@outlook.com      \t\n";
    str_aboutme+="personal-website :zhaolingxi.com      \t\n";
    ui->textEdit->setText(str_aboutme);
}

About_me::~About_me()
{
    delete ui;
}





