#include "componentswidget.h"
#include "ui_componentswidget.h"

ComponentsWidget::ComponentsWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::ComponentsWidget)
{
    ui->setupUi(this);

    TabWidget = new MyTabWidget(this);
    connect(TabWidget, SIGNAL(currentChanged(int)), this, SLOT(TabWidget_currentChanged(int)));

    TabWidget->setTabPosition(QTabWidget::West);
    ui->verticalLayout_2->insertWidget(0, TabWidget);

    listMB      = new QList<Component*>;
    listCase    = new QList<Component*>;
    listCPU     = new QList<Component*>;
    listCooler  = new QList<Component*>;
    listPSU     = new QList<Component*>;
    listRAM     = new QList<Component*>;
    listHDD     = new QList<Component*>;
    listVideo   = new QList<Component*>;
    listDVD     = new QList<Component*>;
    listKbMouse = new QList<Component*>;
    listSoft    = new QList<Component*>;
    listOthers  = new QList<Component*>;

    treeMB      = addTreeWidget(listMB, COMPONENT_DEFAULT, "Материнские платы");
    treeCase    = addTreeWidget(listCase, COMPONENT_DEFAULT, "Корпусы");
    treeCPU     = addTreeWidget(listCPU, COMPONENT_DEFAULT, "Процессоры");
    treeCooler  = addTreeWidget(listCooler, COMPONENT_DEFAULT, "Куллеры");
    treePSU     = addTreeWidget(listPSU, COMPONENT_PSU, "Блоки питания", "Мощность");
    treeRAM     = addTreeWidget(listRAM, COMPONENT_RAM, "Опер. память", "Кол-во модулей",
                                "Общий объем");
    treeHDD     = addTreeWidget(listHDD, COMPONENT_DEFAULT, "HDD и SSD");
    treeVideo   = addTreeWidget(listVideo, COMPONENT_VIDEO, "Видеокарты",
                                "Ранг энергопотребления(1-3)");
    treeDVD     = addTreeWidget(listDVD, COMPONENT_DEFAULT, "DVD приводы");
    treeKbMouse = addTreeWidget(listKbMouse, COMPONENT_KB_MOUSE, "Клавиатуры и мыши",
                                "Тип(KB или Mouse)", "PS/2 или USB");
    treeSoft    = addTreeWidget(listSoft, COMPONENT_SOFT, "Софт", "Тип(OS, Lic, Other)");
    treeOthers  = addTreeWidget(listOthers, COMPONENT_OTHERS, "Дополнительно(PCIe)",
                                "размер PCIe(x...)");

    NoEditorDelegate* noEditDel = new NoEditorDelegate(this);
    MyDoubleSpinboxDelegate* doubleSpinBoxDel = new MyDoubleSpinboxDelegate(this);

    for(int i = 0; i < TabWidget->count(); ++i)
    {
        MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->widget(i));

        tree->setItemDelegateForColumn(0, noEditDel);
        tree->setItemDelegateForColumn(1, doubleSpinBoxDel);
        tree->setItemDelegateForColumn(2, doubleSpinBoxDel);
        tree->setItemDelegateForColumn(3, doubleSpinBoxDel);

        connect(tree, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
                this, SLOT(itemComponent_editValue(QTreeWidgetItem*,int)));
    }

    MySpinboxDelegate* spinBoxDel = new MySpinboxDelegate(this);
    treePSU->setItemDelegateForColumn(4, spinBoxDel);

    treeRAM->setItemDelegateForColumn(4, spinBoxDel);
    treeRAM->setItemDelegateForColumn(5, spinBoxDel);

    QStringList comboList;
    comboList << "Первый" << "Второй" << "Третий";
    MyComboboxDelegate* comboBoxVideoDel = new MyComboboxDelegate(comboList, this);
    treeVideo->setItemDelegateForColumn(4, comboBoxVideoDel);

    comboList.clear();
    comboList << "Клавиатура" << "Мышь";
    MyComboboxDelegate* comboBoxKbMouseTypeDel = new MyComboboxDelegate(comboList, this);
    treeKbMouse->setItemDelegateForColumn(4, comboBoxKbMouseTypeDel);

    comboList.clear();
    comboList << "PS/2" << "USB";
    MyComboboxDelegate* comboBoxKbMouseConnectorDel = new MyComboboxDelegate(comboList, this);
    treeKbMouse->setItemDelegateForColumn(5, comboBoxKbMouseConnectorDel);

    comboList.clear();
    comboList << "ОС" << "Лицензия" << "Другой софт";
    MyComboboxDelegate* comboBoxSoftDel = new MyComboboxDelegate(comboList, this);
    treeSoft->setItemDelegateForColumn(4, comboBoxSoftDel);

    comboList.clear();
    comboList << "x1" << "x4" << "x8" << "x16";
    MyComboboxDelegate* comboBoxOthersDel = new MyComboboxDelegate(comboList, this);
    treeOthers->setItemDelegateForColumn(4, comboBoxOthersDel);

    treeMB->header()->resizeSections(QHeaderView::ResizeToContents);
}

