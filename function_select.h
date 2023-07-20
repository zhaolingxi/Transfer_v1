#ifndef FUNCTION_SELECT_H
#define FUNCTION_SELECT_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Function_Select;
}

class Function_Select : public QDialog
{
    Q_OBJECT

public:
    explicit Function_Select(QWidget *parent = nullptr);
    ~Function_Select();

private slots:

    void on_ok_btn_clicked();

    void on_back_btn_clicked();

    void on_DataBase_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Function_Select *ui;
    QWidget* _p_parent = nullptr;
};

#endif // FUNCTION_SELECT_H
