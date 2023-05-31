#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

// Les 4 "#define" ci-dessous permettent de définir les macros qui permettent de se connecter à la base de données

#define DATABASE_NAME "BD_Nodenot_Lakartxela"
#define CONNECT_TYPE "QODBC"
#define USER_NAME "apommiez001_bd"
#define USER_PASS "apommiez001_bd"

class Database {
    public:
        Database();
        bool openDatabase();    // Permet de se connecter à la base de données, en renvoyant true si la connexion est réussie, false sinon
        void closeDatabase();   // Permet de fermer la connexion à la base de données

    private:
        QSqlDatabase mydb;      // Objet représentant la base de données
};

#endif // DATABASE_H
