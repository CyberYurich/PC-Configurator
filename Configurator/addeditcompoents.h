#ifndef ADDEDITCOMPOENTS_H
#define ADDEDITCOMPOENTS_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QMessageBox>
#include "components.h"
#include "componentswidget.h"

namespace Ui {
class addEditCompoents;
}

class addEditCompoents : public QDialog
{
    Q_OBJECT

public:
    explicit addEditCompoents(ComponentType type, QList<Component*> listForCheck,
                              QWidget *parent = 0);

    ~addEditCompoents();

signals:
    void sendComponent(Component* comp);
    void refreshComponents();

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_ok_clicked();

    void on_doubleSpinBox_cost_editingFinished();

    void on_doubleSpinBox_price_editingFinished();

    void on_doubleSpinBox_margin_editingFinished();

private:
    Ui::addEditCompoents *ui;
    ComponentType type;
    QList<Component*> listForCheck;
    QLineEdit* line;
    QSpinBox* spin1;
    QSpinBox* spin2;
    QComboBox* combo1;
    QComboBox* combo2;


};

#endif // ADDEDITCOMPOENTS_H
