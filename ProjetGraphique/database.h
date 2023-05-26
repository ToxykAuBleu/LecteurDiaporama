#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DATABASE_NAME "bd_nodenot"
#define CONNECT_TYPE "QODBC"
#define USER_NAME "mfoissac002_bd"
#define USER_PASS "mfoissac002_bd"

class Database {
    public:
        Database();
        bool openDatabase();
        void closeDatabase();

    private:
        QSqlDatabase mydb;
};

#endif // DATABASE_H
