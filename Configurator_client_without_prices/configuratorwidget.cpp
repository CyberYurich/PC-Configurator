#include "configuratorwidget.h"
#include "ui_configuratorwidget.h"

ConfiguratorWidget::ConfiguratorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfiguratorWidget)
{
    ui->setupUi(this);
    this->setStyleSheet("QLineEdit { background: white; color: black }"
                        "QComboBox { color: black }");

    ui->comboBox_Platform->installEventFilter(this);
    ui->comboBox_MB->installEventFilter(this);
    ui->comboBox_Case->installEventFilter(this);
    ui->comboBox_CPU->installEventFilter(this);
    ui->comboBox_Cooler->installEventFilter(this);
    ui->comboBox_PSU->installEventFilter(this);
    ui->comboBox_RAM->installEventFilter(this);
    ui->comboBox_HDD1->installEventFilter(this);
    ui->comboBox_HDD2->installEventFilter(this);
    ui->comboBox_HDD3->installEventFilter(this);
    ui->comboBox_HDD4->installEventFilter(this);
    ui->comboBox_Video->installEventFilter(this);
    ui->comboBox_DVD->installEventFilter(this);
    ui->checkBox_Reader->installEventFilter(this);
    ui->comboBox_KB->installEventFilter(this);
    ui->comboBox_Mouse->installEventFilter(this);
    ui->comboBox_OS->installEventFilter(this);
    ui->comboBox_Lic->installEventFilter(this);
    ui->comboBox_Soft1->installEventFilter(this);
    ui->comboBox_Soft2->installEventFilter(this);
    ui->comboBox_Other1->installEventFilter(this);
    ui->comboBox_Other2->installEventFilter(this);
    ui->comboBox_Other3->installEventFilter(this);
    ui->comboBox_Other4->installEventFilter(this);

    ui->spinBox_RAM->installEventFilter(this);
    ui->spinBox_HDD1->installEventFilter(this);
    ui->spinBox_HDD2->installEventFilter(this);
    ui->spinBox_HDD3->installEventFilter(this);
    ui->spinBox_HDD4->installEventFilter(this);
    ui->spinBox_Video->installEventFilter(this);
    ui->spinBox_DVD->installEventFilter(this);
    ui->spinBox_KB->installEventFilter(this);
    ui->spinBox_Mouse->installEventFilter(this);
    ui->spinBox_OS->installEventFilter(this);
    ui->spinBox_Lic->installEventFilter(this);
    ui->spinBox_Soft1->installEventFilter(this);
    ui->spinBox_Soft2->installEventFilter(this);
    ui->spinBox_Other1->installEventFilter(this);
    ui->spinBox_Other2->installEventFilter(this);
    ui->spinBox_Other3->installEventFilter(this);
    ui->spinBox_Other4->installEventFilter(this);
    ui->spinBox_quantity->installEventFilter(this);

    connect(ui->spinBox_RAM, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_RAM_currentIndexChanged(QString)));
    connect(ui->spinBox_HDD1, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_HDD1_currentIndexChanged(QString)));
    connect(ui->spinBox_HDD2, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_HDD2_currentIndexChanged(QString)));
    connect(ui->spinBox_HDD3, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_HDD3_currentIndexChanged(QString)));
    connect(ui->spinBox_HDD4, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_HDD4_currentIndexChanged(QString)));
    connect(ui->spinBox_Video, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Video_currentIndexChanged(QString)));
    connect(ui->spinBox_DVD, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_DVD_currentIndexChanged(QString)));
    connect(ui->spinBox_KB, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_KB_currentIndexChanged(QString)));
    connect(ui->spinBox_Mouse, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Mouse_currentIndexChanged(QString)));
    connect(ui->spinBox_OS, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_OS_currentIndexChanged(QString)));
    connect(ui->spinBox_Lic, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Lic_currentIndexChanged(QString)));
    connect(ui->spinBox_Soft1, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Soft1_currentIndexChanged(QString)));
    connect(ui->spinBox_Soft2, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Soft2_currentIndexChanged(QString)));
    connect(ui->spinBox_Other1, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Other1_currentIndexChanged(QString)));
    connect(ui->spinBox_Other2, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Other2_currentIndexChanged(QString)));
    connect(ui->spinBox_Other3, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Other3_currentIndexChanged(QString)));
    connect(ui->spinBox_Other4, SIGNAL(valueChanged(QString)),
            this, SLOT(on_comboBox_Other4_currentIndexChanged(QString)));

    connect(ui->spinBox_quantity, SIGNAL(valueChanged(QString)),
            this, SLOT(on_lineEdit_price_All_textChanged(QString)));

    otherSettings = new QSettings("settings.ini", QSettings::IniFormat, this);
}

ConfiguratorWidget::~ConfiguratorWidget()
{
    delete ui;
}

void ConfiguratorWidget::connectConfigurator(const QList<Platform*>* platformsList,
                                             const QList<Component*>** arrayOfComponentsLists,
                                             double cardReaderPrice)
{
    this->platformsList = platformsList;
    this->arrayOfComponentsLists = arrayOfComponentsLists;
    this->cardReaderPrice = cardReaderPrice;
}

void ConfiguratorWidget::refreshDescription()
{
    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    if(curPlatform == NULL)
    {
        ui->textBrowser_Desc->clear();
        return;
    }

    QString htmlText = "<b>%1</b><br>"
            "<table width=100%>"
                "<tr>"
                    "<td><b>Чипсет</b> - %2</td>"
                    "<td><b>Сокет</b> - %3</td>"
                    "<td><b>Звук</b> - %4</td>"
                "</tr>"
                "<tr>"
                    "<td><b>Сеть</b> - %5</td>"
                    "<td><b>Кол-во USB 2.0</b> - %6</td>"
                    "<td><b>Кол-во USB 3.0</b> - %7</td>"
                "</tr>"
                "<tr>"
                    "<td><b>Кол-во SATA</b> - %8</td>"
                    "<td><b>Из них SATA3</b> - %9</td>"
                    "<td><b>Кол-во DIMM</b> - %10</td>"
                "</tr>"
                "<tr>"
                    "<td><b>Максимум RAM(Gb)</b> - %11</td>"
                    "<td><b>Интегрир. видео</b> - %12</td>"
                    "<td><b>Порты VGA</b> - %13</td>"
                "</tr>"
                "<tr>"
                    "<td><b>Порты DVI</b> - %14</td>"
                    "<td><b>Порты HDMI</b> - %15</td>"
                    "<td><b>Кол-во PCIe x1</b> - %16</td>"
                "</tr>"
                "<tr>"
                    "<td><b>Кол-во PCIe x4</b> - %17</td>"
                    "<td><b>Кол-во PCIe x8</b> - %18</td>"
                    "<td><b>Кол-во PCIe x16</b> - %19</td>"
                "</tr>"
                "<tr>"
                    "<td><b>Кол-во PS/2</b> - %20</td>"
                    "<td><b>Корпус</b> - %21</td>"
                    "<td><b>Кол-во 5.25</b> - %22</td>"
                "</tr>"
                "<tr>"
                    "<td><b>Кол-во внешних 3.5</b> - %23</td>"
                    "<td><b>Кол-во внутренних 3.5</b> - %24</td>"
                    "<td><b>Встроенный БП</b> - %25</td>"
                "</tr>"
            "</table>";

    ui->textBrowser_Desc->clear();
    ui->textBrowser_Desc->setHtml(htmlText.arg(curPlatform->getDescription())
                                          .arg(curPlatform->getChipset())
                                          .arg(curPlatform->getSocket())
                                          .arg(curPlatform->getSound())
                                          .arg(curPlatform->getLan())
                                          .arg(curPlatform->getUsb2())
                                          .arg(curPlatform->getUsb3())
                                          .arg(curPlatform->getSata())
                                          .arg(curPlatform->getSata3())
                                          .arg(curPlatform->getDimm())
                                          .arg(curPlatform->getRam())
                                          .arg(curPlatform->getIntegrVideo() ? "Да" : "Нет")
                                          .arg(curPlatform->getVga() ? "Да" : "Нет")
                                          .arg(curPlatform->getDvi() ? "Да" : "Нет")
                                          .arg(curPlatform->getHdmi() ? "Да" : "Нет")
                                          .arg(curPlatform->getPcie1())
                                          .arg(curPlatform->getPcie4())
                                          .arg(curPlatform->getPcie8())
                                          .arg(curPlatform->getPcie16())
                                          .arg(curPlatform->getPs2())
                                          .arg(curPlatform->getCaseForm())
                                          .arg(curPlatform->getExt5_25())
                                          .arg(curPlatform->getExt3_5())
                                          .arg(curPlatform->getInt3_5())
                                          .arg(curPlatform->getIntegrPsu() ? "Да" : "Нет"));

    if(curPlatform->getIntegrPsu())
    {
        ui->textBrowser_Desc->append(QString("<b>Мощность БП</b> - %1")
                                     .arg(curPlatform->getPsuPower()));
    }
}

