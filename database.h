#ifndef DATABASE_H
#define DATABASE_H

#include <QDialog>

namespace Ui {
class DataBase;
}

class DataBase : public QDialog
{
    Q_OBJECT

public:
    explicit DataBase(QDialog *parent = nullptr);
    ~DataBase();

private slots:
    void on_search_btn_clicked();

    void on_mode_cmb_activated(int index);

    void on_add_btn_clicked();

    void on_add_btn_4_clicked();

    void on_close_btn_clicked();

    void on_back_btn_clicked();

    void on_add_btn_3_clicked();

    void on_add_btn_7_clicked();

    void on_add_btn_6_clicked();

    void on_add_btn_5_clicked();

private:
    Ui::DataBase *ui;
    QDialog* _parent=nullptr;

    void checkLocalDataBase();
};

#endif // DATABASE_H
