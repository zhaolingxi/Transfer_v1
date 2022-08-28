#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<string>
#include"settings.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QMainWindow *parent = nullptr);
    ~login();

private slots:
    void on_btn_login_setting_clicked();

private:
    Ui::login *ui;
};
#endif // LOGIN_H