void ConfiguratorWidget::clearCombobox(QComboBox *box)
{
    box->blockSignals(true);
    box->clear();
    box->blockSignals(false);
}

void ConfiguratorWidget::clearSpinbox(QSpinBox *box)
{
    box->blockSignals(true);
    box->setMinimum(0);
    box->setValue(0);
    box->blockSignals(false);
}

void ConfiguratorWidget::refreshCombobox(QComboBox* box, int compArrIndex, bool isRequired)
{
    clearCombobox(box);

    if(isRequired == false)
        box->addItem("---");

    foreach(Component* comp, *(this->arrayOfComponentsLists[compArrIndex]))
    {
        if(box == ui->comboBox_PSU)
        {
            PSU* psu = static_cast<PSU*>(comp);
            foreach(QString platf, *(psu->getConnectedPlatforms()))
            {
                if(platf == ui->comboBox_Platform->currentText())
                {
                    box->addItem(psu->getName(), QVariant::fromValue(psu));
                    break;
                }
            }
        }
        else if(box == ui->comboBox_RAM)
        {
            RAM* ram = static_cast<RAM*>(comp);
            foreach(QString platf, *(ram->getConnectedPlatforms()))
            {
                if(platf == ui->comboBox_Platform->currentText())
                {
                    box->addItem(ram->getName(), QVariant::fromValue(ram));
                    break;
                }
            }
        }
        else if(box == ui->comboBox_Video)
        {
            Video* video = static_cast<Video*>(comp);
            foreach(QString platf, *(video->getConnectedPlatforms()))
            {
                if(platf == ui->comboBox_Platform->currentText())
                {
                    box->addItem(video->getName(), QVariant::fromValue(video));
                    break;
                }
            }
        }
        else if(box == ui->comboBox_KB)
        {
            KbMouse* kb = static_cast<KbMouse*>(comp);
            if(kb->getTypeKbMouse() == "Клавиатура")
            {
                foreach(QString platf, *(kb->getConnectedPlatforms()))
                {
                    if(platf == ui->comboBox_Platform->currentText())
                    {
                        box->addItem(kb->getName(), QVariant::fromValue(kb));
                        break;
                    }
                }
            }
        }
        else if(box == ui->comboBox_Mouse)
        {
            KbMouse* mouse = static_cast<KbMouse*>(comp);
            if(mouse->getTypeKbMouse() == "Мышь")
            {
                foreach(QString platf, *(mouse->getConnectedPlatforms()))
                {
                    if(platf == ui->comboBox_Platform->currentText())
                    {
                        box->addItem(mouse->getName(), QVariant::fromValue(mouse));
                        break;
                    }
                }
            }
        }
        else if(box == ui->comboBox_OS)
        {
            Soft* os = static_cast<Soft*>(comp);
            if(os->getTypeSoft() == "ОС")
            {
                foreach(QString platf, *(os->getConnectedPlatforms()))
                {
                    if(platf == ui->comboBox_Platform->currentText())
                    {
                        box->addItem(os->getName(), QVariant::fromValue(os));
                        break;
                    }
                }
            }
        }
        else if(box == ui->comboBox_Lic)
        {
            Soft* lic = static_cast<Soft*>(comp);
            if(lic->getTypeSoft() == "Лицензия")
            {
                foreach(QString platf, *(lic->getConnectedPlatforms()))
                {
                    if(platf == ui->comboBox_Platform->currentText())
                    {
                        box->addItem(lic->getName(), QVariant::fromValue(lic));
                        break;
                    }
                }
            }
        }
        else if(box == ui->comboBox_Soft1 || box == ui->comboBox_Soft2)
        {
            Soft* otherSoft = static_cast<Soft*>(comp);
            if(otherSoft->getTypeSoft() == "Другой софт")
            {
                foreach(QString platf, *(otherSoft->getConnectedPlatforms()))
                {
                    if(platf == ui->comboBox_Platform->currentText())
                    {
                        box->addItem(otherSoft->getName(), QVariant::fromValue(otherSoft));
                        break;
                    }
                }
            }
        }
        else if(box == ui->comboBox_Other1 || box == ui->comboBox_Other2 ||
                box == ui->comboBox_Other3 || box == ui->comboBox_Other4)
        {
            Others* others = static_cast<Others*>(comp);
            foreach(QString platf, *(others->getConnectedPlatforms()))
            {
                if(platf == ui->comboBox_Platform->currentText())
                {
                    box->addItem(others->getName(), QVariant::fromValue(others));
                    break;
                }
            }
        }
        else
        {
            foreach(QString platf, *(comp->getConnectedPlatforms()))
            {
                if(platf == ui->comboBox_Platform->currentText())
                {
                    box->addItem(comp->getName(), QVariant::fromValue(comp));
                    break;
                }
            }
        }
    }

    if(box->count() == 0)
        box->addItem("Комплектующие отсутствуют");
}

void ConfiguratorWidget::refreshPrice(double* curPrice, QComboBox* curItem, QSpinBox* quantity)
{
    QString itemText = curItem->currentText();
    if(itemText == "---")
    {
        *curPrice = 0;
        quantity->setMinimum(0);
        clearSpinbox(quantity);
        calculate_lineEdit_price_All();
        emit configurationChanged();
        return;
    }

    int quant;
    if(quantity != NULL)
        quant = quantity->value();
    else
        quant = 1;

    if(quant == 0)
    {
        quantity->setMinimum(1);
        quant = 1;
    }

    Component* ptrItem = curItem->itemData(curItem->currentIndex()).value<Component*>();
    if(ptrItem != NULL)
    {
        *curPrice = ptrItem->getPrice() * (double)quant;
    }
    else
    {
        *curPrice = 0;
    }

    calculate_lineEdit_price_All();
    emit configurationChanged();
}

void ConfiguratorWidget::refreshAllComponents()
{
    refreshDescription();

    ui->spinBox_RAM->blockSignals(true);
    ui->spinBox_RAM->setMinimum(1);
    ui->spinBox_RAM->setValue(1);
    ui->spinBox_RAM->blockSignals(false);

    ui->spinBox_HDD1->blockSignals(true);
    ui->spinBox_HDD1->setMinimum(1);
    ui->spinBox_HDD1->setValue(1);
    ui->spinBox_HDD1->blockSignals(false);

    clearSpinbox(ui->spinBox_HDD2);
    clearSpinbox(ui->spinBox_HDD3);
    clearSpinbox(ui->spinBox_HDD4);
    clearSpinbox(ui->spinBox_Video);
    clearSpinbox(ui->spinBox_DVD);
    clearSpinbox(ui->spinBox_KB);
    clearSpinbox(ui->spinBox_Mouse);
    clearSpinbox(ui->spinBox_Other1);
    clearSpinbox(ui->spinBox_Other2);
    clearSpinbox(ui->spinBox_Other3);
    clearSpinbox(ui->spinBox_Other4);

    ui->spinBox_quantity->blockSignals(true);
    ui->spinBox_quantity->setMinimum(1);
    ui->spinBox_quantity->setValue(1);
    ui->spinBox_quantity->blockSignals(false);

    //clearCombobox(ui->comboBox_PSU);
    //clearCombobox(ui->comboBox_RAM);
    //clearCombobox(ui->comboBox_HDD1);
    clearCombobox(ui->comboBox_HDD2);
    clearCombobox(ui->comboBox_HDD3);
    clearCombobox(ui->comboBox_HDD4);
    clearCombobox(ui->comboBox_Video);
    clearCombobox(ui->comboBox_DVD);
    //clearCombobox(ui->comboBox_KB);
    clearCombobox(ui->comboBox_Mouse);
    clearCombobox(ui->comboBox_Other1);
    clearCombobox(ui->comboBox_Other2);
    clearCombobox(ui->comboBox_Other3);
    clearCombobox(ui->comboBox_Other4);

    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    if(curPlatform == NULL)
    {
        return;
    }

    refreshCombobox(ui->comboBox_MB, 0, true);
    refreshCombobox(ui->comboBox_Case, 1, true);
    refreshCombobox(ui->comboBox_CPU, 2, true);
    refreshCombobox(ui->comboBox_Cooler, 3, true);

    if(curPlatform->getIntegrPsu())
    {
        ui->comboBox_PSU->setEnabled(false);
        clearCombobox(ui->comboBox_PSU);
        ui->comboBox_PSU->addItem(QString("Встроенный(%1 Вт)")
                                  .arg(curPlatform->getPsuPower()));
    }
    else
    {
        ui->comboBox_PSU->setEnabled(true);
        refreshCombobox(ui->comboBox_PSU, 4, true);
    }

    refreshCombobox(ui->comboBox_RAM, 5, true);
    refreshCombobox(ui->comboBox_HDD1, 6, true);
    refreshCombobox(ui->comboBox_HDD2, 6);
    refreshCombobox(ui->comboBox_HDD3, 6);
    refreshCombobox(ui->comboBox_HDD4, 6);
    refreshCombobox(ui->comboBox_Video, 7, !curPlatform->getIntegrVideo());
    refreshCombobox(ui->comboBox_DVD, 8);

    ui->checkBox_Reader->setChecked(false);
    if(curPlatform->getExt3_5() > 0)
        ui->checkBox_Reader->setEnabled(true);
    else
        ui->checkBox_Reader->setEnabled(false);

    refreshCombobox(ui->comboBox_KB, 9);
    refreshCombobox(ui->comboBox_Mouse, 9);
    refreshCombobox(ui->comboBox_OS, 10);
    refreshCombobox(ui->comboBox_Lic, 10);
    refreshCombobox(ui->comboBox_Soft1, 10);
    refreshCombobox(ui->comboBox_Soft2, 10);
    refreshCombobox(ui->comboBox_Other1, 11);
    refreshCombobox(ui->comboBox_Other2, 11);
    refreshCombobox(ui->comboBox_Other3, 11);
    refreshCombobox(ui->comboBox_Other4, 11);
}

