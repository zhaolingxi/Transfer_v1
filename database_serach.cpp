#include<QSqlQuery>
#include<QSqlResult>
#include<QSqlQueryModel>
#include<QSqlRecord>


#include "ui_database_serach.h"

#include "database_serach.h"
#include "database_manager.h"
#include "editorpanel.h"


Database_serach::Database_serach(QDialog *parent,std::string db_path,int db_mode) :
   // QDialog(parent),
    ui(new Ui::Database_serach)
{
    ui->setupUi(this);
    _db_path=db_path;
    _parent=parent;
    _db_mode=db_mode;

    if(db_mode==0)
    {
        ui->cmb_mode->addItem("按标签搜索");
        ui->cmb_mode->addItem("按别名搜索");
        ui->cmb_mode->addItem("按优先级搜索");
        ui->cmb_mode->addItem("按用户自定义列表搜索");
        ui->cmb_mode->setItemData(3, QVariant(0), Qt::UserRole - 1);

        ui->tableWidget->setColumnCount(10);
        ui->tableWidget->setHorizontalHeaderLabels({"id","Name1","Name2","Description","Tag1","Tag2","Tag3","Priority","Body","Tips"});
    }


    ui->cmb_filter1->addItem("全字匹配");
    ui->cmb_filter1->addItem("正则表达");
    ui->cmb_filter1->setItemData(1, QVariant(0), Qt::UserRole - 1);

    database_manager::checkDataBase(_db_path.c_str(),_db_serach);

//    if(true == _db_serach.open())
//    {
//        QSqlQuery query(_db_serach);
//        int num_col=query.record().count();
//        ui->tableWidget->setColumnCount(num_col);
//        QStringList col_labels;
//        for(int column = 0; column < num_col; column++)
//        {
//            col_labels.append(query.value(column).toString());
//        }
//        ui->tableWidget->setHorizontalHeaderLabels(col_labels);
//    }


    setFixedSize(size());
    updataTablewidgetData();
}

Database_serach::~Database_serach()
{
    delete ui;
}

void Database_serach::on_btn_close_clicked()
{
    _db_serach.close();
    QApplication::exit(0);
}


void Database_serach::on_btn_back_clicked()
{
    this->hide();
    if(_parent)_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose,1);
}


void Database_serach::on_btn_ok_clicked()
{
    serach_data iodata_struct;
    generateSerachData(iodata_struct);
    serachRecord(iodata_struct);
}

void Database_serach::generateSerachData(serach_data &iodata_struct)
{
    iodata_struct.serach_key=ui->textEdit_key->toPlainText();
    iodata_struct.serach_mode=ui->cmb_mode->currentText();
    iodata_struct.serach_filter1=ui->cmb_filter1->currentText();
}

bool Database_serach::serachRecord(const serach_data &idata_struct)
{
    if(!_db_serach.open())return 0;
    QString tmp_serach_from_local_db_str=serach_from_local_db_str;
    tmp_serach_from_local_db_str+=" WHERE";

    if(ui->cmb_filter1->currentText()=="全字匹配")
    {
        _db_serach.setConnectOptions("QSQLITE_ENABLE_REGEXP=0");
    }
    else if(ui->cmb_filter1->currentText()=="正则表达")
    {
        _db_serach.setConnectOptions("QSQLITE_ENABLE_REGEXP=1");
    }


    if(ui->cmb_mode->currentText()=="按标签搜索")
    {
        tmp_serach_from_local_db_str+=" Tag1=:key OR Tag2=:key OR Tag3=:key";
    }
    else if(ui->cmb_mode->currentText()=="按别名搜索")
    {
        tmp_serach_from_local_db_str+=" Name1=:key OR Name2=:key";
    }
    else if(ui->cmb_mode->currentText()=="按优先级搜索")
    {
        tmp_serach_from_local_db_str+=" Priority=:key";
    }


    QString qstr_key=idata_struct.serach_key;
    QSqlQuery query(_db_serach);
    query.prepare(tmp_serach_from_local_db_str);
    query.bindValue(":key",qstr_key );
    if(query.exec())
    {
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        while(query.next())
        {
            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);
            for(int column = 0; column < query.record().count(); column++)
            {
                  QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
                  ui->tableWidget->setItem(rowCount,column,item);
            }
        }
    }

    return true;
}

