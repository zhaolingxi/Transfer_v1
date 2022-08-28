#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QMainWindow>
#include<string>
#include"settingdata.h"
using namespace std;

namespace Ui {
class Settings;
}


class Settings : public QWidget
{
    Q_OBJECT

public:
    template <class T>
    explicit Settings(T prepanel,string type,QWidget *parent = nullptr);
    explicit Settings(QMainWindow* prepanel,QWidget *parent = nullptr);
    ~Settings();

    void InitPanel();

private slots:
    void on_btn_back_clicked();

    void on_Edt_serverip_editingFinished();

    void on_btn_confirm_clicked();

private:
    Ui::Settings *ui;
    QWidget* m_prepanel=nullptr;//跳转至设置之前的面板
    QMainWindow* m_prepanel1=nullptr;//跳转至设置之前的面板

};

#endif // SETTINGS_H
