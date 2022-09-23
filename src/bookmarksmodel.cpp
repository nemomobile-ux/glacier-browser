#include "bookmarksmodel.h"
#include "dbadapter.h"

BookmarksModel::BookmarksModel(QObject* parent)
    : QAbstractListModel(parent)
{
    hash.insert(Qt::UserRole, QByteArray("title"));
    hash.insert(Qt::UserRole + 1, QByteArray("url"));
    hash.insert(Qt::UserRole + 2, QByteArray("favicon"));

    beginResetModel();

    QSqlDatabase db = DbAdapter::instance().db;
    QSqlQuery query(db);
    QString weNeed = QString("SELECT DISTINCT title, url, favicon FROM bookmarks ORDER BY id ASC");

    if (!query.exec(weNeed)) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    m_bookmarksSearchResult.clear();
    while (query.next()) {
        BookmarksItem item;
        item.title = query.value(0).toString();
        item.url = query.value(1).toString();
        item.favicon = query.value(2).toString();

        m_bookmarksSearchResult.append(item);
    }

    endResetModel();
}

QVariant BookmarksModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        qDebug() << "noIndex";
        return QVariant();
    }

    if (index.row() >= m_bookmarksSearchResult.count()) {
        qDebug() << "bigSize";
        return QVariant();
    }

    BookmarksItem item = m_bookmarksSearchResult.at(index.row());
    switch (role) {
    case Qt::UserRole:
        return item.title;
    case Qt::UserRole + 1:
        return item.url;
    case Qt::UserRole + 2:
        return item.favicon;
    default:
        return QVariant();
    }
}

int BookmarksModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_bookmarksSearchResult.count();
}

void BookmarksModel::insertToBookmarks(QString url, QString title, QString favicon)
{
    if (!url.isEmpty() && !title.isEmpty()) {
        beginResetModel();

        QSqlDatabase db = DbAdapter::instance().db;
        QSqlQuery query(db);
        query.prepare("INSERT INTO bookmarks (`title`, `url`, `favicon`, `timestamp`) VALUES (:title, :url, :favicon, :timestamp)");
        query.bindValue(":title", title);
        query.bindValue(":url", url);
        query.bindValue(":favicon", favicon);
        query.bindValue(":timestamp", QDateTime::currentDateTime().toMSecsSinceEpoch());

        if (!query.exec()) {
            qDebug() << query.lastQuery() << query.lastError().text();
        }
        BookmarksItem item;
        item.title = title;
        item.url = url;
        item.favicon = favicon;
        m_bookmarksSearchResult.append(item);

        endResetModel();
    }
}

void BookmarksModel::removeFromBookmarks(QString url)
{
    if (!url.isEmpty()) {
        beginResetModel();
        qDebug() << "Bookmarks removed:" << url;

        QList<BookmarksItem>::iterator it = m_bookmarksSearchResult.begin();
        while (it != m_bookmarksSearchResult.end()) {
            if (it->url == url) {
                it = m_bookmarksSearchResult.erase(it);
            } else {
                it++;
            }
        }

        QSqlDatabase db = DbAdapter::instance().db;
        QSqlQuery query(db);

        if (!query.exec(QString("DELETE FROM bookmarks WHERE `url` LIKE '%1'").arg(url))) {
            qDebug() << query.lastQuery() << query.lastError().text();
        }

        endResetModel();
    }
}
