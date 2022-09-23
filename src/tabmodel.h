#ifndef TABMODEL_H
#define TABMODEL_H

#include <QAbstractListModel>
#include <QObject>

class TabModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)

public:
    explicit TabModel(QObject* parent = nullptr);
    ~TabModel();

    Q_INVOKABLE void addTab(QString url);
    Q_INVOKABLE void removeTab(int idx);
    Q_INVOKABLE void changeTab(int idx, QString url);
    Q_INVOKABLE int currentIndex() { return m_currentIndex; }

    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const { return hash; }
    int rowCount(const QModelIndex& parent = QModelIndex()) const;

public slots:
    void setCurrentIndex(int idx);

signals:
    void currentIndexChanged(int idx);
    void rowCountChanged();
    void tabChanged(int idx, QString url);

private:
    QList<QString> m_tabList;
    QHash<int, QByteArray> hash;
    int m_currentIndex;
};

#endif // TABMODEL_H
