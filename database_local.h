#ifndef DATABASE_LOCAL_H
#define DATABASE_LOCAL_H

#include <QWidget>

namespace Ui {
class Database_local;
}

class Database_local : public QWidget
{
    Q_OBJECT

public:
    explicit Database_local(QWidget *parent = nullptr);
    ~Database_local();

private:
    Ui::Database_local *ui;
};

#endif // DATABASE_LOCAL_H