void ConfiguratorWidget::refreshPlatformBox()
{
    clearCombobox(ui->comboBox_Platform);

    if(this->platformsList->isEmpty())
    {
        ui->comboBox_Platform->addItem("Платформы отсутствуют");
        ui->textBrowser_Desc->clear();
        clearCombobox(ui->comboBox_MB);
        clearCombobox(ui->comboBox_Case);
        clearCombobox(ui->comboBox_CPU);
        clearCombobox(ui->comboBox_Cooler);
        clearCombobox(ui->comboBox_PSU);
        clearCombobox(ui->comboBox_RAM);
        clearCombobox(ui->comboBox_HDD1);
        clearCombobox(ui->comboBox_HDD2);
        clearCombobox(ui->comboBox_HDD3);
        clearCombobox(ui->comboBox_HDD4);
        clearCombobox(ui->comboBox_Video);
        clearCombobox(ui->comboBox_DVD);
        ui->checkBox_Reader->setChecked(false);
        ui->checkBox_Reader->setEnabled(false);
        clearCombobox(ui->comboBox_KB);
        clearCombobox(ui->comboBox_Mouse);
        clearCombobox(ui->comboBox_OS);
        clearCombobox(ui->comboBox_Lic);
        clearCombobox(ui->comboBox_Soft1);
        clearCombobox(ui->comboBox_Soft2);
        clearCombobox(ui->comboBox_Other1);
        clearCombobox(ui->comboBox_Other2);
        clearCombobox(ui->comboBox_Other3);
        clearCombobox(ui->comboBox_Other4);
        return;
    }

    foreach(Platform* platf ,*(this->platformsList))
    {
        ui->comboBox_Platform->addItem(platf->getName(), QVariant::fromValue(platf));
    }

    refreshAllComponents();
}

bool ConfiguratorWidget::eventFilter(QObject *obj, QEvent* event)
{
    if(event->type() == QEvent::Wheel)
    {
        /*if(obj->metaObject()->className() == QString("QComboBox"))
        {
            QComboBox* combo = static_cast<QComboBox*>(obj);
            combo->hidePopup();
        }*/

        //TOTO: свернуть комбобокс, когда указатель мыши на другом виджете

        this->event(event);
        return true;
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
}

void ConfiguratorWidget::saveOtherSettings()
{
    otherSettings->setValue("comboBox_Platform", ui->comboBox_Platform->currentIndex());
    otherSettings->setValue("comboBox_MB", ui->comboBox_MB->currentIndex());
    otherSettings->setValue("comboBox_Case", ui->comboBox_Case->currentIndex());
    otherSettings->setValue("comboBox_CPU", ui->comboBox_CPU->currentIndex());
    otherSettings->setValue("comboBox_Cooler", ui->comboBox_Cooler->currentIndex());
    otherSettings->setValue("comboBox_PSU", ui->comboBox_PSU->currentIndex());
    otherSettings->setValue("comboBox_RAM", ui->comboBox_RAM->currentIndex());
    otherSettings->setValue("comboBox_HDD1", ui->comboBox_HDD1->currentIndex());
    otherSettings->setValue("comboBox_HDD2", ui->comboBox_HDD2->currentIndex());
    otherSettings->setValue("comboBox_HDD3", ui->comboBox_HDD3->currentIndex());
    otherSettings->setValue("comboBox_HDD4", ui->comboBox_HDD4->currentIndex());
    otherSettings->setValue("comboBox_Video", ui->comboBox_Video->currentIndex());
    otherSettings->setValue("comboBox_DVD", ui->comboBox_DVD->currentIndex());
    otherSettings->setValue("checkBox_Cardreader", ui->checkBox_Reader->isChecked());
    otherSettings->setValue("comboBox_KB", ui->comboBox_KB->currentIndex());
    otherSettings->setValue("comboBox_Mouse", ui->comboBox_Mouse->currentIndex());
    otherSettings->setValue("comboBox_OS", ui->comboBox_OS->currentIndex());
    otherSettings->setValue("comboBox_Lic", ui->comboBox_Lic->currentIndex());
    otherSettings->setValue("comboBox_Soft1", ui->comboBox_Soft1->currentIndex());
    otherSettings->setValue("comboBox_Soft2", ui->comboBox_Soft2->currentIndex());
    otherSettings->setValue("comboBox_Other1", ui->comboBox_Other1->currentIndex());
    otherSettings->setValue("comboBox_Other2", ui->comboBox_Other2->currentIndex());
    otherSettings->setValue("comboBox_Other3", ui->comboBox_Other3->currentIndex());
    otherSettings->setValue("comboBox_Other4", ui->comboBox_Other4->currentIndex());

    otherSettings->setValue("spinBox_RAM", ui->spinBox_RAM->value());
    otherSettings->setValue("spinBox_HDD1", ui->spinBox_HDD1->value());
    otherSettings->setValue("spinBox_HDD2", ui->spinBox_HDD2->value());
    otherSettings->setValue("spinBox_HDD3", ui->spinBox_HDD3->value());
    otherSettings->setValue("spinBox_HDD4", ui->spinBox_HDD4->value());
    otherSettings->setValue("spinBox_Video", ui->spinBox_Video->value());
    otherSettings->setValue("spinBox_DVD", ui->spinBox_DVD->value());
    otherSettings->setValue("spinBox_KB", ui->spinBox_KB->value());
    otherSettings->setValue("spinBox_Mouse", ui->spinBox_Mouse->value());
    otherSettings->setValue("spinBox_OS", ui->spinBox_OS->value());
    otherSettings->setValue("spinBox_Lic", ui->spinBox_Lic->value());
    otherSettings->setValue("spinBox_Soft1", ui->spinBox_Soft1->value());
    otherSettings->setValue("spinBox_Soft2", ui->spinBox_Soft2->value());
    otherSettings->setValue("spinBox_Other1", ui->spinBox_Other1->value());
    otherSettings->setValue("spinBox_Other2", ui->spinBox_Other2->value());
    otherSettings->setValue("spinBox_Other3", ui->spinBox_Other3->value());
    otherSettings->setValue("spinBox_Other4", ui->spinBox_Other4->value());
    otherSettings->setValue("spinBox_quantity", ui->spinBox_quantity->value());
}

void ConfiguratorWidget::loadOtherSettings()
{
    ui->comboBox_Platform->setCurrentIndex(otherSettings->value("comboBox_Platform", 0).toInt());
    ui->comboBox_MB->setCurrentIndex(otherSettings->value("comboBox_MB", 0).toInt());
    ui->comboBox_Case->setCurrentIndex(otherSettings->value("comboBox_Case", 0).toInt());
    ui->comboBox_CPU->setCurrentIndex(otherSettings->value("comboBox_CPU", 0).toInt());
    ui->comboBox_Cooler->setCurrentIndex(otherSettings->value("comboBox_Cooler", 0).toInt());
    ui->comboBox_PSU->setCurrentIndex(otherSettings->value("comboBox_PSU", 0).toInt());
    ui->comboBox_RAM->setCurrentIndex(otherSettings->value("comboBox_RAM", 0).toInt());
    ui->comboBox_HDD1->setCurrentIndex(otherSettings->value("comboBox_HDD1", 0).toInt());
    ui->comboBox_HDD2->setCurrentIndex(otherSettings->value("comboBox_HDD2", 0).toInt());
    ui->comboBox_HDD3->setCurrentIndex(otherSettings->value("comboBox_HDD3", 0).toInt());
    ui->comboBox_HDD4->setCurrentIndex(otherSettings->value("comboBox_HDD4", 0).toInt());
    ui->comboBox_Video->setCurrentIndex(otherSettings->value("comboBox_Video", 0).toInt());
    ui->comboBox_DVD->setCurrentIndex(otherSettings->value("comboBox_DVD", 0).toInt());
    ui->checkBox_Reader->setChecked(otherSettings->value("checkBox_Cardreader", "false").toBool());
    ui->comboBox_KB->setCurrentIndex(otherSettings->value("comboBox_KB", 0).toInt());
    ui->comboBox_Mouse->setCurrentIndex(otherSettings->value("comboBox_Mouse", 0).toInt());
    ui->comboBox_OS->setCurrentIndex(otherSettings->value("comboBox_OS", 0).toInt());
    ui->comboBox_Lic->setCurrentIndex(otherSettings->value("comboBox_Lic", 0).toInt());
    ui->comboBox_Soft1->setCurrentIndex(otherSettings->value("comboBox_Soft1", 0).toInt());
    ui->comboBox_Soft2->setCurrentIndex(otherSettings->value("comboBox_Soft2", 0).toInt());
    ui->comboBox_Other1->setCurrentIndex(otherSettings->value("comboBox_Other1", 0).toInt());
    ui->comboBox_Other2->setCurrentIndex(otherSettings->value("comboBox_Other2", 0).toInt());
    ui->comboBox_Other3->setCurrentIndex(otherSettings->value("comboBox_Other3", 0).toInt());
    ui->comboBox_Other4->setCurrentIndex(otherSettings->value("comboBox_Other4", 0).toInt());

    ui->spinBox_RAM->setValue(otherSettings->value("spinBox_RAM", 0).toInt());
    ui->spinBox_HDD1->setValue(otherSettings->value("spinBox_HDD1", 0).toInt());
    ui->spinBox_HDD2->setValue(otherSettings->value("spinBox_HDD2", 0).toInt());
    ui->spinBox_HDD3->setValue(otherSettings->value("spinBox_HDD3", 0).toInt());
    ui->spinBox_HDD4->setValue(otherSettings->value("spinBox_HDD4", 0).toInt());
    ui->spinBox_Video->setValue(otherSettings->value("spinBox_Video", 0).toInt());
    ui->spinBox_DVD->setValue(otherSettings->value("spinBox_DVD", 0).toInt());
    ui->spinBox_KB->setValue(otherSettings->value("spinBox_KB", 0).toInt());
    ui->spinBox_Mouse->setValue(otherSettings->value("spinBox_Mouse", 0).toInt());
    ui->spinBox_OS->setValue(otherSettings->value("spinBox_OS", 0).toInt());
    ui->spinBox_Lic->setValue(otherSettings->value("spinBox_Lic", 0).toInt());
    ui->spinBox_Soft1->setValue(otherSettings->value("spinBox_Soft1", 0).toInt());
    ui->spinBox_Soft2->setValue(otherSettings->value("spinBox_Soft2", 0).toInt());
    ui->spinBox_Other1->setValue(otherSettings->value("spinBox_Other1", 0).toInt());
    ui->spinBox_Other2->setValue(otherSettings->value("spinBox_Other2", 0).toInt());
    ui->spinBox_Other3->setValue(otherSettings->value("spinBox_Other3", 0).toInt());
    ui->spinBox_Other4->setValue(otherSettings->value("spinBox_Other4", 0).toInt());
    ui->spinBox_quantity->setValue(otherSettings->value("spinBox_quantity", 0).toInt());
}

void ConfiguratorWidget::on_comboBox_Platform_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    refreshAllComponents();
    emit configurationChanged();
}

