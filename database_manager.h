#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#include<qstring.h>
#include<vector>

#include<QSqlDatabase>
#include<QMessageBox>

extern QString local_db_path;

extern const QString crate_local_db_str;
extern const QString insert_to_local_db_str;
extern const QString delete_local_db_str;
extern const QString delete_local_db_line_str;
extern const QString serach_from_local_db_str;
extern const QString update_local_db_str;
extern std::vector<QString> local_db_member;

class database_manager
{
public:
    database_manager();

    static QString ToSqlStr(QString iStr);
    static void ToSqlStr2(QString &ioStr);

    static void checkDataBase(QString cur_path,QSqlDatabase &iodb);
};



#endif // DATABASE_MANAGER_H
