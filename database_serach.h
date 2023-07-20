#ifndef DATABASE_SERACH_H
#define DATABASE_SERACH_H

#include <QDialog>
#include <QSqlDatabase>



struct serach_data
{
public:
    QString serach_mode="";
    QString serach_key="";
    QString serach_filter1="";
    serach_data(){}
    ~serach_data(){};
};

namespace Ui {
class Database_serach;
}

class Database_serach : public QDialog
{
    Q_OBJECT

public:
    explicit Database_serach(QDialog *parent = nullptr,std::string db_path="",int db_mode=0);
    ~Database_serach();

    void generateSerachData(serach_data &iodata_struct);
    bool serachRecord(const serach_data &idata_struct);
    void updataTablewidgetData();
    void showAllLinesIndata();

public slots:
    void on_Modify_cell(QString iStr,int row,int col);

private slots:
    void on_btn_close_clicked();
    void on_btn_back_clicked();
    void on_btn_ok_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);


    void on_btn_del_clicked();

    void on_btn_showall_clicked();

private:
    Ui::Database_serach *ui;
    std::string _db_path;
    QDialog* _parent = nullptr;

    QSqlDatabase _db_serach;
    int _db_mode;
    int _db_col_num;
};

#endif // DATABASE_SERACH_H
