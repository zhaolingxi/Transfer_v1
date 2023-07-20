#ifndef ABOUT_ME_H
#define ABOUT_ME_H

#include <QDialog>

using namespace std ;

namespace Ui {
class About_me;
}

class About_me : public QDialog
{
    Q_OBJECT

public:
    explicit About_me(QWidget *parent = nullptr);
    ~About_me();


    QString GetlinkUrl(const QString &str);
    void SetTextContent(const QString &str);

private:
    Ui::About_me *ui;
};

#endif // ABOUT_ME_H