void ConfiguratorWidget::on_comboBox_MB_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    //qDebug() << arg1;

    refreshPrice(&mbPrice, ui->comboBox_MB, NULL);
}

void ConfiguratorWidget::on_comboBox_Case_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    refreshPrice(&casePrice, ui->comboBox_Case, NULL);
}

void ConfiguratorWidget::on_comboBox_CPU_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    refreshPrice(&cpuPrice, ui->comboBox_CPU, NULL);
}

void ConfiguratorWidget::on_comboBox_Cooler_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    refreshPrice(&coolerPrice, ui->comboBox_Cooler, NULL);
}

void ConfiguratorWidget::on_comboBox_PSU_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkPSU())
    {
        //qDebug() << "true";
        PSUcurrentIndex = ui->comboBox_PSU->currentIndex();
        refreshPrice(&psuPrice, ui->comboBox_PSU, NULL);
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_PSU->blockSignals(true);
        ui->comboBox_PSU->setCurrentIndex(PSUcurrentIndex);
        ui->comboBox_PSU->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_RAM_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkRAM())
    {
        //qDebug() << "true";
        RAMcurrentIndex = ui->comboBox_RAM->currentIndex();
        RAMcurrentQuantity = ui->spinBox_RAM->value();
        refreshPrice(&ramPrice, ui->comboBox_RAM, ui->spinBox_RAM);
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_RAM->blockSignals(true);
        ui->spinBox_RAM->blockSignals(true);
        ui->comboBox_RAM->setCurrentIndex(RAMcurrentIndex);
        ui->spinBox_RAM->setValue(RAMcurrentQuantity);
        ui->comboBox_RAM->blockSignals(false);
        ui->spinBox_RAM->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_HDD1_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkHDDandDVD())
    {
        //qDebug() << "true";
        refreshPrice(&hdd1Price, ui->comboBox_HDD1, ui->spinBox_HDD1);
        HDD1currentIndex = ui->comboBox_HDD1->currentIndex();
        HDD1currentQuantity = ui->spinBox_HDD1->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_HDD1->blockSignals(true);
        ui->spinBox_HDD1->blockSignals(true);

        if(HDD1currentQuantity == 0)
        {
            ui->spinBox_HDD1->setMinimum(0);
        }
        ui->comboBox_HDD1->setCurrentIndex(HDD1currentIndex);
        ui->spinBox_HDD1->setValue(HDD1currentQuantity);

        ui->comboBox_HDD1->blockSignals(false);
        ui->spinBox_HDD1->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_HDD2_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkHDDandDVD())
    {
        //qDebug() << "true";
        refreshPrice(&hdd2Price, ui->comboBox_HDD2, ui->spinBox_HDD2);
        HDD2currentIndex = ui->comboBox_HDD2->currentIndex();
        HDD2currentQuantity = ui->spinBox_HDD2->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_HDD2->blockSignals(true);
        ui->spinBox_HDD2->blockSignals(true);

        if(HDD2currentQuantity == 0)
        {
            ui->spinBox_HDD2->setMinimum(0);
        }
        ui->comboBox_HDD2->setCurrentIndex(HDD2currentIndex);
        ui->spinBox_HDD2->setValue(HDD2currentQuantity);

        ui->comboBox_HDD2->blockSignals(false);
        ui->spinBox_HDD2->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_HDD3_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkHDDandDVD())
    {
        //qDebug() << "true";
        refreshPrice(&hdd3Price, ui->comboBox_HDD3, ui->spinBox_HDD3);
        HDD3currentIndex = ui->comboBox_HDD3->currentIndex();
        HDD3currentQuantity = ui->spinBox_HDD3->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_HDD3->blockSignals(true);
        ui->spinBox_HDD3->blockSignals(true);

        if(HDD3currentQuantity == 0)
        {
            ui->spinBox_HDD3->setMinimum(0);
        }
        ui->comboBox_HDD3->setCurrentIndex(HDD3currentIndex);
        ui->spinBox_HDD3->setValue(HDD3currentQuantity);

        ui->comboBox_HDD3->blockSignals(false);
        ui->spinBox_HDD3->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_HDD4_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkHDDandDVD())
    {
        //qDebug() << "true";
        refreshPrice(&hdd4Price, ui->comboBox_HDD4, ui->spinBox_HDD4);
        HDD4currentIndex = ui->comboBox_HDD4->currentIndex();
        HDD4currentQuantity = ui->spinBox_HDD4->value();        
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_HDD4->blockSignals(true);
        ui->spinBox_HDD4->blockSignals(true);

        if(HDD4currentQuantity == 0)
        {
            ui->spinBox_HDD4->setMinimum(0);
        }
        ui->comboBox_HDD4->setCurrentIndex(HDD4currentIndex);
        ui->spinBox_HDD4->setValue(HDD4currentQuantity);

        ui->comboBox_HDD4->blockSignals(false);
        ui->spinBox_HDD4->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_Video_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkVideo() && checkPSU())
    {
        //qDebug() << "true";
        refreshPrice(&videoPrice, ui->comboBox_Video, ui->spinBox_Video);
        VideoCurrentIndex = ui->comboBox_Video->currentIndex();
        VideoCurrentQuantity = ui->spinBox_Video->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_Video->blockSignals(true);
        ui->spinBox_Video->blockSignals(true);

        if(VideoCurrentQuantity == 0)
        {
            ui->spinBox_Video->setMinimum(0);
        }
        ui->comboBox_Video->setCurrentIndex(VideoCurrentIndex);
        ui->spinBox_Video->setValue(VideoCurrentQuantity);

        ui->comboBox_Video->blockSignals(false);
        ui->spinBox_Video->blockSignals(false);
    }

}