void Database_serach::updataTablewidgetData()
{
    QString tmp_serach_from_local_db_str=serach_from_local_db_str;
    tmp_serach_from_local_db_str+=" WHERE 1=1";
    if(true == _db_serach.open())
    {
        QSqlQuery query(_db_serach);
        query.prepare(tmp_serach_from_local_db_str);
        if(query.exec())
        {
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            while(query.next())
            {
                int rowCount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(rowCount);
                for(int column = 0; column < query.record().count(); column++)
                {
                      QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
                      ui->tableWidget->setItem(rowCount,column,item);
                }
            }
        }
    }
}



void Database_serach::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString str_cell=ui->tableWidget->item(row,column)->text();
    EditorPanel * pedt_panel=new EditorPanel(this,str_cell,row,column);
    pedt_panel->show();

    //信号与槽函数
    connect(pedt_panel,SIGNAL(signal_modify_done(QString,int,int)),this,SLOT(on_Modify_cell(QString,int,int)));
}


void Database_serach::on_Modify_cell(QString iStr,int row,int col)
{
    if(col==0)
    {
        QMessageBox::information(nullptr,"提示","<font size='2' color='red'>请不要修改主键</font>", QMessageBox::Yes);
        return;
    }
    QTableWidgetItem *new_item=ui->tableWidget->item(row,col);
    new_item->setText(iStr);
    QString col_title=local_db_member[col];
    QString cur_uuid=ui->tableWidget->item(row,0)->text();

    if(true == _db_serach.open())
    {
        QSqlQuery query(_db_serach);
        QString tmp_update_local_db_str=update_local_db_str;
        tmp_update_local_db_str+=col_title;
        tmp_update_local_db_str+=" =";
        tmp_update_local_db_str+=":iStr";
        tmp_update_local_db_str+=" WHERE id=";
        tmp_update_local_db_str+=":cur_uuid";
        query.prepare(tmp_update_local_db_str);
        query.bindValue(":iStr",iStr);
        query.bindValue(":cur_uuid",cur_uuid);
        if(!query.exec())
        {
            QMessageBox::information(nullptr,"提示","<font size='2' color='red'>数据库更新失败,请检查输入</font>", QMessageBox::Yes);
        }
    }

}




void Database_serach::on_btn_del_clicked()
{
   QList<QTableWidgetItem*> qlist_items=ui->tableWidget->selectedItems();
   if(qlist_items.empty())
   {
        QMessageBox::information(nullptr,"提示","<font size='2' color='red'>删除行不能为空</font>", QMessageBox::Yes);
   }
   else
   {

       QMessageBox::StandardButton ret_btn=QMessageBox::information
               (nullptr,"提示","<font size='2' color='red'>确定从数据库中移除所选行吗？</font>", QMessageBox::Yes|QMessageBox::Cancel);
       if(ret_btn==QMessageBox::Yes)
       {
           QStringList qlist_strdel;
           int count = qlist_items.count();
           for(int i = 0; i < count; i++)
           {
               int row = ui->tableWidget->row(qlist_items.at(i));
               QString uuid = ui->tableWidget->item(row,0)->text();
               qlist_strdel.append(uuid);
           }
           if(true == _db_serach.open())
           {
              QSqlQuery query(_db_serach);
              int falg_err=0;
              for(int ii=0;ii<qlist_strdel.size();ii++)
              {
                    QString tmp_delete_local_db_line_str=delete_local_db_line_str;
                    tmp_delete_local_db_line_str+="id=:u_id";
                    query.prepare(tmp_delete_local_db_line_str);
                    query.bindValue(":u_id",qlist_strdel[ii]);
                    if(!query.exec())
                    {
                        falg_err=1;
                    }
              }
              if(falg_err) QMessageBox::information(nullptr,"提示","<font size='2' color='red'>数据库删除数据失败</font>", QMessageBox::Yes);
              updataTablewidgetData();
           }
       }

   }
}


void Database_serach::on_btn_showall_clicked()
{
    updataTablewidgetData();
}

