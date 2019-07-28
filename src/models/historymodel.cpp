#include "historymodel.h"
#include "../dbadapter.h"

HistoryModel::HistoryModel(QObject *parent) : QAbstractListModel(parent) {
    hash.insert(Qt::UserRole ,QByteArray("title"));
    hash.insert(Qt::UserRole+1 ,QByteArray("url"));
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        qDebug() << "noIndex";
        return QVariant();
    }

    if(index.row() >= m_historySearchResult.count()) {
        qDebug() << "bigSize";
        return QVariant();
    }

    historyItem item = m_historySearchResult.at(index.row());
    switch (role) {
    case Qt::UserRole:
        return item.title;
    case Qt::UserRole+1:
        return item.url;
    default:
        return QVariant();
    }
}

int HistoryModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_historySearchResult.count();
}

void HistoryModel::setHistorySearch(QString historySearch) {
    if(historySearch != m_historySearch && historySearch.length() > 2) {
        m_historySearch = historySearch;
        p_setHistorySearch(historySearch);
    }

}

void HistoryModel::p_setHistorySearch(QString historySearch) {
    beginResetModel();
    m_historySearchResult.clear();

    QSqlDatabase db = DbAdapter::instance().db;
    QSqlQuery query(db);
    QString weNeed = QString("SELECT DISTINCT title, url FROM history WHERE `title` LIKE '%%1%' OR `url` LIKE '%%1%' ORDER BY id DESC").arg(historySearch);

    if(!query.exec(weNeed)) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    while(query.next()) {
        historyItem item;
        item.title = query.value(0).toString();
        item.url = query.value(1).toString();

        m_historySearchResult.append(item);
    }

    endResetModel();
}

void HistoryModel::insertToHistory(QString url = "", QString title = "") {
    if(!url.isEmpty() && !title.isEmpty()) {
        beginResetModel();

        QSqlDatabase db = DbAdapter::instance().db;
        QSqlQuery query(db);
        query.prepare("INSERT INTO history (`title`, `url`, `timestamp`) VALUES (:title, :url, :timestamp)");
        query.bindValue(":title",title);
        query.bindValue(":url",url);
        query.bindValue(":timestamp",QDateTime::currentDateTime().toMSecsSinceEpoch());

        if(!query.exec()) {
            qDebug() << query.lastQuery() << query.lastError().text();
        }
        endResetModel();
    }
}

void HistoryModel::removeFromHistory(QString url = "") {
    if(!url.isEmpty()){
        qDebug() << "History removed:" << url;

        QSqlDatabase db = DbAdapter::instance().db;
        QSqlQuery query(db);

        if(!query.exec(QString("DELETE FROM history WHERE `url` LIKE '%1'").arg(url))) {
            qDebug() << query.lastQuery() << query.lastError().text();
        } else {
            p_setHistorySearch(m_historySearch);
        }
    }
}

void HistoryModel::searchClear()
{
    beginResetModel();
    m_historySearchResult.clear();
    endResetModel();
}