void ComponentsWidget::clearAndDeleteList(QList<Component *> *list)
{
    qDeleteAll(list->begin(), list->end());
    list->clear();
    delete list;
}

void ComponentsWidget::clearAndDeleteAllLists()
{
    clearAndDeleteList(listMB);
    clearAndDeleteList(listCase);
    clearAndDeleteList(listCPU);
    clearAndDeleteList(listCooler);
    clearAndDeleteList(listPSU);
    clearAndDeleteList(listRAM);
    clearAndDeleteList(listHDD);
    clearAndDeleteList(listVideo);
    clearAndDeleteList(listDVD);
    clearAndDeleteList(listKbMouse);
    clearAndDeleteList(listSoft);
    clearAndDeleteList(listOthers);
}

ComponentsWidget::~ComponentsWidget()
{
    clearAndDeleteAllLists();
    delete ui;
}

const QList<Component *> *ComponentsWidget::getComponentsList(ComponentType type) const
{
    switch(type)
    {
        case COMPONENT_MB: return this->listMB;
        case COMPONENT_CASE: return this->listCase;
        case COMPONENT_CPU: return this->listCPU;
        case COMPONENT_COOLER: return this->listCooler;
        case COMPONENT_PSU: return this->listPSU;
        case COMPONENT_RAM: return this->listRAM;
        case COMPONENT_HDD: return this->listHDD;
        case COMPONENT_VIDEO: return this->listVideo;
        case COMPONENT_DVD: return this->listDVD;
        case COMPONENT_KB_MOUSE: return this->listKbMouse;
        case COMPONENT_SOFT: return this->listSoft;
        case COMPONENT_OTHERS: return this->listOthers;
        case COMPONENT_DEFAULT: qDebug() << "Неверный параметр для функции getComponentsList";
    }
    return NULL;
}

const QDoubleSpinBox *ComponentsWidget::getCardReaderPriceDSpinbox() const
{
    return ui->doubleSpinBox_price_reader;
}

void ComponentsWidget::refreshTree()
{
    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());
    tree->clear();

    QListIterator<Component*> i(*tree->getList());
    while (i.hasNext())
    {
        Component* comp = i.next();
        tree->addTopLevelItem(comp->getTreeWidgetItem());
    }
    tree->header()->resizeSections(QHeaderView::ResizeToContents);
    emit componentsChanged();
}

void ComponentsWidget::refreshAllComponents()
{
    for(int i = 0; i < TabWidget->count(); ++i)
    {
        TabWidget->setCurrentIndex(i);
        refreshTree();
    }
    TabWidget->setCurrentIndex(0);
}

void ComponentsWidget::refreshPlatformsList(const QList<Platform *> * platformsList)
{
    ui->list_platforms->clear();
    foreach(Platform* platf, *(platformsList))
    {
        ui->list_platforms->addItem(platf->getName());
    }

    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());
    treeComponent_currentItemChanged(tree->currentItem(), NULL);
}