void ConfiguratorWidget::on_comboBox_DVD_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkHDDandDVD())
    {
        //qDebug() << "true";
        refreshPrice(&dvdPrice, ui->comboBox_DVD, ui->spinBox_DVD);
        DVDcurrentIndex = ui->comboBox_DVD->currentIndex();
        DVDcurrentQuantity = ui->spinBox_DVD->value();        
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_DVD->blockSignals(true);
        ui->spinBox_DVD->blockSignals(true);

        if(DVDcurrentQuantity == 0)
        {
            ui->spinBox_DVD->setMinimum(0);
        }
        ui->comboBox_DVD->setCurrentIndex(DVDcurrentIndex);
        ui->spinBox_DVD->setValue(DVDcurrentQuantity);

        ui->comboBox_DVD->blockSignals(false);
        ui->spinBox_DVD->blockSignals(false);
    }
}

void ConfiguratorWidget::on_checkBox_Reader_stateChanged(int arg1)
{
    if(arg1)
    {
        readerPrice = cardReaderPrice;
    }
    else
    {
        readerPrice = 0;
    }
    calculate_lineEdit_price_All();
    emit configurationChanged();
}

void ConfiguratorWidget::on_comboBox_KB_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkKBandMouse())
    {
        //qDebug() << "true";
        refreshPrice(&kbPrice, ui->comboBox_KB, ui->spinBox_KB);
        KBcurrentIndex = ui->comboBox_KB->currentIndex();
        KBcurrentQuantity = ui->spinBox_KB->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_KB->blockSignals(true);
        ui->spinBox_KB->blockSignals(true);

        if(KBcurrentQuantity == 0)
        {
            ui->spinBox_KB->setMinimum(0);
        }
        ui->comboBox_KB->setCurrentIndex(KBcurrentIndex);
        ui->spinBox_KB->setValue(KBcurrentQuantity);

        ui->comboBox_KB->blockSignals(false);
        ui->spinBox_KB->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_Mouse_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkKBandMouse())
    {
        //qDebug() << "true";
        refreshPrice(&mousePrice, ui->comboBox_Mouse, ui->spinBox_Mouse);
        MouseCurrentIndex = ui->comboBox_Mouse->currentIndex();
        MouseCurrentQuantity = ui->spinBox_Mouse->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_Mouse->blockSignals(true);
        ui->spinBox_Mouse->blockSignals(true);

        if(MouseCurrentQuantity == 0)
        {
            ui->spinBox_Mouse->setMinimum(0);
        }
        ui->comboBox_Mouse->setCurrentIndex(MouseCurrentIndex);
        ui->spinBox_Mouse->setValue(MouseCurrentQuantity);

        ui->comboBox_Mouse->blockSignals(false);
        ui->spinBox_Mouse->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_OS_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    refreshPrice(&osPrice, ui->comboBox_OS, ui->spinBox_OS);
}

void ConfiguratorWidget::on_comboBox_Lic_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    refreshPrice(&licPrice, ui->comboBox_Lic, ui->spinBox_Lic);
}

void ConfiguratorWidget::on_comboBox_Soft1_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    refreshPrice(&soft1Price, ui->comboBox_Soft1, ui->spinBox_Soft1);
}

void ConfiguratorWidget::on_comboBox_Soft2_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    refreshPrice(&soft2Price, ui->comboBox_Soft2, ui->spinBox_Soft2);
}

void ConfiguratorWidget::on_comboBox_Other1_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkOthers())
    {
        //qDebug() << "true";
        refreshPrice(&other1Price, ui->comboBox_Other1, ui->spinBox_Other1);
        Other1currentIndex = ui->comboBox_Other1->currentIndex();
        Other1currentQuantity = ui->spinBox_Other1->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_Other1->blockSignals(true);
        ui->spinBox_Other1->blockSignals(true);

        if(Other1currentQuantity == 0)
        {
            ui->spinBox_Other1->setMinimum(0);
        }
        ui->comboBox_Other1->setCurrentIndex(Other1currentIndex);
        ui->spinBox_Other1->setValue(Other1currentQuantity);

        ui->comboBox_Other1->blockSignals(false);
        ui->spinBox_Other1->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_Other2_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkOthers())
    {
        //qDebug() << "true";
        refreshPrice(&other2Price, ui->comboBox_Other2, ui->spinBox_Other2);
        Other2currentIndex = ui->comboBox_Other2->currentIndex();
        Other2currentQuantity = ui->spinBox_Other2->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_Other2->blockSignals(true);
        ui->spinBox_Other2->blockSignals(true);

        if(Other2currentQuantity == 0)
        {
            ui->spinBox_Other2->setMinimum(0);
        }
        ui->comboBox_Other2->setCurrentIndex(Other2currentIndex);
        ui->spinBox_Other2->setValue(Other2currentQuantity);

        ui->comboBox_Other2->blockSignals(false);
        ui->spinBox_Other2->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_Other3_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkOthers())
    {
        //qDebug() << "true";
        refreshPrice(&other3Price, ui->comboBox_Other3, ui->spinBox_Other3);
        Other3currentIndex = ui->comboBox_Other3->currentIndex();
        Other3currentQuantity = ui->spinBox_Other3->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_Other3->blockSignals(true);
        ui->spinBox_Other3->blockSignals(true);

        if(Other3currentQuantity == 0)
        {
            ui->spinBox_Other3->setMinimum(0);
        }
        ui->comboBox_Other3->setCurrentIndex(Other3currentIndex);
        ui->spinBox_Other3->setValue(Other3currentQuantity);

        ui->comboBox_Other3->blockSignals(false);
        ui->spinBox_Other3->blockSignals(false);
    }
}

void ConfiguratorWidget::on_comboBox_Other4_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(checkOthers())
    {
        //qDebug() << "true";
        refreshPrice(&other4Price, ui->comboBox_Other4, ui->spinBox_Other4);
        Other4currentIndex = ui->comboBox_Other4->currentIndex();
        Other4currentQuantity = ui->spinBox_Other4->value();
    }
    else
    {
        //qDebug() << "false";
        ui->comboBox_Other4->blockSignals(true);
        ui->spinBox_Other4->blockSignals(true);

        if(Other4currentQuantity == 0)
        {
            ui->spinBox_Other4->setMinimum(0);
        }
        ui->comboBox_Other4->setCurrentIndex(Other4currentIndex);
        ui->spinBox_Other4->setValue(Other4currentQuantity);

        ui->comboBox_Other4->blockSignals(false);
        ui->spinBox_Other4->blockSignals(false);
    }
}

void ConfiguratorWidget::calculate_lineEdit_price_All()
{
    double result = mbPrice + casePrice + cpuPrice + coolerPrice + psuPrice +
                    ramPrice + hdd1Price + hdd2Price + hdd3Price + hdd4Price +
                    videoPrice + dvdPrice + readerPrice + kbPrice + mousePrice +
                    osPrice + licPrice + soft1Price + soft2Price +
                    other1Price + other2Price + other3Price + other4Price;
    ui->lineEdit_price_All->setText(QString::number(result, 'f', 2));
}

void ConfiguratorWidget::on_lineEdit_price_All_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    double allPrice = ui->lineEdit_price_All->text().toDouble();
    double result = allPrice * ui->spinBox_quantity->value();
    ui->lineEdit_price_Total->setText(QString::number(result, 'f', 2));

    emit configurationChanged();
}

bool ConfiguratorWidget::checkPSU()
{
    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    PSU* curPSU = ui->comboBox_PSU->currentData().value<PSU*>();
    Video* curVideo = ui->comboBox_Video->currentData().value<Video*>();
    int quantityVideo = ui->spinBox_Video->value();
    int psuPower;
    int videoPower;

    if(curVideo == NULL || curPlatform == NULL)
        return true;

    if(curPlatform->getIntegrPsu())
        psuPower = curPlatform->getPsuPower();
    else
    {
        if(curPSU == NULL)
            return true;
        else
            psuPower = curPSU->getPower();
    }

    if(quantityVideo > 1)
    {
        videoPower = 750;
        if(psuPower < videoPower)
        {
            QString msgText = "Недостаточная мощность блока питания.";
            msgText.append(" Для установки нескольких видеокарт необходим");
            msgText.append(" блок питания мощностью не менее %1 Вт.");

            QMessageBox::warning(this, "Недостаточно мощности",
                                 msgText.arg(videoPower), QMessageBox::Ok);
            return false;
        }
    }
    else
    {
        if(curVideo->getPowerRank() == "Третий")
        {
            videoPower = 650;
            if(psuPower < videoPower)
            {
                QString msgText = "Недостаточная мощность блока питания.";
                msgText.append(" Для видеокарты %1 необходим блок питания");
                msgText.append(" мощностью не менее %2 Вт.");

                QMessageBox::warning(this, "Недостаточно мощности",
                                     msgText.arg(curVideo->getName()).arg(videoPower),
                                     QMessageBox::Ok);
                return false;
            }
        }
        else if(curVideo->getPowerRank() == "Второй")
        {
            videoPower = 500;
            if(psuPower < videoPower)
            {
                QString msgText = "Недостаточная мощность блока питания.";
                msgText.append(" Для видеокарты %1 необходим блок питания");
                msgText.append(" мощностью не менее %2 Вт.");

                QMessageBox::warning(this, "Недостаточно мощности",
                                     msgText.arg(curVideo->getName()).arg(videoPower),
                                     QMessageBox::Ok);
                return false;
            }
        }
    }

    return true;
}

