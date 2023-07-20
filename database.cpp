//stl
#include<iostream>
#include<stdio.h>

#include "database.h"
#include "ui_database.h"
#include"qsqldatabase.h"
#include"qsqlquery.h"
#include"qmessagebox.h"
#include<QDir>

//panel
#include "database_add.h"
#include "database_serach.h"
#include "database_manager.h"
#include "database_in_out.h"


//self
#include "read_files.h"

DataBase::DataBase(QDialog *parent) :
   // QDialog(parent),
    ui(new Ui::DataBase)
{
    ui->setupUi(this);
    _parent=parent;

//add defult value in widget
    //cmb
    ui->cmb_mode->addItem("Local","本地数据库模式");
    ui->cmb_mode->addItem("Text","读取、搜索文本文件");
    ui->cmb_mode->addItem("Git","链接GIT服务器，获取、推送更新");
    ui->cmb_mode->addItem("Multi","链接多个本地数据库");
    ui->cmb_mode->setItemData(1, QVariant(0), Qt::UserRole - 1);
    ui->cmb_mode->setItemData(2, QVariant(0), Qt::UserRole - 1);
    ui->cmb_mode->setItemData(3, QVariant(0), Qt::UserRole - 1);
    //QString cur_path=getCurrentDir();
    //QString cur_path = QDir::currentPath();
    QString cur_path = QCoreApplication::applicationDirPath().toUtf8();
    cur_path+="/database/local/test_local.db";
    ui->textEdit_datapath->setText(cur_path);
    local_db_path=cur_path;

    setFixedSize(size());
}

DataBase::~DataBase()
{
    delete ui;
}

void DataBase::on_search_btn_clicked()
{
    int mode=ui->cmb_mode->currentIndex();
    this->hide();
    Database_serach *Database_add_plane= new Database_serach(this,local_db_path.toStdString(),mode);
    Database_add_plane->show();
}


void DataBase::on_mode_cmb_activated(int index)
{
    if(index==0)
    {

    }
    else if(index==1)
    {

    }
    else if(index==2)
    {

    }
}


void DataBase::on_add_btn_clicked()
{
    this->hide();
    Database_add *Database_add_plane= new Database_add(this,local_db_path.toStdString());
    Database_add_plane->show();
}


void DataBase::on_add_btn_4_clicked()
{
    checkLocalDataBase();
}

void DataBase::checkLocalDataBase()
{
    QString cur_path=ui->textEdit_datapath->toPlainText().toUtf8();
    FILE* fp=fopen(cur_path.toStdString().c_str(),"rb");
    QString link;
    if(!fp)
    {
        link="数据库缺失，已为您新创建";
    }
    else{
        link="数据库加载正常";fclose(fp);
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");  //引入数据库的驱动字符串为SQLITE,相当于用这个来创建需要链接的数据库类型
    db.setDatabaseName(cur_path);                            //设置数据库,创建一个数据库文件
    bool ret=db.open();                                      //打开数据库
    if(ret)
    {
        QString str= "<font size='2' color='black'>";
        str+=link; str+="</font>";
        QMessageBox::information(this,"提示", str,QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,"提示","<font size='2' color='red'>数据库链接失败,请检查路径</font>", QMessageBox::Yes);
    }
}


void DataBase::on_close_btn_clicked()
{
    QApplication::exit(0);
}


void DataBase::on_back_btn_clicked()
{
    this->hide();
    if(_parent)_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose,1);
}


void DataBase::on_add_btn_3_clicked()
{
      QMessageBox::information(this,"警告","<font size='2' color='red'>是否删除本地数据库？</font>", QMessageBox::Yes|QMessageBox::Cancel);
}


void DataBase::on_add_btn_7_clicked()
{
    // 启动执行命令不关闭CMD窗口
     // system("start cmd /k");

     // 启动执行命令后自动关闭CMD窗口
     // system("start cmd /C");

     // 设置临时PATH
      QString cmd = "start cmd /k SET PATH=";
      QString path = QCoreApplication::applicationDirPath().toUtf8();
      // QString path = getCurrentDir();
      path.replace("/", "\\");
      system(cmd.toLatin1() + path.toLatin1());
      system("sqlite3");
}


void DataBase::on_add_btn_6_clicked()
{
    this->hide();
    Database_In_Out *Database_add_plane= new Database_In_Out(this,local_db_path.toStdString(),2);
    Database_add_plane->show();
}


void DataBase::on_add_btn_5_clicked()
{
    this->hide();
    Database_In_Out *Database_add_plane= new Database_In_Out(this,local_db_path.toStdString(),1);
    Database_add_plane->show();
}

