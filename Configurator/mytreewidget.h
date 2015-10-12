#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>
#include "components.h"

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit MyTreeWidget(QWidget* parent = 0, QList<Component*>* list = NULL,
                          ComponentType type = COMPONENT_DEFAULT):
        QTreeWidget(parent), list(list), type(type) {}

    QList<Component*>* getList() const {return list;}
    void setList(QList<Component*>* list) {this->list = list;}

    ComponentType getType() const {return type;}
    void setType(ComponentType type) {this->type = type;}

private:
    QList<Component*>* list;
    ComponentType type;
};

#endif // MYTREEWIDGET_H
