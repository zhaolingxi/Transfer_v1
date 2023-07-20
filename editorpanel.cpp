#include "editorpanel.h"
#include "ui_editorpanel.h"

EditorPanel::EditorPanel(QDialog *parent,QString iStr,int row, int column) :
    //QDialog(parent),
    ui(new Ui::EditorPanel)
{
    ui->setupUi(this);
    _Str=iStr;
    _parent=parent;
    _row=row;_column=column;

    ui->textEdit->setText(_Str);

    setFixedSize(size());
}

EditorPanel::~EditorPanel()
{
    delete ui;
}

void EditorPanel::on_btn_close_clicked()
{
    //this->hide();
   // this->setAttribute(Qt::WA_DeleteOnClose,1);
    delete this;
}


void EditorPanel::on_btn_back_clicked()
{
    ui->textEdit->setText(_Str);
}


void EditorPanel::on_btn_ok_clicked()
{
    _Str=ui->textEdit->toPlainText();
    emit this->signal_modify_done(_Str,_row,_column);
    on_btn_close_clicked();
}

