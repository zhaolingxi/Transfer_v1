#include "database_manager.h"

QString local_db_path;

const QString crate_local_db_str="create table local_function_table (id vchar PRIMARY KEY, Name1 vchar,Name2 vchar,"
                       "Description vchar,Tag1 vchar,Tag2 vchar,Tag3 vchar,Priority int,Body text,Tips vchar)";

const QString delete_local_db_str="DROP TABLE local_function_table";

const QString delete_local_db_line_str="DELETE FROM local_function_table WHERE ";

const QString insert_to_local_db_str="INSERT INTO local_function_table (id, Name1,Name2,Description,Tag1,Tag2,Tag3,Priority,Body,Tips)" \
                               "VALUES(:id, :Name1, :Name2, :Description, :Tag1, :Tag2, :Tag3, :Priority, :Body, :Tips)";

const QString serach_from_local_db_str="select * from local_function_table";
//Name1,Name2,Tag1,Tag2,Tag3

const QString update_local_db_str="UPDATE local_function_table SET ";

std::vector<QString> local_db_member={"id", "Name1","Name1","Description","Tag1","Tag2","Tag3","Priority","Body","Tips"};

QString database_manager::ToSqlStr(QString iStr)
{
    QString tmp="'";
    tmp+=iStr;
    tmp+=tmp;
    return tmp;
}

void database_manager::ToSqlStr2(QString &ioStr)
{
    QString tmp="'";
    tmp+=ioStr;
    tmp+="'";
    ioStr=tmp;
}

database_manager::database_manager()
{

}

void database_manager::checkDataBase(QString cur_path,QSqlDatabase &iodb)
{
    FILE* fp=fopen(cur_path.toStdString().c_str(),"rb");
    QString link;
    if(!fp)
    {
        link="数据库缺失，将为您新创建";
    }
    else{
        link="数据库加载正常";fclose(fp);
    }
    iodb = QSqlDatabase::addDatabase("QSQLITE");               //引入数据库的驱动字符串为SQLITE,相当于用这个来创建需要链接的数据库类型
    iodb.setDatabaseName(cur_path);                            //设置数据库,创建一个数据库文件
    bool ret=iodb.open();                                      //打开数据库
    if(!ret)
    {
        QMessageBox::information(nullptr,"提示","<font size='2' color='red'>数据库链接失败,请检查路径</font>", QMessageBox::Yes);
    }
}
