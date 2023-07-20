#include "database_local.h"
#include "ui_database_local.h"

Database_local::Database_local(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Database_local)
{
    ui->setupUi(this);
}

Database_local::~Database_local()
{
    delete ui;
}
