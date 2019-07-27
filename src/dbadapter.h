#ifndef DBADAPTER_H
#define DBADAPTER_H

#include <QObject>
#include <QtSql>
#include <QSqlQueryModel>

class DbAdapter : public QObject
{
    Q_OBJECT
public:
    explicit DbAdapter(QObject *parent = 0);
    ~DbAdapter();

    static DbAdapter& instance();
    QSqlDatabase db;

private:
    QSqlQuery query;
    QMutex lock;
    void initDB();
};

#endif // DBADAPTER_H
