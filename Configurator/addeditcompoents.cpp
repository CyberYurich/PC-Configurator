#include "addeditcompoents.h"
#include "ui_addeditcompoents.h"

addEditCompoents::addEditCompoents(ComponentType type, QList<Component *> listForCheck,
                                   QWidget *parent) :
    QDialog(parent), ui(new Ui::addEditCompoents)
{
    ui->setupUi(this);
    //this->setAttribute(Qt::WA_DeleteOnClose, true); - для динамически созданного диалога
    this->setWindowTitle("Добавление новой комплектующей");
    this->type = type;
    this->listForCheck = listForCheck;

    switch (this->type)
    {
    case COMPONENT_PSU:
        {
            QLabel* lbl = new QLabel("Мощность:");
            QHBoxLayout* layout = new QHBoxLayout;
            line = new QLineEdit;
            line->setMaximumWidth(58);
            layout->addWidget(lbl);
            layout->addWidget(line);
            layout->addStretch();
            ui->verticalLayout_forAdd->addLayout(layout);
            break;
        }
    case COMPONENT_RAM:
        {
            QLabel* lbl1 = new QLabel("Количество модулей:");
            QLabel* lbl2 = new QLabel("Общий объем, Гб:");
            QHBoxLayout* layoutLeft = new QHBoxLayout;
            QHBoxLayout* layoutRight = new QHBoxLayout;
            QHBoxLayout* layoutMain = new QHBoxLayout;
            spin1 = new QSpinBox;
            spin2 = new QSpinBox;
            layoutLeft->addWidget(lbl1);
            layoutLeft->addWidget(spin1);
            layoutRight->addWidget(lbl2);
            layoutRight->addWidget(spin2);
            layoutMain->addLayout(layoutLeft);
            layoutMain->addLayout(layoutRight);
            layoutMain->addStretch();
            ui->verticalLayout_forAdd->addLayout(layoutMain);
            break;
        }
    case COMPONENT_VIDEO:
        {
            QLabel* lbl = new QLabel("Ранг энергопотребления:");
            QHBoxLayout* layout = new QHBoxLayout;
            combo1 = new QComboBox;
            combo1->addItem("Первый");
            combo1->addItem("Второй");
            combo1->addItem("Третий");
            layout->addWidget(lbl);
            layout->addWidget(combo1);
            layout->addStretch();
            ui->verticalLayout_forAdd->addLayout(layout);
            break;
        }
    case COMPONENT_KB_MOUSE:
        {
            QLabel* lbl1 = new QLabel("Тип:");
            QLabel* lbl2 = new QLabel("PS/2 или USB:");
            QHBoxLayout* layoutLeft = new QHBoxLayout;
            QHBoxLayout* layoutRight = new QHBoxLayout;
            QHBoxLayout* layoutMain = new QHBoxLayout;
            combo1 = new QComboBox;
            combo2 = new QComboBox;
            combo1->addItem("Клавиатура");
            combo1->addItem("Мышь");
            combo2->addItem("PS/2");
            combo2->addItem("USB");
            layoutLeft->addWidget(lbl1);
            layoutLeft->addWidget(combo1);
            layoutRight->addWidget(lbl2);
            layoutRight->addWidget(combo2);
            layoutMain->addLayout(layoutLeft);
            layoutMain->addLayout(layoutRight);
            layoutMain->addStretch();
            ui->verticalLayout_forAdd->addLayout(layoutMain);
            break;
        }
    case COMPONENT_SOFT:
        {
            QLabel* lbl = new QLabel("Тип:");
            QHBoxLayout* layout = new QHBoxLayout;
            combo1 = new QComboBox;
            combo1->addItem("ОС");
            combo1->addItem("Лицензия");
            combo1->addItem("Другой софт");
            layout->addWidget(lbl);
            layout->addWidget(combo1);
            layout->addStretch();
            ui->verticalLayout_forAdd->addLayout(layout);
            break;
        }
    case COMPONENT_OTHERS:
        {
            QLabel* lbl = new QLabel("Размер PCIe:");
            QHBoxLayout* layout = new QHBoxLayout;
            combo1 = new QComboBox;
            combo1->addItem("x1");
            combo1->addItem("x4");
            combo1->addItem("x8");
            combo1->addItem("x16");
            layout->addWidget(lbl);
            layout->addWidget(combo1);
            layout->addStretch();
            ui->verticalLayout_forAdd->addLayout(layout);
            break;
        }
    default:
        break;
    }

    ui->pushButton_ok->setAutoDefault(false);
    ui->pushButton_Cancel->setAutoDefault(false);
}

addEditCompoents::~addEditCompoents()
{
    delete ui;
    qDebug() << "Вызов деструктора для окна создания компонента";
}

void addEditCompoents::on_pushButton_Cancel_clicked()
{
    this->close();
}

