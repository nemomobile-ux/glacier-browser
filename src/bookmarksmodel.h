#ifndef BOOKMARKSMODEL_H
#define BOOKMARKSMODEL_H

#include <QAbstractListModel>
#include <QObject>

class BookmarksModel : public QAbstractListModel
{
    Q_OBJECT

    struct BookmarksItem
    {
        QString title;
        QString url;
    };

public:
    explicit BookmarksModel(QObject *parent = nullptr);

    Q_INVOKABLE void insertToBookmarks(QString url = "", QString title = "");
    Q_INVOKABLE void removeFromBookmarks(QString url = "");


    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {return hash;}
    int rowCount(const QModelIndex &parent = QModelIndex()) const;


private:
    QHash<int,QByteArray> hash;
    QList<BookmarksItem> m_bookmarksSearchResult;


};

#endif // BOOKMARKSMODEL_H
