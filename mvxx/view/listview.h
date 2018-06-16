#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QSharedPointer>
#include <QListView>
#include <QPushButton>
#include <QAbstractListModel>

class CListView : public QObject
{
    Q_OBJECT
public:
    CListView(QSharedPointer<QAbstractListModel> const& model, QWidget* listWidget);

private slots:
    void onItemPressed(QModelIndex const& index);
    void onDataChanged();

private:
    void initialize();

    QSharedPointer<QAbstractListModel> m_model;
    QListView* m_list;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;

signals:
    void itemChanged(QModelIndex const& index);
    void addButtonCLicked();
    void deleteButtonClicked();
};

#endif // LISTVIEW_H