void addEditCompoents::on_pushButton_ok_clicked()
{
    QListIterator<Component*> i(listForCheck);
    while (i.hasNext())
    {
        if(ui->lineEdit_name->text() == i.next()->getName())
        {
            QMessageBox::warning(this, "Совпадение имен",
                                 "Комплектующая с таким именем уже существует.", QMessageBox::Ok);
            ui->lineEdit_name->setFocus();
            ui->lineEdit_name->selectAll();
            return;
        }
    }


    switch (type)
    {
    case COMPONENT_DEFAULT:
    {
        Component* comp = new Component(ui->lineEdit_name->text(),
                                        ui->doubleSpinBox_cost->value(),
                                        ui->doubleSpinBox_price->value(),
                                        ui->doubleSpinBox_margin->value());
        emit sendComponent(comp);
        break;
    }
    case COMPONENT_PSU:
    {
        Component* comp = new PSU(ui->lineEdit_name->text(),
                                  ui->doubleSpinBox_cost->value(),
                                  ui->doubleSpinBox_price->value(),
                                  ui->doubleSpinBox_margin->value(),
                                  line->text().toInt());
        emit sendComponent(comp);
        break;
    }
    case COMPONENT_RAM:
    {
        Component* comp = new RAM(ui->lineEdit_name->text(),
                                  ui->doubleSpinBox_cost->value(),
                                  ui->doubleSpinBox_price->value(),
                                  ui->doubleSpinBox_margin->value(),
                                  spin1->value(), spin2->value());
        emit sendComponent(comp);
        break;
    }
    case COMPONENT_VIDEO:
    {
        Component* comp = new Video(ui->lineEdit_name->text(),
                                    ui->doubleSpinBox_cost->value(),
                                    ui->doubleSpinBox_price->value(),
                                    ui->doubleSpinBox_margin->value(),
                                    combo1->currentText());
        emit sendComponent(comp);
        break;
    }
    case COMPONENT_KB_MOUSE:
    {
        Component* comp = new KbMouse(ui->lineEdit_name->text(),
                                      ui->doubleSpinBox_cost->value(),
                                      ui->doubleSpinBox_price->value(),
                                      ui->doubleSpinBox_margin->value(),
                                      combo1->currentText(), combo2->currentText());
        emit sendComponent(comp);
        break;
    }
    case COMPONENT_SOFT:
    {
        Component* comp = new Soft(ui->lineEdit_name->text(),
                                   ui->doubleSpinBox_cost->value(),
                                   ui->doubleSpinBox_price->value(),
                                   ui->doubleSpinBox_margin->value(),
                                   combo1->currentText());
        emit sendComponent(comp);
        break;
    }
    case COMPONENT_OTHERS:
    {
        Component* comp = new Others(ui->lineEdit_name->text(),
                                     ui->doubleSpinBox_cost->value(),
                                     ui->doubleSpinBox_price->value(),
                                     ui->doubleSpinBox_margin->value(),
                                     combo1->currentText());
        emit sendComponent(comp);
        break;
    }
    default:
        qDebug() << "ошибка определения типа комплектующей в диалоге addEditCompoents";
        break;
    }
    this->close();
}

void addEditCompoents::on_doubleSpinBox_cost_editingFinished()
{
    /*disconnect(ui->doubleSpinBox_price, SIGNAL(editingFinished()),
               this, SLOT(on_doubleSpinBox_price_editingFinished()));
    disconnect(ui->doubleSpinBox_margin, SIGNAL(editingFinished()),
               this, SLOT(on_doubleSpinBox_margin_editingFinished()));*/

    if(ui->doubleSpinBox_cost->value() < ui->doubleSpinBox_price->value())
    {
        double cost = ui->doubleSpinBox_cost->value();
        double price = ui->doubleSpinBox_price->value();
        double margin = ((price - cost) / price) * 100;
        ui->doubleSpinBox_margin->setValue(margin);
    }
    else
    {
        ui->doubleSpinBox_price->setValue(ui->doubleSpinBox_cost->value());
        ui->doubleSpinBox_margin->setValue(0.0);
    }

    /*connect(ui->doubleSpinBox_price, SIGNAL(editingFinished()),
            this, SLOT(on_doubleSpinBox_price_editingFinished()));
    connect(ui->doubleSpinBox_margin, SIGNAL(editingFinished()),
            this, SLOT(on_doubleSpinBox_margin_editingFinished()));*/
}

void addEditCompoents::on_doubleSpinBox_price_editingFinished()
{
    /*disconnect(ui->doubleSpinBox_cost, SIGNAL(editingFinished()),
               this, SLOT(on_doubleSpinBox_cost_editingFinished()));
    disconnect(ui->doubleSpinBox_margin, SIGNAL(editingFinished()),
               this, SLOT(on_doubleSpinBox_margin_editingFinished()));*/

    if(ui->doubleSpinBox_cost->value() < ui->doubleSpinBox_price->value())
    {
        double cost = ui->doubleSpinBox_cost->value();
        double price = ui->doubleSpinBox_price->value();
        double margin = ((price - cost) / price) * 100;
        ui->doubleSpinBox_margin->setValue(margin);
    }
    else
    {
        ui->doubleSpinBox_cost->setValue(ui->doubleSpinBox_price->value());
        ui->doubleSpinBox_margin->setValue(0.0);
    }

    /*connect(ui->doubleSpinBox_cost, SIGNAL(editingFinished()),
            this, SLOT(on_doubleSpinBox_cost_editingFinished()));
    connect(ui->doubleSpinBox_margin, SIGNAL(editingFinished()),
            this, SLOT(on_doubleSpinBox_margin_editingFinished()));*/
}

void addEditCompoents::on_doubleSpinBox_margin_editingFinished()
{
    /*disconnect(ui->doubleSpinBox_cost, SIGNAL(editingFinished()),
               this, SLOT(on_doubleSpinBox_cost_editingFinished()));
    disconnect(ui->doubleSpinBox_price, SIGNAL(editingFinished()),
               this, SLOT(on_doubleSpinBox_price_editingFinished()));*/

    double cost = ui->doubleSpinBox_cost->value();
    double margin = ui->doubleSpinBox_margin->value();
    double price = cost / (1.0 - (margin / 100.0));
    ui->doubleSpinBox_price->setValue(price);

    /*connect(ui->doubleSpinBox_cost, SIGNAL(editingFinished()),
            this, SLOT(on_doubleSpinBox_cost_editingFinished()));
    connect(ui->doubleSpinBox_price, SIGNAL(editingFinished()),
            this, SLOT(on_doubleSpinBox_price_editingFinished()));*/
}