void ComponentsWidget::loadComponents(QList<Component*>* ListMB, QList<Component*>* ListCase,
                                      QList<Component*>* ListCPU, QList<Component*>* ListCooler,
                                      QList<Component*>* ListPSU, QList<Component*>* ListRAM,
                                      QList<Component*>* ListHDD, QList<Component*>* ListVideo,
                                      QList<Component*>* ListDVD, QList<Component*>* ListKbMouse,
                                      QList<Component*>* ListSoft, QList<Component*>* ListOthers,
                                      double readerPrice)
{
    clearAndDeleteAllLists();

    this->listMB = ListMB;
    this->listCase = ListCase;
    this->listCPU = ListCPU;
    this->listCooler = ListCooler;
    this->listPSU = ListPSU;
    this->listRAM = ListRAM;
    this->listHDD = ListHDD;
    this->listVideo = ListVideo;
    this->listDVD = ListDVD;
    this->listKbMouse = ListKbMouse;
    this->listSoft = ListSoft;
    this->listOthers = ListOthers;

    treeMB->setList(listMB);
    treeCase->setList(listCase);
    treeCPU->setList(listCPU);
    treeCooler->setList(listCooler);
    treePSU->setList(listPSU);
    treeRAM->setList(listRAM);
    treeHDD->setList(listHDD);
    treeVideo->setList(listVideo);
    treeDVD->setList(listDVD);
    treeKbMouse->setList(listKbMouse);
    treeSoft->setList(listSoft);
    treeOthers->setList(listOthers);

    ui->doubleSpinBox_price_reader->setValue(readerPrice);

    refreshAllComponents();
}

void ComponentsWidget::removePlatform(QString platformForRemove)
{
    for(int i = 0; i < TabWidget->count(); ++i)
    {
        MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->widget(i));
        foreach (Component* comp, *(tree->getList()))
        {
            foreach(QString platf, *(comp->getConnectedPlatforms()))
            {
                if(platf == platformForRemove)
                {
                    comp->delPlatform(platf);
                }
            }
        }
    }
}

void ComponentsWidget::addComponent(Component *comp)
{
    /*qDebug() << "Cost = " << comp->getCost();
    qDebug() << "Price = " << comp->getPrice();
    qDebug() << "Margin = " << comp->getMargin();*/

    comp->setParent(this);
    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());
    tree->getList()->append(comp);
    refreshTree();
}

MyTreeWidget *ComponentsWidget::addTreeWidget(QList<Component*>* list, ComponentType type,
                                              QString name, QString str1, QString str2)
{
    QStringList strTreeHeaderLables;
    strTreeHeaderLables.append("Название");
    strTreeHeaderLables.append("Входная цена");
    strTreeHeaderLables.append("Выходная цена");
    strTreeHeaderLables.append("Маржинальность");

    MyTreeWidget* result = new MyTreeWidget(this, list, type);
    QObject::connect(result, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this,
                     SLOT(treeComponent_currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
    if(str1 != "")
    {
        if(str2 != "")
        {
            result->setColumnCount(6);
            strTreeHeaderLables.append(str1);
            strTreeHeaderLables.append(str2);
        }
        else
        {
            result->setColumnCount(5);
            strTreeHeaderLables.append(str1);
        }
    }
    else
    {
        result->setColumnCount(4);
    }

    result->setHeaderLabels(strTreeHeaderLables);
    result->header()->setStretchLastSection(false);
    result->header()->resizeSections(QHeaderView::ResizeToContents);
    result->setSortingEnabled(true);
    TabWidget->addTab(result, name);

    return result;
}

void ComponentsWidget::on_btnAddComponent_clicked()
{
    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());

    addEditCompoents componentsDialog(tree->getType(), *(tree->getList()), this);
    connect(&componentsDialog, SIGNAL(sendComponent(Component*)),
            this, SLOT(addComponent(Component*)));
    componentsDialog.exec();
}

void ComponentsWidget::on_btnDeleteComponent_clicked()
{
    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());
    if(tree->currentItem() == NULL)
        return;

    QMutableListIterator<Component*> i(*(tree->getList()));
    while(i.hasNext())
    {
        Component* comp = i.next();
        if (comp->getName() == tree->currentItem()->text(0))
        {
            delete comp;
            i.remove();
            refreshTree();
            return;
        }
    }
}

