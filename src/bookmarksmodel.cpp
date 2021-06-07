#include "bookmarksmodel.h"
#include "dbadapter.h"

BookmarksModel::BookmarksModel(QObject *parent) : QAbstractListModel(parent) {
    hash.insert(Qt::UserRole ,QByteArray("title"));
    hash.insert(Qt::UserRole+1 ,QByteArray("url"));
}

QVariant BookmarksModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        qDebug() << "noIndex";
        return QVariant();
    }

    if(index.row() >= m_bookmarksSearchResult.count()) {
        qDebug() << "bigSize";
        return QVariant();
    }

    bookmarksItem item = m_bookmarksSearchResult.at(index.row());
    switch (role) {
    case Qt::UserRole:
        return item.title;
    case Qt::UserRole+1:
        return item.url;
    default:
        return QVariant();
    }
}

int BookmarksModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_bookmarksSearchResult.count();
}

void BookmarksModel::setBookmarksSearch(QString bookmarksSearch) {
    if(bookmarksSearch != m_bookmarksSearch && bookmarksSearch.length() > 2) {
        m_bookmarksSearch = bookmarksSearch;
        p_setBookmarksSearch(bookmarksSearch);
    }

}

void BookmarksModel::p_setBookmarksSearch(QString bookmarksSearch) {
    beginResetModel();
    m_bookmarksSearchResult.clear();

    QSqlDatabase db = DbAdapter::instance().db;
    QSqlQuery query(db);
    QString weNeed = QString("SELECT DISTINCT title, url FROM bookmarks WHERE `title` LIKE '%%1%' OR `url` LIKE '%%1%' ORDER BY id DESC").arg(bookmarksSearch);

    if(!query.exec(weNeed)) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    while(query.next()) {
        bookmarksItem item;
        item.title = query.value(0).toString();
        item.url = query.value(1).toString();

        m_bookmarksSearchResult.append(item);
    }

    endResetModel();
}

void BookmarksModel::insertToBookmarks(QString url = "", QString title = "") {
    if(!url.isEmpty() && !title.isEmpty()) {
        beginResetModel();

        QSqlDatabase db = DbAdapter::instance().db;
        QSqlQuery query(db);
        query.prepare("INSERT INTO bookmarks (`title`, `url`, `timestamp`) VALUES (:title, :url, :timestamp)");
        query.bindValue(":title",title);
        query.bindValue(":url",url);
        query.bindValue(":timestamp",QDateTime::currentDateTime().toMSecsSinceEpoch());

        if(!query.exec()) {
            qDebug() << query.lastQuery() << query.lastError().text();
        }
        endResetModel();
    }
}

void BookmarksModel::removeFromBookmarks(QString url = "") {
    if(!url.isEmpty()){
        qDebug() << "Bookmarks removed:" << url;

        QSqlDatabase db = DbAdapter::instance().db;
        QSqlQuery query(db);

        if(!query.exec(QString("DELETE FROM bookmarks WHERE `url` LIKE '%1'").arg(url))) {
            qDebug() << query.lastQuery() << query.lastError().text();
        } else {
            p_setBookmarksSearch(m_bookmarksSearch);
        }
    }
}

void BookmarksModel::searchClear()
{
    beginResetModel();
    m_bookmarksSearchResult.clear();
    endResetModel();
}
