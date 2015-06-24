#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>
#include "components.h"

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit MyTreeWidget(QWidget* parent = 0, QList<Component*>* list = NULL):
        QTreeWidget(parent), list(list) {}

    QList<Component*>* getList() const {return list;}
    void setList(QList<Component*>* list) {this->list = list;}

private:
    QList<Component*>* list;
};

#endif // MYTREEWIDGET_H
