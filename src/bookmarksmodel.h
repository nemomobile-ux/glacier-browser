#ifndef BOOKMARKSMODEL_H
#define BOOKMARKSMODEL_H

#include <QAbstractListModel>
#include <QObject>

class BookmarksModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString bookmarksSearch READ bookmarksSearch WRITE setBookmarksSearch NOTIFY bookmarksSearchChanged)

    struct bookmarksItem
    {
        QString title;
        QString url;
    };

public:
    explicit BookmarksModel(QObject *parent = nullptr);

    Q_INVOKABLE void insertToBookmarks(QString url, QString title);
    Q_INVOKABLE void removeFromBookmarks(QString url);
    Q_INVOKABLE void searchClear();

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {return hash;}

    QString bookmarksSearch() const {return m_bookmarksSearch;}
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

public slots:
    void setBookmarksSearch(QString bookmarksSearch);

signals:
    void bookmarksSearchChanged(QString bookmarksSearch);

private:
    QHash<int,QByteArray> hash;
    QString m_bookmarksSearch;
    QList<bookmarksItem> m_bookmarksSearchResult;

    void p_setBookmarksSearch(QString bookmarksSearch);
};

#endif // BOOKMARKSMODEL_H
