#ifndef COMPONENTSWIDGET_H
#define COMPONENTSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QListWidget>
#include <QKeyEvent>
#include "components.h"
#include "addeditcompoents.h"
#include "mydelegates.h"
#include "mytabwidget.h"
#include "mytreewidget.h"

namespace Ui {
class ComponentsWidget;
}

class ComponentsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentsWidget(QWidget *parent = 0);
    ~ComponentsWidget();

    const QList<Component*>* getComponentsList(ComponentType type) const;
    const QDoubleSpinBox* getCardReaderPriceDSpinbox() const;

signals:
    void componentsChanged();

public slots:
    void addComponent(Component* comp);
    void refreshAllComponents();
    void refreshPlatformsList(const QList<Platform *> *platformsList);
    void loadComponents(QList<Component*>* ListMB, QList<Component*>* ListCase,
                        QList<Component*>* ListCPU, QList<Component*>* ListCooler,
                        QList<Component*>* ListPSU, QList<Component*>* ListRAM,
                        QList<Component*>* ListHDD, QList<Component*>* ListVideo,
                        QList<Component*>* ListDVD, QList<Component*>* ListKbMouse,
                        QList<Component*>* ListSoft, QList<Component*>* listOthers,
                        double readerPrice);
    void removePlatform(QString platformForRemove);

private slots:
    void on_btnAddComponent_clicked();

    void on_btnDeleteComponent_clicked();

    void on_list_platforms_itemDoubleClicked(QListWidgetItem *item);

    void TabWidget_currentChanged(int index);

    void treeComponent_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void itemComponent_editValue(QTreeWidgetItem* item, int column);

    void on_doubleSpinBox_price_reader_valueChanged(double arg1);

private:
    Ui::ComponentsWidget *ui;
    MyTabWidget* TabWidget;
    MyTreeWidget* treeMB;
    MyTreeWidget* treeCase;
    MyTreeWidget* treeCPU;
    MyTreeWidget* treeCooler;
    MyTreeWidget* treePSU;
    MyTreeWidget* treeRAM;
    MyTreeWidget* treeHDD;
    MyTreeWidget* treeVideo;
    MyTreeWidget* treeDVD;
    MyTreeWidget* treeKbMouse;
    MyTreeWidget* treeSoft;
    MyTreeWidget* treeOthers;
    QList<Component*>* listMB;
    QList<Component*>* listCase;
    QList<Component*>* listCPU;
    QList<Component*>* listCooler;
    QList<Component*>* listPSU;
    QList<Component*>* listRAM;
    QList<Component*>* listHDD;
    QList<Component*>* listVideo;
    QList<Component*>* listDVD;
    QList<Component*>* listKbMouse;
    QList<Component*>* listSoft;
    QList<Component*>* listOthers;

    MyTreeWidget* addTreeWidget(QList<Component*>* list, QString name,
                                QString str1 = "", QString str2 = "");
    void refreshTree();

    void costPriceMarginEdit(QTreeWidgetItem* item, int column, MyTreeWidget *tree,
                             Component *componentForEdit);
    void advansedParametersEdit(QTreeWidgetItem* item, int column, Component* componentForEdit);

    void clearAndDeleteList(QList<Component*>* list);
    void clearAndDeleteAllLists();
};

#endif // COMPONENTSWIDGET_H