void ComponentsWidget::on_list_platforms_itemDoubleClicked(QListWidgetItem *item)
{
    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());
    if(tree->currentItem() == NULL)
        return;

    if(item->backgroundColor() == Qt::blue && item->textColor() == Qt::white)
    {
        foreach (Component* comp, *(tree->getList()))
        {
            if(comp->getName() == tree->currentItem()->text(0))
            {
                foreach(QString platf, *(comp->getConnectedPlatforms()))
                {
                    if(item->text() == platf)
                    {
                        comp->delPlatform(platf);
                        qDebug() << "Платформа " << platf
                                 << " отвязана от компонента: " << comp->getName();
                        item->setBackgroundColor(Qt::white);
                        item->setTextColor(Qt::black);
                        emit componentsChanged();
                        break;
                    }
                }
                break;
            }
        }
    }
    else
    {
        foreach (Component* comp, *(tree->getList()))
        {
            if(comp->getName() == tree->currentItem()->text(0))
            {
                comp->addPlatform(item->text());
                qDebug() << "Платформа" << item->text()
                         << " привязана к компоненту: " << comp->getName();
                item->setBackgroundColor(Qt::blue);
                item->setTextColor(Qt::white);
                emit componentsChanged();
                break;
            }
        }
    }
}

void ComponentsWidget::TabWidget_currentChanged(int index)
{
    Q_UNUSED(index)

    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());
    treeComponent_currentItemChanged(tree->currentItem(), NULL);
}

void ComponentsWidget::treeComponent_currentItemChanged(QTreeWidgetItem *current,
                                                        QTreeWidgetItem *previous)
{
    Q_UNUSED(previous)

    for (int i = 0; i < ui->list_platforms->count(); i++)
    {
        ui->list_platforms->item(i)->setBackgroundColor(Qt::white);
        ui->list_platforms->item(i)->setTextColor(Qt::black);
    }

    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());
    if(tree->currentItem() == NULL)
        return;

    foreach (Component* comp, *(tree->getList()))
    {
        if(comp->getName() == current->text(0))
        {

            foreach(QString platf, *(comp->getConnectedPlatforms()))
            {
                QList<QListWidgetItem*> fndPlatf =
                        ui->list_platforms->findItems(platf, Qt::MatchCaseSensitive);

                foreach(QListWidgetItem* listItm, fndPlatf)
                {
                    listItm->setBackgroundColor(Qt::blue);
                    listItm->setTextColor(Qt::white);
                }
            }
            break;
        }
    }
}

void ComponentsWidget::itemComponent_editValue(QTreeWidgetItem *item, int column)
{
    if(column == 0)
        return;

    MyTreeWidget* tree = static_cast<MyTreeWidget*>(TabWidget->currentWidget());
    Component* componentForEdit = NULL;

    foreach (Component* comp, *(tree->getList()))
    {
        if(comp->getName() == item->text(0))
            componentForEdit = comp;
    }

    if(column <= 3)
        costPriceMarginEdit(item, column, tree, componentForEdit);
    else
    {
        componentForEdit->setAdvancedParameter(item, column);
        emit componentsChanged();
    }
}

void ComponentsWidget::costPriceMarginEdit(QTreeWidgetItem *item, int column, MyTreeWidget* tree,
                                           Component* componentForEdit)
{
    switch(column)
    {
    case 1 :
        {
            componentForEdit->editCost(item->text(column).toDouble());
            break;
        }
    case 2 :
        {
            componentForEdit->editPrice(item->text(column).toDouble());
            break;
        }
    case 3 :
        {
            componentForEdit->editMargin(item->text(column).toDouble());
            break;
        }
    default : return;
    }
    disconnect(tree, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this, SLOT(itemComponent_editValue(QTreeWidgetItem*,int)));

    item->setText(1, QString::number(componentForEdit->getCost(),'f', 2));
    item->setText(2, QString::number(componentForEdit->getPrice(),'f', 2));
    item->setText(3, QString::number(componentForEdit->getMargin(),'f', 2)+"%");

    connect(tree, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this, SLOT(itemComponent_editValue(QTreeWidgetItem*,int)));
    emit componentsChanged();
}

void ComponentsWidget::on_doubleSpinBox_price_reader_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    emit componentsChanged();
}
