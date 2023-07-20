#ifndef EDITORPANEL_H
#define EDITORPANEL_H

#include <QDialog>

namespace Ui {
class EditorPanel;
}

class EditorPanel : public QDialog
{
    Q_OBJECT

public:
    explicit EditorPanel(QDialog *parent = nullptr,
                         QString iStr="",int row=-1, int column=-1);
    ~EditorPanel();

private slots:
    void on_btn_close_clicked();

    void on_btn_back_clicked();

    void on_btn_ok_clicked();

signals:
    void signal_modify_done(QString iStr,int row,int col);

private:
    Ui::EditorPanel *ui;
    QString _Str;
    QDialog* _parent=nullptr;
    int _row;
    int _column;
};

#endif // EDITORPANEL_H