bool ConfiguratorWidget::checkRAM()
{
    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    RAM* curRam = ui->comboBox_RAM->currentData().value<RAM*>();
    int quantityRam = ui->spinBox_RAM->value();

    if(curRam == NULL || curPlatform == NULL)
        return true;

    if(curPlatform->getRam() < (curRam->getCapacity() * quantityRam))
    {
        QString msgText = "Выбранная платформа не поддерживает такой объем памяти.";
        msgText.append(" Платформа %1 максимально поддерживает %2 Гб.");

        QMessageBox::warning(this, "Слишком большой объем памяти",
                             msgText.arg(curPlatform->getName()).arg(curPlatform->getRam()),
                             QMessageBox::Ok);
        return false;
    }

    if(curPlatform->getDimm() < (curRam->getCountOfModules() * quantityRam))
    {
        QString msgText = "Недостаточно свободных слотов DIMM.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");

        QMessageBox::warning(this, "Недостаточно слотов DIMM",
                             msgText.arg(curPlatform->getName()).arg(curPlatform->getDimm()),
                             QMessageBox::Ok);
        return false;
    }

    return true;
}

bool ConfiguratorWidget::checkHDDandDVD()
{
    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    int quantityHDD = ui->spinBox_HDD1->value() + ui->spinBox_HDD2->value() +
                      ui->spinBox_HDD3->value() + ui->spinBox_HDD4->value();
    int quantityDVD = ui->spinBox_DVD->value();

    if(curPlatform == NULL)
        return true;

    if(curPlatform->getInt3_5() < quantityHDD)
    {
        QString msgText = "Недостаточно свободных внутренних отсеков 3,5.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");
        msgText.append(" Проверьте общее количество установленных HDD.");

        QMessageBox::warning(this, "Недостаточно внутренних отсеков 3,5",
                             msgText.arg(curPlatform->getName()).arg(curPlatform->getInt3_5()),
                             QMessageBox::Ok);
        return false;
    }

    if(curPlatform->getExt5_25() < quantityDVD)
    {
        QString msgText = "Недостаточно свободных внешних отсеков 5,25.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");
        msgText.append(" Проверьте общее количество установленных DVD.");

        QMessageBox::warning(this, "Недостаточно внешних отсеков 5,25",
                             msgText.arg(curPlatform->getName()).arg(curPlatform->getExt5_25()),
                             QMessageBox::Ok);
        return false;
    }

    if(curPlatform->getSata() < (quantityHDD + quantityDVD))
    {
        QString msgText = "Недостаточно свободных слотов SATA.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");
        msgText.append(" Проверьте общее количество установленных HDD и DVD.");

        QMessageBox::warning(this, "Недостаточно слотов SATA",
                             msgText.arg(curPlatform->getName()).arg(curPlatform->getSata()),
                             QMessageBox::Ok);
        return false;
    }

    return true;
}

bool ConfiguratorWidget::checkVideo()
{
    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    if(curPlatform == NULL)
        return true;

    Others* curOther1 = ui->comboBox_Other1->currentData().value<Others*>();
    Others* curOther2 = ui->comboBox_Other2->currentData().value<Others*>();
    Others* curOther3 = ui->comboBox_Other3->currentData().value<Others*>();
    Others* curOther4 = ui->comboBox_Other4->currentData().value<Others*>();

    int totalQuantityPCIe = ui->spinBox_Video->value() + ui->spinBox_Other1->value() +
                            ui->spinBox_Other2->value() + ui->spinBox_Other3->value() +
                            ui->spinBox_Other4->value();

    int platformQuantityPCIe = curPlatform->getPcie1() + curPlatform->getPcie4() +
                               curPlatform->getPcie8() + curPlatform->getPcie16();

    if(platformQuantityPCIe < totalQuantityPCIe)
    {
        QString msgText = "Все слоты PCIe задействованы.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");

        QMessageBox::warning(this, "Все PCIe задействованы",
                             msgText.arg(curPlatform->getName()).arg(platformQuantityPCIe),
                             QMessageBox::Ok);
        return false;
    }

    int quantityPCIe_16 = ui->spinBox_Video->value();
    if(curOther1 != NULL && curOther1->getPcie() == "x16")
        quantityPCIe_16 += ui->spinBox_Other1->value();
    if(curOther2 != NULL && curOther2->getPcie() == "x16")
        quantityPCIe_16 += ui->spinBox_Other2->value();
    if(curOther3 != NULL && curOther3->getPcie() == "x16")
        quantityPCIe_16 += ui->spinBox_Other3->value();
    if(curOther4 != NULL && curOther4->getPcie() == "x16")
        quantityPCIe_16 += ui->spinBox_Other4->value();

    if(curPlatform->getPcie16() < quantityPCIe_16)
    {
        QString msgText = "Недостаточно свободных слотов PCIe x16.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");

        QMessageBox::warning(this, "Недостаточно слотов PCIe x16",
                             msgText.arg(curPlatform->getName()).arg(curPlatform->getPcie16()),
                             QMessageBox::Ok);
        return false;
    }

    return true;
}

bool ConfiguratorWidget::checkKBandMouse()
{
    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    if(curPlatform == NULL)
        return true;

    KbMouse* curKb = ui->comboBox_KB->currentData().value<KbMouse*>();
    KbMouse* curMouse = ui->comboBox_Mouse->currentData().value<KbMouse*>();
    int quantityPS2 = 0;
    int quantityUSB = 0;

    if(curKb != NULL)
    {
        if(curKb->getConnector() == "PS/2")
            quantityPS2 += ui->spinBox_KB->value();
        else
            quantityUSB += ui->spinBox_KB->value();
    }

    if(curMouse != NULL)
    {
        if(curMouse->getConnector() == "PS/2")
            quantityPS2 += ui->spinBox_Mouse->value();
        else
            quantityUSB += ui->spinBox_Mouse->value();
    }

    if(curPlatform->getPs2() < quantityPS2)
    {
        QString msgText = "Недостаточно свободных портов PS/2.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");

        QMessageBox::warning(this, "Недостаточно портов PS/2",
                             msgText.arg(curPlatform->getName()).arg(curPlatform->getPs2()),
                             QMessageBox::Ok);
        return false;
    }

    if(curPlatform->getUsb2() + curPlatform->getUsb3() < quantityUSB)
    {
        QString msgText = "Недостаточно свободных портов USB.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");

        QMessageBox::warning(this, "Недостаточно портов USB",
                             msgText.arg(curPlatform->getName()).arg(curPlatform->getUsb2() +
                                                                     curPlatform->getUsb3()),
                             QMessageBox::Ok);
        return false;
    }

    return true;
}

