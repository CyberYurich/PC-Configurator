#include "platformswidget.h"
#include "ui_platformswidget.h"

PlatformsWidget::PlatformsWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::PlatformsWidget)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(24);

    QStringList strTreeHeaderLables;
    strTreeHeaderLables.append("Название");
    strTreeHeaderLables.append("Описание");
    strTreeHeaderLables.append("Чипсет");
    strTreeHeaderLables.append("Сокет");
    strTreeHeaderLables.append("Звук");
    strTreeHeaderLables.append("Сеть");
    strTreeHeaderLables.append("Кол-во USB 2.0");
    strTreeHeaderLables.append("Кол-во USB 3.0");
    strTreeHeaderLables.append("Кол-во SATA");
    strTreeHeaderLables.append("Из них SATA 3");
    strTreeHeaderLables.append("Кол-во DIMM");
    strTreeHeaderLables.append("Ограничение по RAM(Gb)");
    strTreeHeaderLables.append("Интегр. видео");
    strTreeHeaderLables.append("Порты VGA");
    strTreeHeaderLables.append("Порты DVI");
    strTreeHeaderLables.append("Порты HDMI");
    strTreeHeaderLables.append("Кол-во PCIe  x1");
    strTreeHeaderLables.append("Кол-во PCIe  x4");
    strTreeHeaderLables.append("Кол-во PCIe  x8");
    strTreeHeaderLables.append("Кол-во PCIe  x16");
    strTreeHeaderLables.append("Кол-во PS/2");
    strTreeHeaderLables.append("Форм-фактор корпуса");
    strTreeHeaderLables.append("Кол-во 5,25");
    strTreeHeaderLables.append("Кол-во внешних 3,5");
    strTreeHeaderLables.append("Кол-во внутренних 3,5");
    strTreeHeaderLables.append("Встроенный БП");
    strTreeHeaderLables.append("Мощность БП");

    ui->treeWidget->setHeaderLabels(strTreeHeaderLables);
    ui->treeWidget->header()->resizeSections(QHeaderView::ResizeToContents);
    ui->treeWidget->setSortingEnabled(true);

    platformsList = new QList<Platform*>;

}

void PlatformsWidget::clearAndDeletePlatforms(QList<Platform *> *list)
{
    qDeleteAll(list->begin(), list->end());
    list->clear();
    delete list;
}

PlatformsWidget::~PlatformsWidget()
{
    clearAndDeletePlatforms(platformsList);

    delete ui;
}

void PlatformsWidget::refreshPlatforms()
{
    ui->treeWidget->clear();
    QListIterator<Platform*> i(*platformsList);
    while (i.hasNext())
    {
        Platform* platf = i.next();
        QTreeWidgetItem* itm = new QTreeWidgetItem(24);
        itm->setText(0, platf->getName());
        itm->setText(1, platf->getDescription());
        itm->setText(2, platf->getChipset());
        itm->setText(3, QString::number(platf->getSocket()));
        itm->setText(4, platf->getSound());
        itm->setText(5, platf->getLan());
        itm->setText(6, QString::number(platf->getUsb2()));
        itm->setText(7, QString::number(platf->getUsb3()));
        itm->setText(8, QString::number(platf->getSata()));
        itm->setText(9, QString::number(platf->getSata3()));     
        itm->setText(10, QString::number(platf->getDimm()));
        itm->setText(11, QString::number(platf->getRam()));
        itm->setText(12, (platf->getIntegrVideo() ? "Да" : "Нет"));
        itm->setText(13, (platf->getVga() ? "Да" : "Нет"));
        itm->setText(14, (platf->getDvi() ? "Да" : "Нет"));
        itm->setText(15, (platf->getHdmi() ? "Да" : "Нет"));
        itm->setText(16, QString::number(platf->getPcie1()));
        itm->setText(17, QString::number(platf->getPcie4()));
        itm->setText(18, QString::number(platf->getPcie8()));
        itm->setText(19, QString::number(platf->getPcie16()));
        itm->setText(20, QString::number(platf->getPs2()));
        itm->setText(21, platf->getCaseForm());
        itm->setText(22, QString::number(platf->getExt5_25()));
        itm->setText(23, QString::number(platf->getExt3_5()));
        itm->setText(24, QString::number(platf->getInt3_5()));
        itm->setText(25, (platf->getIntegrPsu() ? "Да" : "Нет"));
        itm->setText(26, QString::number(platf->getPsuPower()));
        ui->treeWidget->addTopLevelItem(itm);
    }
    ui->treeWidget->header()->resizeSections(QHeaderView::ResizeToContents);
    emit platformsChanged();
}

