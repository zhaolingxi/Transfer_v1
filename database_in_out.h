#ifndef DATABASE_IN_OUT_H
#define DATABASE_IN_OUT_H

#include <QDialog>
#include <QSqlDatabase>


namespace Ui {
class Database_In_Out;
}

class Database_In_Out : public QDialog
{
    Q_OBJECT

public:
    explicit Database_In_Out(QDialog *parent = nullptr,std::string db_path="",int mode=0);
    ~Database_In_Out();


    void readDataFromSqlWriteToCSV(const QString &tableName,const QString &csvFileName,const QString &filePath);

    bool readDataFromSqlWriteToSQL(const QString &sqlFileName,const QString &filePath);

    bool readDataFromSqlWriteToDB(const QString &sqlFileName,const QString &local_database);

    bool readDataFromCSVWriteToDB(const QString &sqlFileName,const QString &tableName);

private slots:
    void changePathBtnSLOT();

    void on_btn_close_clicked();

    void on_btn_back_clicked();

    void on_btn_ok_clicked();

    void on_pushbtn_path_2_clicked();

private:
    Ui::Database_In_Out *ui;
    QDialog* _parent = nullptr;
    std::string _db_path;
    QSqlDatabase _db_in_out;
    int _mode;
    QStringList _selectedFiles;
};

#endif // DATABASE_IN_OUT_H
