#include "dbadapter.h"

#include <QtSql>
#include <QDebug>
#include <QStandardPaths>

static DbAdapter *dbAdapterInstance = 0;

DbAdapter::DbAdapter(QObject *parent) : QObject(parent) {
    QMutexLocker locker(&lock);
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/db.sql";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if(!db.open()) {
        qDebug() << db.lastError().text();
    }

    if(QFile(dbPath).size() == 0) {
        initDB();
    }

    qDebug() << "Db is" << dbPath;
}

DbAdapter::~DbAdapter() {
    db.close();
}

DbAdapter& DbAdapter::instance() {
    static QMutex mutex;
    QMutexLocker locker(&mutex);

    if(!dbAdapterInstance) {
        dbAdapterInstance = new DbAdapter();
    }
    return *dbAdapterInstance;
}

void DbAdapter::initDB() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE `history` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `title` TEXT, `url` TEXT, `timestamp` INTEGER)")) {
        qDebug() << query.lastError();
    }

    if (!query.exec("CREATE TABLE `bookmarks` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `title` TEXT, `url` TEXT, `favicon` TEXT, `timestamp` INTEGER)")) {
        qDebug() << query.lastError();
    }
}
