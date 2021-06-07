#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QAbstractListModel>
#include <QObject>

class HistoryModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString historySearch READ historySearch WRITE setHistorySearch NOTIFY historySearchChanged)

    struct historyItem
    {
        QString title;
        QString url;
    };

public:
    explicit HistoryModel(QObject *parent = nullptr);

    Q_INVOKABLE void insertToHistory(QString url, QString title);
    Q_INVOKABLE void removeFromHistory(QString url);
    Q_INVOKABLE void searchClear();

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {return hash;}

    QString historySearch() const {return m_historySearch;}
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

public slots:
    void setHistorySearch(QString historySearch);

signals:
    void historySearchChanged(QString historySearch);

private:
    QHash<int,QByteArray> hash;
    QString m_historySearch;
    QList<historyItem> m_historySearchResult;

    void p_setHistorySearch(QString historySearch);
};

#endif // HISTORYMODEL_H