void PlatformsWidget::addPlatform(Platform* platf)
{
    platf->setParent(this);
    platformsList->append(platf);
    refreshPlatforms();
}

void PlatformsWidget::loadPlatforms(QList<Platform*>* platformsList)
{
    clearAndDeletePlatforms(this->platformsList);

    this->platformsList = platformsList;
    refreshPlatforms();
}

void PlatformsWidget::on_btnAddPlatform_clicked()
{
   addEditPlatformDialog platformDialog(*platformsList, this);
   connect(&platformDialog, SIGNAL(sendPlatform(Platform*)), this, SLOT(addPlatform(Platform*)));
   platformDialog.exec();
}

void PlatformsWidget::on_btnDeletePlatform_clicked()
{
    if (ui->treeWidget->currentItem() == NULL)
        return;

    QMutableListIterator<Platform*> i(*platformsList);
    while(i.hasNext())
    {
        Platform* platf = i.next();
        if (platf->getName() == ui->treeWidget->currentItem()->text(0))
        {
            emit removePlatformFromComponents(platf->getName());
            delete platf;
            i.remove();
            refreshPlatforms();
            return;
        }
    }

    //Альтернатива с STL итератором
    /*
    QList<Platform*>::iterator it = platformsList->begin();
    for (; it != platformsList->end(); ++it)
    {
        if ((*it)->getName() == ui->treeWidget->currentItem()->text(0))
        {
            emit removePlatformFromComponents(platf->getName());
            delete (*it);
            it = platformsList->erase(it);
            refreshPlatforms();
            return;
        }
    }
    */
}

void PlatformsWidget::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item)
{
    QListIterator<Platform*> i(*platformsList);
    Platform* platf = NULL;
    while (i.hasNext())
    {
        if (i.next()->getName() == item->text(0))
        {
            platf = i.peekPrevious();
            break;
        }
    }

    if (platf != NULL)
    {
        addEditPlatformDialog platformDialog(item->text(0),
                                             item->text(1),
                                             item->text(2),
                                             item->text(3).toInt(),
                                             item->text(4),
                                             item->text(5),
                                             item->text(6).toShort(),
                                             item->text(7).toShort(),
                                             item->text(8).toShort(),
                                             item->text(9).toShort(),
                                             item->text(10).toShort(),
                                             item->text(11).toShort(),
                                             item->text(12) == "Да" ? true : false,
                                             item->text(13) == "Да" ? true : false,
                                             item->text(14) == "Да" ? true : false,
                                             item->text(15) == "Да" ? true : false,
                                             item->text(16).toShort(),
                                             item->text(17).toShort(),
                                             item->text(18).toShort(),
                                             item->text(19).toShort(),
                                             item->text(20).toShort(),
                                             item->text(21),
                                             item->text(22).toShort(),
                                             item->text(23).toShort(),
                                             item->text(24).toShort(),
                                             item->text(25) == "Да" ? true : false,
                                             item->text(26).toInt(),
                                             platf, this);

        connect(&platformDialog, SIGNAL(refreshPlatforms()), this, SLOT(refreshPlatforms()));
        platformDialog.exec();
    }
    else
    {
        qDebug() << "Ошибка при передаче указателя на редактируемую платформу";
    }
}
