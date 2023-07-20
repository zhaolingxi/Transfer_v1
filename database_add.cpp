#include "database_add.h"
#include "ui_database_add.h"

#include "quuid.h"

#include "database_add.h"
#include "database_manager.h"

#include"qmessagebox.h"
#include<QDateTime>


//self
#include "read_files.h"


void ToSqlStrs()
{
    return;
}

template <typename T>
void ToSqlStrs(T &head)
{
    database_manager::ToSqlStr2(head);
}

template <typename T,typename ...Args>
void ToSqlStrs(T &head,Args& ... args)
{
    database_manager::ToSqlStr2(head);
    ToSqlStrs(args...);
}

Database_add::Database_add(QDialog *parent,std::string db_path) :
   // QDialog(parent),
    ui(new Ui::Database_add)
{
    ui->setupUi(this);
    _p_parent=parent;
    _db_path=db_path;

    QIcon qico("..\\source\\res\\photo\\icon\\title.png");
    QDialog::setWindowIcon(qico);


//添加控件信息
    ui->cmb_name->addItem("别名1");
    ui->cmb_name->addItem("别名2");

    ui->cmb_tag->addItem("标签1");
    ui->cmb_tag->addItem("标签2");
    ui->cmb_tag->addItem("标签3");

    setFixedSize(size());
}

Database_add::~Database_add()
{
    delete ui;
}

void Database_add::on_btn_ok_clicked()
{
    if(addDataToSqlite())
    {
        clearAllData();
        ui->textEdit->clear();
    }
}


void Database_add::on_cmb_name_activated(int index)
{
    auto it= _map_cmb_name_str.find(index);
    if(it==_map_cmb_name_str.end())
    {
        ui->edt_name->clear();
    }
    else
    {
        ui->edt_name->setText(it->second);
    }
}


void Database_add::on_edt_name_textChanged()
{
    int index=ui->cmb_name->currentIndex();
    QString cur_str=ui->edt_name->toPlainText();
    auto it= _map_cmb_name_str.find(index);
    if(it==_map_cmb_name_str.end())
    {
        _map_cmb_name_str.insert({index,cur_str});
    }
    else
    {
        (it->second)=cur_str;
    }
}


void Database_add::on_cmb_tag_activated(int index)
{
    auto it= _map_cmb_tag_str.find(index);
    if(it==_map_cmb_tag_str.end())
    {
        ui->edt_lab->clear();
    }
    else
    {
        ui->edt_lab->setText(it->second);
    }
}


void Database_add::on_edt_lab_textChanged()
{
    int index=ui->cmb_tag->currentIndex();
    QString cur_str=ui->edt_lab->toPlainText();
    auto it= _map_cmb_tag_str.find(index);
    if(it==_map_cmb_tag_str.end())
    {
        _map_cmb_tag_str.insert({index,cur_str});
    }
    else
    {
        (it->second)=cur_str;
    }
}

void Database_add::clearAllData()
{
    ui->edt_name->clear();
    ui->edt_lab->clear();
    _map_cmb_name_str.clear();
    _map_cmb_tag_str.clear();

}

bool Database_add::addDataToSqlite()
{
    checkLocalDataBase();
    QSqlQuery* query = new QSqlQuery();
    query->exec(crate_local_db_str);
    function_share_data idata_struct;
    generateFunctionShareData(idata_struct);
    bool ret= insertRecord(idata_struct);
    if(!ret)
    {
        QMessageBox::information(this,"警告","<font size='2' color='red'>数据库添加记录失败,请检查输入</font>", QMessageBox::Yes);
    }
    else
    {
        if(ui->rdb_open->isChecked()) QMessageBox::information(this,"提示","<font size='2' color='red'>数据插入成功</font>", QMessageBox::Yes);
    }
    return ret;
}

void Database_add::generateFunctionShareData(function_share_data &iodata_struct)
{
    QUuid uuid=QUuid::createUuid();
    iodata_struct.uuid = uuid.toString().toUtf8();

    auto it=_map_cmb_name_str.find(0);
    if(it!=_map_cmb_name_str.end())iodata_struct.Name1=it->second.toUtf8();
    it=_map_cmb_name_str.find(1);
    if(it!=_map_cmb_name_str.end())iodata_struct.Name2=it->second.toUtf8();

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    iodata_struct.Description+=" Create Date:";
    iodata_struct.Description+=current_date;iodata_struct.Description=iodata_struct.Description.toUtf8();

    it=_map_cmb_tag_str.find(0);
    if(it!=_map_cmb_tag_str.end())iodata_struct.Tag1=it->second.toUtf8();
    it=_map_cmb_tag_str.find(1);
    if(it!=_map_cmb_tag_str.end())iodata_struct.Tag2=it->second.toUtf8();
    it=_map_cmb_tag_str.find(2);
    if(it!=_map_cmb_tag_str.end())iodata_struct.Tag2=it->second.toUtf8();

    iodata_struct.Priority=1;
    iodata_struct.Body=ui->textEdit->toPlainText().toUtf8();
    iodata_struct.Tips="Tips";iodata_struct.Tips=iodata_struct.Tips.toUtf8();
}



void Database_add::checkLocalDataBase()
{
    QString cur_path=_db_path.c_str();
    FILE* fp=fopen(cur_path.toStdString().c_str(),"rb");
    QString link;
    if(!fp)
    {
        link="数据库缺失，将为您新创建";
    }
    else{
        link="数据库加载正常";fclose(fp);
    }
    _db_local = QSqlDatabase::addDatabase("QSQLITE");               //引入数据库的驱动字符串为SQLITE,相当于用这个来创建需要链接的数据库类型
    _db_local.setDatabaseName(cur_path);                            //设置数据库,创建一个数据库文件
    bool ret=_db_local.open();                                      //打开数据库
    if(!ret)
    {
        QMessageBox::information(this,"提示","<font size='2' color='red'>数据库链接失败,请检查路径</font>", QMessageBox::Yes);
    }
}


void Database_add::on_btn_close_clicked()
{
    _db_local.close();
    QApplication::exit(0);
}


void Database_add::on_btn_back_clicked()
{
    _db_local.close();
    this->hide();
    if(_p_parent)_p_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose,1);
}


bool Database_add::insertRecord(const function_share_data &idata_struct)
{
    QSqlQuery query;
    query.prepare(insert_to_local_db_str);
    query.bindValue(":id", idata_struct.uuid);
    query.bindValue(":Name1", idata_struct.Name1);
    query.bindValue(":Name2", idata_struct.Name2);
    query.bindValue(":Description", idata_struct.Description);
    query.bindValue(":Tag1", idata_struct.Tag1);
    query.bindValue(":Tag2", idata_struct.Tag2);
    query.bindValue(":Tag3", idata_struct.Tag3);
    query.bindValue(":Priority", idata_struct.Priority);
    query.bindValue(":Body", idata_struct.Body);
    query.bindValue(":Tips", idata_struct.Tips);
    if(!query.exec())
    {
        // qDebug() << "insertRecord error: " << query.lastError();
         return false;
    }
    return true;
}