bool ConfiguratorWidget::checkOthers()
{
    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    if(curPlatform == NULL)
        return true;

    int totalQuantityPCIe = ui->spinBox_Video->value() + ui->spinBox_Other1->value() +
                            ui->spinBox_Other2->value() + ui->spinBox_Other3->value() +
                            ui->spinBox_Other4->value();

    int platformQuantityPCIe = curPlatform->getPcie1() + curPlatform->getPcie4() +
                               curPlatform->getPcie8() + curPlatform->getPcie16();

    if(platformQuantityPCIe < totalQuantityPCIe)
    {
        QString msgText = "Все слоты PCIe задействованы.";
        msgText.append(" Платформа %1 максимально поддерживает %2 шт.");

        QMessageBox::warning(this, "Все PCIe задействованы",
                             msgText.arg(curPlatform->getName()).arg(platformQuantityPCIe),
                             QMessageBox::Ok);
        return false;
    }

    int quantityPCIe_1 = 0;
    int quantityPCIe_4 = 0;
    int quantityPCIe_8 = 0;
    int quantityPCIe_16 = 0;
    Others* curOther1 = ui->comboBox_Other1->currentData().value<Others*>();
    Others* curOther2 = ui->comboBox_Other2->currentData().value<Others*>();
    Others* curOther3 = ui->comboBox_Other3->currentData().value<Others*>();
    Others* curOther4 = ui->comboBox_Other4->currentData().value<Others*>();
    QMultiMap<Others*, int> mapOthers;
    if(curOther1 != NULL)
        mapOthers.insert(curOther1, ui->spinBox_Other1->value());
    if(curOther2 != NULL)
        mapOthers.insert(curOther2, ui->spinBox_Other2->value());
    if(curOther3 != NULL)
        mapOthers.insert(curOther3, ui->spinBox_Other3->value());
    if(curOther4 != NULL)
        mapOthers.insert(curOther4, ui->spinBox_Other4->value());

    QMapIterator<Others*, int> i(mapOthers);
    while(i.hasNext())
    {
        i.next();
        if(i.key()->getPcie() == "x1")
            quantityPCIe_1 += i.value();
        else if(i.key()->getPcie() == "x4")
            quantityPCIe_4 += i.value();
        else if(i.key()->getPcie() == "x8")
            quantityPCIe_8 += i.value();
        else if(i.key()->getPcie() == "x16")
            quantityPCIe_16 += i.value();
    }

    quantityPCIe_16 += ui->spinBox_Video->value();

    if(quantityPCIe_1 > curPlatform->getPcie1())
    {
        quantityPCIe_4 += quantityPCIe_1 - curPlatform->getPcie1();
        quantityPCIe_1 = curPlatform->getPcie1();
    }
    if(quantityPCIe_4 > curPlatform->getPcie4())
    {
        quantityPCIe_8 += quantityPCIe_4 - curPlatform->getPcie4();
        quantityPCIe_4 = curPlatform->getPcie4();
    }
    if(quantityPCIe_8 > curPlatform->getPcie8())
    {
        quantityPCIe_16 += quantityPCIe_8 - curPlatform->getPcie8();
        quantityPCIe_8 = curPlatform->getPcie8();
    }
    if(quantityPCIe_16 > curPlatform->getPcie16())
    {
        QString msgText = "Недостаточно свободных слотов PCIe.";
        msgText.append(" Платформа %1 максимально поддерживает:\n");
        msgText.append(" x1\t%2 шт,\n x4\t%3 шт,\n x8\t%4 шт,\n x16\t%5 шт.\n");
        msgText.append("Вы пытаетесь установить:\n");
        msgText.append(" x1\t%6 шт,\n x4\t%7 шт,\n x8\t%8 шт,\n x16\t%9 шт.");

        QMessageBox::warning(this, "Недостаточно слотов PCIe",
                             msgText.arg(curPlatform->getName())
                                    .arg(curPlatform->getPcie1())
                                    .arg(curPlatform->getPcie4())
                                    .arg(curPlatform->getPcie8())
                                    .arg(curPlatform->getPcie16())
                                    .arg(quantityPCIe_1)
                                    .arg(quantityPCIe_4)
                                    .arg(quantityPCIe_8)
                                    .arg(quantityPCIe_16)
                             , QMessageBox::Ok);
        return false;
    }

    //qDebug() << "x1 - " << quantityPCIe_1;
    //qDebug() << "x4 - " << quantityPCIe_4;
    //qDebug() << "x8 - " << quantityPCIe_8;
    //qDebug() << "x16 - " << quantityPCIe_16;

    return true;
}

void ConfiguratorWidget::on_pushButton_offer_clicked()
{
    QDir dir = QDir::current();
    if(dir.exists("Offers"))
        dir.cd("Offers");
    else
    {
        if(dir.mkdir("Offers"))
            dir.cd("Offers");
        else
            qDebug() << "Невозможно создать директорию Offers";
    }

    QString curDate = QDate::currentDate().toString("dd-MM-yy");
    QString organization = organizationName;
    organization.replace(" ", "-");
    QString account = accountName;
    account.replace(" ", "-");
    QString offer;

    if(ui->radioButton_txt->isChecked())
        offer = QFileDialog::getSaveFileName(this, "Сохранение запроса",
                                             dir.filePath(curDate + "_" + organization + "_" +
                                                          account + "_Запрос" +
                                                          QString::number(offerNumber) + ".txt"),
                                                          "Text files (*.txt)");
    else
        offer = QFileDialog::getSaveFileName(this, "Сохранение запроса",
                                             dir.filePath(curDate + "_" + organization + "_" +
                                                          account + "_Запрос" +
                                                          QString::number(offerNumber) + ".doc"),
                                                          "Text files (*.doc)");

    if(!offer.isEmpty())
    {
        if(ui->radioButton_txt->isChecked())
            saveOfferToTxt(offer);
        else
            saveOfferToDoc(offer);
    }
    else
        qDebug() << "имя файла не выбрано";
}

QString ConfiguratorWidget::printComponent(QString compName, QComboBox *combobox, QSpinBox *spinbox)
{
    int quantity = 0;
    if(spinbox == NULL)
        quantity = 1;
    else
        quantity = spinbox->value();

    return compName.leftJustified(15, ' ') + combobox->currentText().leftJustified(50, '.', true) +
            QString(" ") + QString::number(quantity) + QString(" шт.");
}

void ConfiguratorWidget::printOptionalComponent(QTextStream &stream, QString compName,
                                                QComboBox *combobox, QSpinBox *spinbox)
{
    if(combobox->currentText() != "---")
    {
        stream << printComponent(compName, combobox, spinbox) << endl;
    }
}

void ConfiguratorWidget::saveOfferToTxt(QString fileName)
{
    QFile file(fileName);

    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    if(curPlatform == NULL)
    {
        qDebug() << "Платформа отсутствует";
        return;
    }

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        QString curDate = QDate::currentDate().toString("dd.MM.yy");

        stream << endl << qSetFieldWidth(71) << center <<
                  QString("Запрос на коммерческое предложение №" + QString::number(offerNumber) +
                          " от " + curDate) << reset << endl << endl;

        stream << qSetFieldWidth(71) << center <<
                  ui->comboBox_Platform->currentText() <<
                  reset << endl;

        stream << QString("").leftJustified(71, '-') << endl;

        stream << printComponent("Мат. плата:", ui->comboBox_MB) << endl;
        stream << printComponent("Корпус:", ui->comboBox_Case) << endl;
        stream << printComponent("Процессор:", ui->comboBox_CPU) << endl;
        stream << printComponent("Куллер:", ui->comboBox_Cooler) << endl;
        if(curPlatform->getIntegrPsu())
        {
            stream << QString("Блок питания:").leftJustified(15, ' ') << QString("Встроенный(") <<
                      QString::number(curPlatform->getPsuPower()).rightJustified(4, ' ') <<
                      QString(" Вт)").leftJustified(35, '.') << QString(" 1 шт.") << endl;
        }
        else
        {
            stream << printComponent("Блок питания:", ui->comboBox_PSU) << endl;
        }
        stream << printComponent("Опер. память:", ui->comboBox_RAM, ui->spinBox_RAM) << endl;
        stream << printComponent("Жесткий диск:", ui->comboBox_HDD1, ui->spinBox_HDD1) << endl;

        printOptionalComponent(stream, "Жесткий диск:", ui->comboBox_HDD2, ui->spinBox_HDD2);
        printOptionalComponent(stream, "Жесткий диск:", ui->comboBox_HDD3, ui->spinBox_HDD3);
        printOptionalComponent(stream, "Жесткий диск:", ui->comboBox_HDD4, ui->spinBox_HDD4);
        printOptionalComponent(stream, "Видеокарта:", ui->comboBox_Video, ui->spinBox_Video);
        printOptionalComponent(stream, "DVD привод:", ui->comboBox_DVD, ui->spinBox_DVD);
        if(ui->checkBox_Reader->isChecked())
        {
            stream << QString("Картридер:").leftJustified(15, ' ') <<
                      QString("Стандартный").leftJustified(50, '.') << QString(" 1 шт.") << endl;
        }
        printOptionalComponent(stream, "Клавиатура:", ui->comboBox_KB, ui->spinBox_KB);
        printOptionalComponent(stream, "Мышь:", ui->comboBox_Mouse, ui->spinBox_Mouse);
        printOptionalComponent(stream, "ОС:", ui->comboBox_OS, ui->spinBox_OS);
        printOptionalComponent(stream, "Лицензия:", ui->comboBox_Lic, ui->spinBox_Lic);
        printOptionalComponent(stream, "Доп. ПО:", ui->comboBox_Soft1, ui->spinBox_Soft1);
        printOptionalComponent(stream, "Доп. ПО:", ui->comboBox_Soft2, ui->spinBox_Soft2);
        printOptionalComponent(stream, "Дополнительно:", ui->comboBox_Other1, ui->spinBox_Other1);
        printOptionalComponent(stream, "Дополнительно:", ui->comboBox_Other2, ui->spinBox_Other2);
        printOptionalComponent(stream, "Дополнительно:", ui->comboBox_Other3, ui->spinBox_Other3);
        printOptionalComponent(stream, "Дополнительно:", ui->comboBox_Other4, ui->spinBox_Other4);

        stream << QString("").leftJustified(71, '-') << endl;

        double pricePerOne = ui->lineEdit_price_All->text().toDouble();
        double ndsPerOne = pricePerOne * (1 - 1 / 1.18);

        double pricePerAll = ui->lineEdit_price_Total->text().toDouble();
        double ndsPerAll = pricePerAll * (1 - 1 / 1.18);

        stream << QString("Количество: ").rightJustified(66, ' ') <<
                  ui->spinBox_quantity->value() << QString(" шт.") << endl << endl;

        stream << QString("Цена за единицу: ") << ui->lineEdit_price_All->text() <<
                  QString(" USD(в том числе НДС: ") <<
                  QString::number(ndsPerOne, 'f', 2) << QString(" USD).") << endl;

        stream << QString("Итоговая стоимость: ") << ui->lineEdit_price_Total->text() <<
                  QString(" USD(в том числе НДС: ") <<
                  QString::number(ndsPerAll, 'f', 2) << QString(" USD).");

        if(stream.status() != QTextStream::Ok)
            qDebug() << "Ошибка записи файла";
        else
        {
            ++offerNumber;
            qDebug() << "КП сохранено(.txt)";
        }
    }
    else
        qDebug() << "Ошибка открытия файла при записи: " << file.errorString();

    file.close();
}

