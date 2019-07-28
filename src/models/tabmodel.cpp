#include "tabmodel.h"

#include <QDebug>

TabModel::TabModel(QObject *parent) : QAbstractListModel(parent)
{
    hash.insert(Qt::UserRole ,QByteArray("url"));
    m_currentIndex = m_tabList.count()-1;
}

TabModel::~TabModel()
{

}

void TabModel::addTab(QString url)
{
    if(!m_tabList.contains(url)) {

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_tabList.append(url);
        qDebug() << "addTab:" << url;
        m_currentIndex++;
        endInsertRows();
        emit rowCountChanged();
        emit currentIndexChanged(m_currentIndex);
        qDebug() << "Current index now:" << m_currentIndex;
    }
}

void TabModel::removeTab(int idx)
{
    if(idx < m_tabList.count()) {
        m_tabList.removeAt(idx);
        dataChanged(index(idx),index(idx));
        emit rowCountChanged();
    }
}

void TabModel::changeTab(int idx, QString url)
{
    if(idx < 0 || idx >= m_tabList.count())
    {
        return;
    }

    if(idx < m_tabList.count() && m_tabList[idx] != url) {
        m_tabList[idx] = url;
        dataChanged(index(idx),index(idx));
        emit tabChanged(idx,url);
        qDebug() << "tabChanged:" << idx << ":" << url;
    }
}

QVariant TabModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if(index.row() >= m_tabList.count()) {
        return QVariant();
    }

    switch (role) {
    case Qt::UserRole:
        return m_tabList[index.row()];
    default:
        return QVariant();
    }
}

int TabModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_tabList.count();
}

void TabModel::setCurrentIndex(int idx)
{
    if(idx < m_tabList.count() && idx != m_currentIndex ) {
        m_currentIndex = idx;
        emit currentIndexChanged(m_currentIndex);
    }
}
