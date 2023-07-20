#include<QFileDialog>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QMessageBox>
#include<QRegularExpression>
#include<QProcess>
#include<QDir>
#include<QFuture>
#include<QtConcurrent>


#include"read_files.h"

//#include"sqlite3.h"

#include "database_manager.h"

#include "database_in_out.h"
#include "ui_database_in_out.h"

Database_In_Out::Database_In_Out(QDialog *parent,std::string db_path,int mode) :
   // QDialog(parent),
    ui(new Ui::Database_In_Out)
{
    ui->setupUi(this);
    _parent=parent;
    _db_path=db_path;
    _mode=mode;
    if(_mode==1)
    {
        ui->lab_filepath->setText("导入(源文件)");
        ui->lab_filepath_2->setText("导入(目标数据库)");
        ui->lab_filetype->setVisible(false);
        ui->cmb_mode->setVisible(false);
    }
    else if(_mode==2)
    {
        ui->lab_filepath->setText("导出(源文件)");
        ui->lab_filepath_2->setText("导出(目标文件夹)");
    }

    //按钮初始化
    connect(ui->pushbtn_path,SIGNAL(clicked(bool)),this,SLOT(changePathBtnSLOT()));

    //添加控件信息
    ui->cmb_mode->addItem(".sql");
    ui->cmb_mode->addItem(".csv");

    database_manager::checkDataBase(_db_path.c_str(),_db_in_out);

    setFixedSize(size());
}

Database_In_Out::~Database_In_Out()
{
    delete ui;
}


void Database_In_Out::changePathBtnSLOT()
{

    if(_mode==1)
    {
        QString selected;
        QStringList selectedFiles=QFileDialog::getOpenFileNames(this,"选择文件","./","*.sql");
        if (!selectedFiles.isEmpty())
        {
            _selectedFiles.clear();
            int sz=selectedFiles.count();
            for(int i=0;i<sz;i++)
            {
                QString qstr=selectedFiles[i];
                qstr= qstr.replace(QRegularExpression("\\"), "/");
                _selectedFiles.append(qstr);
                selected+=qstr;
            }
        }
        //显示选择的目录路径
        ui->textEdit->setText(selected);
    }
    else if(_mode==2){
        QString selected;
        QStringList selectedFiles=QFileDialog::getOpenFileNames(this,"选择文件","./","*.db");
        if (!selectedFiles.isEmpty())
        {
            _selectedFiles.clear();
            int sz=selectedFiles.count();
            for(int i=0;i<sz;i++)
            {
                QString qstr=selectedFiles[i];
                qstr= qstr.replace(QRegularExpression("\\"), "/");
                _selectedFiles.append(qstr);
                selected+=qstr;
            }
        }
        //显示选择的目录路径
        ui->textEdit->setText(selected);
    }
}


void Database_In_Out::on_pushbtn_path_2_clicked()
{
    if(_mode==1)
    {
        QString selected;
        QStringList selectedFiles=QFileDialog::getOpenFileNames(this,"选择文件","./","*.db");
        if (!selectedFiles.isEmpty())
        {
            _selectedFiles.clear();
            int sz=selectedFiles.count();
            for(int i=0;i<sz;i++)
            {
                QString qstr=selectedFiles[i];
                qstr= qstr.replace(QRegularExpression("\\"), "/");
                _selectedFiles.append(qstr);
                selected+=qstr;
            }
        }
        //显示选择的目录路径
        ui->textEdit_2->setText(selected);
    }
    else if(_mode==2){
        QString selectedDir;
        //获取选择的目录路径
        selectedDir=QFileDialog::getExistingDirectory(this,"选择一个目录","./",QFileDialog::ShowDirsOnly);
        //若目录路径不为空
        if (!selectedDir.isEmpty())
        {
            //将路径中的斜杠替换为反斜杠
            selectedDir = selectedDir.replace(QRegularExpression("\\"), "/");
            //显示选择的目录路径
            ui->textEdit_2->setText(selectedDir);
        }
    }
}


void Database_In_Out::on_btn_close_clicked()
{
    QApplication::exit(0);
}


void Database_In_Out::on_btn_back_clicked()
{
    this->hide();
    if(_parent)_parent->show();
    this->setAttribute(Qt::WA_DeleteOnClose,1);
}


