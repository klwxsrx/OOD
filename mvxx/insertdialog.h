#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include <QSharedPointer>
#include "model/newharmonicviewmodel.h"
#include "view/editharmonicview.h"
#include "controller/editharmoniccontroller.h"
#include "ui_insertdialog.h"

namespace Ui
{
    class Dialog;
}

class CInsertHarmonicDialog final : public QDialog
{
    Q_OBJECT
public:
    CInsertHarmonicDialog();

private:
    QSharedPointer<CNewHarmonicViewModel> m_model;
    QSharedPointer<CEditHarmonicController> m_controller;
    QSharedPointer<Ui::Dialog> m_ui;

private slots:
    void accept() override;

signals:
    dialogAccepted(Trigonometric::Function func, double ampl, double freq, double phase);
};

#endif // INSERTDIALOG_H
