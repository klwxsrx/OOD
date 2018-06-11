#ifndef LISTPRESENTER_H
#define LISTPRESENTER_H

#include <QSharedPointer>
#include <QListView>
#include <QPushButton>
#include <QException>
#include "model/iharmonicitemlistmodel.h"

class CListPresenter : public QObject
{
    Q_OBJECT
public:
    CListPresenter(QSharedPointer<IHarmonicItemListModel> const& model, QWidget* listWidget);
    void initialize();

private:
    void updateCurrentSelection(QModelIndex const& index);

    QSharedPointer<IHarmonicItemListModel> m_model;
    QListView* m_list;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
};

#endif // LISTPRESENTER_H
