#include "about_me.h"
#include "ui_about_me.h"

#include<QRegularExpression>

QList< std::pair<QString,bool> >strArray;
std::unordered_map<unsigned,int> urlIndex;

About_me::About_me(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_me)
{
    ui->setupUi(this);
    QString str_aboutme;
    str_aboutme+="gitgub url:  https://github.com/    \t\n";
    str_aboutme+="e-mail :zhaolingxi628&outlook.com      \t\n";
    str_aboutme+="personal-website :zhaolingxi.com      \t\n";
    ui->textEdit->setText(str_aboutme);
}

About_me::~About_me()
{
    delete ui;
}



//QString About_me::GetlinkUrl(const QString &str)
//{
//    return "<a href='"+str+"'>"+str+"</a>";
//}
////#define LINK_RegulaString "((http[s]{0,1}|ftp)://[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)|(www.[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)"
////将普通网址改为html文本,显示下划线样式 蓝色
//void About_me::SetTextContent(const QString &str)
//{
//    QString content = str;
//    QRegularExpression regexp(LINK_RegulaString);
//    int pos = content.indexOf(regexp);
//    while(pos>=0){
//        if(pos==0){
//            QString tmp = content.mid(0,regexp.matchedLength());
//            content = content.mid(regexp.matchedLength());
//            strArray.push_back(make_pair(tmp,true));
//        }else{
//            QString tmp1 = content.mid(0,pos);
//            QString tmp2 = content.mid(pos,regexp.matchedLength());
//            content = content.mid(pos+regexp.matchedLength());
//            strArray.push_back(make_pair(tmp1,false));
//            strArray.push_back(make_pair(tmp2,true));
//        }
//        pos = content.indexOf(regexp);
//    }
//    if(content.size()>0)
//        strArray.push_back(make_pair(content,false));
//    for(int i=0;i<strArray.size();++i){
//        pair<QString,bool> t = strArray.at(i);
//        if(t.second == false)
//            this->textEdit->setUcs4String(t.first);
//        else{
//            int count = this->textEdit->toPlainText().size();
//            this->textEdit->append(this->GetlinkUrl(t.first));
//            int len = this->GetlinkUrl(t.first).size();
//            for(int j = count;j<count+len;++j)
//                urlIndex[j] = i;
//        }
//    }
//}
//    int pos = content.indexOf(regexp);
//    while(pos>=0){
//        if(pos==0){
//            QString tmp = content.mid(0,regexp.matchedLength());
//            content = content.mid(regexp.matchedLength());
//            strArray.push_back(make_pair(tmp,true));
//        }else{
//            QString tmp1 = content.mid(0,pos);
//            QString tmp2 = content.mid(pos,regexp.matchedLength());
//            content = content.mid(pos+regexp.matchedLength());
//            strArray.push_back(make_pair(tmp1,false));
//            strArray.push_back(make_pair(tmp2,true));
//        }
//        pos = content.indexOf(regexp);
//    }
//    if(content.size()>0)
//        strArray.push_back(make_pair(content,false));
//    for(int i=0;i<strArray.size();++i){
//        pair<QString,bool> t = strArray.at(i);
//        if(t.second == false)
//            this->textEdit->setUcs4String(t.first);//这段代码自己封装的 为了解析特殊表情，相当于settext
//        else{
//            int count = this->textEdit->toPlainText().size();
//            this->textEdit->append(this->GetlinkUrl(t.first));
//            int len = this->GetlinkUrl(t.first).size();
//            for(int j = count;j<count+len;++j)
//                urlIndex[j] = i;
//        }
//    }
//}


