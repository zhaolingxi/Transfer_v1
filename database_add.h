#ifndef DATABASE_ADD_H
#define DATABASE_ADD_H

#include <QDialog>
#include"qsqlquery.h"
#include "settingdata.h"

#include <string>

namespace Ui {
class Database_add;
}

struct function_share_data
{
public:
    QString uuid="";
    QString Name1="";
    QString Name2="";
    QString Description="author: "+_username;
    QString Tag1="";
    QString Tag2="";
    QString Tag3="";
    int Priority=1;
    QString Body="";
    QString Tips="";
    function_share_data(){}
    ~function_share_data(){};
};

class Database_add : public QDialog
{
    Q_OBJECT

public:
    explicit Database_add(QDialog *parent = nullptr,std::string db_path="");
    ~Database_add();

private slots:
    void on_btn_ok_clicked();

    void on_cmb_name_activated(int index);

    void on_edt_name_textChanged();

    void on_cmb_tag_activated(int index);

    void on_edt_lab_textChanged();

    void on_btn_close_clicked();

    void on_btn_back_clicked();

private:
    Ui::Database_add *ui;
    QDialog* _p_parent = nullptr;

    std::map<int,QString> _map_cmb_name_str;
    std::map<int,QString> _map_cmb_tag_str;
    std::string _db_path;
    QSqlDatabase _db_local;

    void clearAllData();
    bool addDataToSqlite();
    void generateFunctionShareData(function_share_data &iodata_struct);
    void checkLocalDataBase();

    bool insertRecord(const function_share_data &idata_struct);

};

#endif // DATABASE_ADD_H