void Database_In_Out::on_btn_ok_clicked()
{
    QString filePath=ui->textEdit->toPlainText();
    if(filePath.isEmpty())
    {
        QMessageBox::information(this,"警告","<font size='2' color='red'>请选择文件路径</font>", QMessageBox::Yes);
        return;
    }
    if(_mode==1)
    {
        int sz=_selectedFiles.count();
        for(int i=0;i<sz;i++)
        {
            QFuture<void> res = QtConcurrent::run(this, &Database_In_Out::readDataFromSqlWriteToDB,ui->textEdit->toPlainText(),_selectedFiles[i]);//启动线程调用
            while(!res.isFinished())
            {
                    //
                QApplication::processEvents();//不停地处理事件，让程序保持响应
            }
            //bool ret=readDataFromSqlWriteToDB(ui->textEdit->toPlainText(),_selectedFiles[i]);
            if(!res.isFinished())
            {
                QMessageBox::information(nullptr,"提示","<font size='2' color='red'>输出完成，清查看文件</font>", QMessageBox::Yes);
            }
        }
    }
    else
    {
        if(ui->cmb_mode->currentText()==".sql")
        {
            QString out_file_name="output.sql";
            QFuture<void> res = QtConcurrent::run(this, &Database_In_Out::readDataFromSqlWriteToSQL,out_file_name,filePath);//启动线程调用
            while(!res.isFinished())
            {
                    //
                QApplication::processEvents();//不停地处理事件，让程序保持响应
            }
            //bool ret=readDataFromSqlWriteToSQL("output.sql",filePath);
            if(!res.isFinished())
            {
                QMessageBox::information(nullptr,"提示","<font size='2' color='red'>输出完成，清查看文件</font>", QMessageBox::Yes);
            }
        }
        else
        {
            readDataFromSqlWriteToCSV("local_function_table","output.csv",filePath);
        }
    }


}




void Database_In_Out::readDataFromSqlWriteToCSV(const QString &tableName,const QString &csvFileName,const QString &filePath)//将表导出为csv格式表格
{
    if(!_db_in_out.open()) return;
     QSqlTableModel *exportModel = new QSqlTableModel();
     exportModel->setTable(tableName);
     exportModel->select();
     QStringList strList;//记录数据库中的一行报警数据
     QString strString;
     QString FILE_PATH(filePath);FILE_PATH+="/";FILE_PATH+=csvFileName;
     QFile csvFile(FILE_PATH);
     if (csvFile.open(QIODevice::ReadWrite))
     {
        for (int i=0;i<exportModel->rowCount();i++)
        {
            for(int j=0;j<exportModel->columnCount();j++)
            {
                strList.insert(j,exportModel->data(exportModel->index(i,j)).toString());//把每一行的每一列数据读取到strList中
            }
            strString = strList.join(", ")+"\n";//给两个列数据之前加“,”号，一行数据末尾加回车
            strList.clear();//记录一行数据后清空，再记下一行数据
            csvFile.write(strString.toUtf8());//使用方法：转换为Utf8格式后在windows下的excel打开是乱码,可先用notepad++打开并转码为unicode，再次用excel打开即可。
            //qDebug()<<strString.toUtf8();
       }
        csvFile.close();
     }
}

bool Database_In_Out::readDataFromSqlWriteToSQL(const QString &sqlFileName,const QString &filePath)
{
        QProcess* p=new QProcess();
         p->start("cmd.exe");
         QString cmd0="sqlite3 ";cmd0+=ui->textEdit->toPlainText();cmd0+=" .dump >";
            cmd0+=ui->textEdit_2->toPlainText();cmd0+="/output.sql";cmd0+="\r\n";
         QString cmd=cmd0;

         /* 转为char*并写入 */
         QByteArray qbarr = cmd.toLatin1();
         char *ch = qbarr.data();
         qint64 len = cmd.length();
         p->write(ch, len);
         bool ret= p->waitForFinished();	//避免阻塞，3秒等待时间，重要
         p->close();
         return ret;
}

bool Database_In_Out::readDataFromSqlWriteToDB(const QString &sqlFileName,const QString &local_database)
{
    QProcess* p=new QProcess();
     p->start("cmd.exe");
     QString cmd0="sqlite3 ";cmd0+=local_database;cmd0+=" <";cmd0+=sqlFileName;cmd0+="\r\n";
     QString cmd=cmd0;

     /* 转为char*并写入 */
     QByteArray qbarr = cmd.toLatin1();
     char *ch = qbarr.data();
     qint64 len = cmd.length();
     p->write(ch, len);
     bool ret= p->waitForFinished();	//避免阻塞，3秒等待时间，重要
     p->close();
     return ret;
}

bool readDataFromCSVWriteToDB(const QString &sqlFileName,const QString &tableName)
{
    QProcess* p=new QProcess();
     p->start("cmd.exe");
     QString cmd0="sqlite3";cmd0+="\r\n";
     QString cmd1=".separator ',' ";cmd1+=sqlFileName.toStdString().c_str(); cmd1+="\r\n";
     QString cmd4=".exit\r\n";
     QString cmd=cmd0+cmd1+cmd4;

     /* 转为char*并写入 */
     QByteArray qbarr = cmd.toLatin1();
     char *ch = qbarr.data();
     qint64 len = cmd.length();
     p->write(ch, len);
     bool ret= p->waitForFinished(3000);	//避免阻塞，3秒等待时间，重要
     p->close();
     return ret;
}






