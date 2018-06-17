#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QSharedPointer>
#include <QListView>
#include <QPushButton>
#include <QAbstractListModel>

class CListView final : public QObject
{
    Q_OBJECT
public:
    CListView(QSharedPointer<QAbstractListModel> const& model, QWidget* listWidget);

private:
    void initialize();

    QSharedPointer<QAbstractListModel> m_model;
    QListView* m_list;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;

private slots:
    void onItemPressed(QModelIndex const& index);
    void onDataChanged();

signals:
    void itemPressed(QModelIndex const& index);
    void addButtonClicked();
    void deleteButtonClicked();
};

#endif // LISTVIEW_H
