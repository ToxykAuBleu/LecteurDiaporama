#include "database.h"
#include <QDebug>
#include <QSqlError>

Database::Database() { }

bool Database::openDatabase() {
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setHostName("lakartxela.iutbayonne.univ-pau.fr");
    mydb.setDatabaseName(DATABASE_NAME);
    mydb.setUserName(USER_NAME);
    mydb.setPassword(USER_PASS);
    bool ok = mydb.open();
    if (!ok) {
        qDebug() << mydb.lastError().text() << Qt::endl;
        return false;
    }
    return true;
}

void Database::closeDatabase() {
    mydb.close();
}
