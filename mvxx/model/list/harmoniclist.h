#ifndef HARMONICLIST_H
#define HARMONICLIST_H

#include <QList>
#include "harmonicitembuilder.h"

class CHarmonicList final : public QObject
{
    Q_OBJECT
public:
    void addHarmonicItem(Trigonometric::Function func, double ampl, double freq, double phase);
    void replaceItem(int index, Trigonometric::Function func, double ampl, double freq, double phase);
    void removeHarmonicItem(int index);

    QSharedPointer<CHarmonicItem> getHarmonicItem(int index) const;
    int getSize() const;
    bool isEmpty() const;

private:
    QList<QSharedPointer<CHarmonicItem>> m_list;

signals:
    void listChanged();
};

#endif // HARMONICLIST_H
