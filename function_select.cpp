#include "function_select.h"
#include "ui_function_select.h"
#include "database.h"
#include <iostream>

Function_Select::Function_Select(QWidget *parent) :
   // QDialog(parent),
    ui(new Ui::Function_Select)
{
    ui->setupUi(this);
    _p_parent=parent;

    setFixedSize(size());
}

Function_Select::~Function_Select()
{
    delete ui;
}




void Function_Select::on_ok_btn_clicked()
{
    QApplication::exit(0);
}


void Function_Select::on_back_btn_clicked()
{
    this->hide();
    if(_p_parent)_p_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose,1);
}


void Function_Select::on_DataBase_clicked()
{
    this->hide();
    DataBase *database_plane= new DataBase(this);
    database_plane->show();
}


void Function_Select::on_pushButton_2_clicked()
{

}