QString ConfiguratorWidget::getComponentForDoc(QComboBox *combobox, QSpinBox *spinbox)
{
    int quantity = 0;
    if(spinbox == NULL)
        quantity = 1;
    else
        quantity = spinbox->value();

    return QString("\r\n%1 - %2 шт.").arg(combobox->currentText()).arg(QString::number(quantity));
}

QString ConfiguratorWidget::getOptionalComponentForDoc(QComboBox *combobox, QSpinBox *spinbox)
{
    QString result;
    if(combobox->currentText() != "---")
    {
        result = getComponentForDoc(combobox, spinbox);
    }
    return result;
}

QString ConfiguratorWidget::getAllComponentsForDoc()
{
    Platform* curPlatform = ui->comboBox_Platform->currentData().value<Platform*>();
    if(curPlatform == NULL)
    {
        qDebug() << "Платформа отсутствует";
        return "";
    }

    QString result = QString("%1 - 1 шт.").arg(ui->comboBox_MB->currentText());

    result.append(getComponentForDoc(ui->comboBox_Case));
    result.append(getComponentForDoc(ui->comboBox_CPU));
    result.append(getComponentForDoc(ui->comboBox_Cooler));
    if(curPlatform->getIntegrPsu())
    {
        result.append(QString("\r\nВстроенный БП(%1 Вт) - 1 шт.")
                      .arg(QString::number(curPlatform->getPsuPower())));
    }
    else
    {
        result.append(getComponentForDoc(ui->comboBox_PSU));
    }
    result.append(getComponentForDoc(ui->comboBox_RAM, ui->spinBox_RAM));
    result.append(getComponentForDoc(ui->comboBox_HDD1, ui->spinBox_HDD1));

    result.append(getOptionalComponentForDoc(ui->comboBox_HDD2, ui->spinBox_HDD2));
    result.append(getOptionalComponentForDoc(ui->comboBox_HDD3, ui->spinBox_HDD3));
    result.append(getOptionalComponentForDoc(ui->comboBox_HDD4, ui->spinBox_HDD4));
    result.append(getOptionalComponentForDoc(ui->comboBox_Video, ui->spinBox_Video));
    result.append(getOptionalComponentForDoc(ui->comboBox_DVD, ui->spinBox_DVD));
    if(ui->checkBox_Reader->isChecked())
    {
        result.append("\r\nСтандартный картридер - 1 шт.");
    }
    result.append(getOptionalComponentForDoc(ui->comboBox_KB, ui->spinBox_KB));
    result.append(getOptionalComponentForDoc(ui->comboBox_Mouse, ui->spinBox_Mouse));
    result.append(getOptionalComponentForDoc(ui->comboBox_OS, ui->spinBox_OS));
    result.append(getOptionalComponentForDoc(ui->comboBox_Lic, ui->spinBox_Lic));
    result.append(getOptionalComponentForDoc(ui->comboBox_Soft1, ui->spinBox_Soft1));
    result.append(getOptionalComponentForDoc(ui->comboBox_Soft2, ui->spinBox_Soft2));
    result.append(getOptionalComponentForDoc(ui->comboBox_Other1, ui->spinBox_Other1));
    result.append(getOptionalComponentForDoc(ui->comboBox_Other2, ui->spinBox_Other2));
    result.append(getOptionalComponentForDoc(ui->comboBox_Other3, ui->spinBox_Other3));
    result.append(getOptionalComponentForDoc(ui->comboBox_Other4, ui->spinBox_Other4));
    return result;
}

void ConfiguratorWidget::saveOfferToDoc(QString fileName)
{
    //текущая дата
    QString curDate = QDate::currentDate().toString("dd.MM.yy");

    //расчет НДС
    double pricePerOne = ui->lineEdit_price_All->text().toDouble();
    double ndsPerOne = pricePerOne * (1 - 1 / 1.18);

    double pricePerAll = ui->lineEdit_price_Total->text().toDouble();
    double ndsPerAll = pricePerAll * (1 - 1 / 1.18);

    //инициализация MS Word
    QAxObject* wordApplication = new QAxObject ("Word.Application", this);
    wordApplication->setProperty("DisplayAlerts", "0");
    wordApplication->setProperty("Visible", false);

    //создание пустого файла
    QAxObject* wordDocuments = wordApplication->querySubObject( "Documents()" );
    QAxObject* newDocument = wordDocuments->querySubObject("Add()");

    //активация созданного документа
    QAxObject* activeDocument = wordApplication->querySubObject("ActiveDocument()");

    //выделение
    QAxObject* selection = wordApplication->querySubObject("Selection()");

    //форматирование текста параграфов
    QAxObject* paragraphFormat = selection->querySubObject("ParagraphFormat()");
    QAxObject* font = selection->querySubObject("Font()");

    //заголовок
    selection->dynamicCall("TypeParagraph()");
    paragraphFormat->dynamicCall("SetAlignment(WdParagraphAlignment)", 1);
    font->dynamicCall("SetName", "Times New Roman");
    font->dynamicCall("SetSize", 14);
    font->dynamicCall("SetBold(int)", 1);
    selection->dynamicCall("TypeText(Text)",
                           QString("Запрос на коммерческое предложение №" +
                                   QString::number(offerNumber) + " от " + curDate));

    selection->dynamicCall("TypeParagraph()");

    //название платформы
    selection->dynamicCall("TypeParagraph()");
    paragraphFormat->dynamicCall("SetAlignment(WdParagraphAlignment)", 0);
    font->dynamicCall("SetSize", 12);
    selection->dynamicCall("TypeText(Text)", QString(ui->comboBox_Platform->currentText()) + ": ");

    //компоненты
    selection->dynamicCall("TypeParagraph()");
    font->dynamicCall("SetBold(int)", 0);
    selection->dynamicCall("TypeText(Text)", getAllComponentsForDoc());

    //количество
    selection->dynamicCall("TypeParagraph()");
    font->dynamicCall("SetBold(int)", 1);
    selection->dynamicCall("TypeText(Text)",
                           QString("Количество: "+
                                   QString::number(ui->spinBox_quantity->value())+" шт."));

    selection->dynamicCall("TypeParagraph()");

    //цена за единицу
    selection->dynamicCall("TypeParagraph()");
    selection->dynamicCall("TypeText(Text)", QString("Цена за единицу: " +
                           ui->lineEdit_price_All->text() + " USD(в том числе НДС: " +
                           QString::number(ndsPerOne, 'f', 2) + " USD)."));

    //итоговая стоимость
    selection->dynamicCall("TypeParagraph()");
    selection->dynamicCall("TypeText(Text)", QString("Итоговая стоимость: " +
                           ui->lineEdit_price_Total->text() + " USD(в том числе НДС: " +
                           QString::number(ndsPerAll, 'f', 2) + " USD)."));

    //сохранение файла
    activeDocument->dynamicCall("SaveAs(const QVariant&, const QVariant&)",
                                QVariant(fileName), QVariant(0));
    ++offerNumber;
    qDebug() << "КП сохранено(.doc)";

    //удаление объектов
    font->clear();
    delete font;

    paragraphFormat->clear();
    delete paragraphFormat;

    selection->clear();
    delete selection;

    activeDocument->clear();
    delete activeDocument;

    newDocument->clear();
    delete newDocument;

    wordDocuments->clear();
    delete wordDocuments;

    wordApplication->dynamicCall( "Quit()" );
    delete wordApplication;
}
