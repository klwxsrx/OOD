#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QSharedPointer>
#include <QListView>
#include <QPushButton>
#include "model/iharmonicitemlistmodel.h"

class CListView : public QObject
{
    Q_OBJECT
public:
    CListView(QSharedPointer<IHarmonicItemListModel> const& model, QWidget* listWidget);

private slots:
    void onItemPressed(QModelIndex const& index);
    void onDataChanged();
    void onDeleteButtonClicked();

private:
    void initialize();

    QSharedPointer<IHarmonicItemListModel> m_model;
    QListView* m_list;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;

signals:
    void itemChanged(QModelIndex const& index);
    void deleteButtonClicked(QModelIndex const& index);
};

#endif // LISTVIEW_H
