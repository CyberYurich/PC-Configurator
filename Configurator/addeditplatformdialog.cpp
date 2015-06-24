#include "addeditplatformdialog.h"
#include "ui_addeditplatformdialog.h"

addEditPlatformDialog::addEditPlatformDialog(QList<Platform*> listForCheck, QWidget *parent) :
    QDialog(parent), ui(new Ui::addEditPlatformDialog)
{
    ui->setupUi(this);
    //this->setAttribute(Qt::WA_DeleteOnClose, true); - для динамически созданного диалога
    this->setFixedSize(704,507);
    this->setWindowTitle("Добавление новой платформы");
    this->isAdd = true;
    this->listForCheck = listForCheck;
}

addEditPlatformDialog::addEditPlatformDialog(QString name, QString description, QString chipset,
                                             int socket, QString sound, QString lan, short usb2,
                                             short usb3, short sata, short sata3, short dimm,
                                             short ram, bool integrVideo, bool vga, bool dvi,
                                             bool hdmi, short pcie1, short pcie4, short pcie8,
                                             short pcie16, short ps2, QString caseForm,
                                             short ext5_25, short ext3_5, short int3_5,
                                             bool integrPsu, int psuPower, Platform* forEdit,
                                             QWidget *parent):
    QDialog(parent),
    ui(new Ui::addEditPlatformDialog)
{
    ui->setupUi(this);
    //this->setAttribute(Qt::WA_DeleteOnClose, true); - for dynamic dialogs
    this->setFixedSize(704,507);
    this->setWindowTitle("Редактирование платформы");
    this->isAdd = false;
    ui->lineEdit_name->setText(name);
    ui->lineEdit_name->setEnabled(false);
    ui->textEdit_description->setText(description);
    ui->lineEdit_chipset->setText(chipset);
    ui->lineEdit_socket->setText(QString::number(socket));
    ui->lineEdit_sound->setText(sound);
    ui->lineEdit_lan->setText(lan);
    ui->spinBox_usb2->setValue((int)usb2);
    ui->spinBox_usb3->setValue((int)usb3);
    ui->spinBox_sata->setValue((int)sata);
    ui->spinBox_sata3->setValue((int)sata3);
    ui->spinBox_dimm->setValue((int)dimm);
    ui->spinBox_ram->setValue((int)ram);
    ui->comboBox_integrVideo->setCurrentText(integrVideo ? "Да" : "Нет");
    ui->comboBox_vga->setCurrentText(vga ? "Да" : "Нет");
    ui->comboBox_dvi->setCurrentText(dvi ? "Да" : "Нет");
    ui->comboBox_hdmi->setCurrentText(hdmi ? "Да" : "Нет");
    ui->spinBox_pcie1->setValue((int)pcie1);
    ui->spinBox_pcie4->setValue((int)pcie4);
    ui->spinBox_pcie8->setValue((int)pcie8);
    ui->spinBox_pcie16->setValue((int)pcie16);
    ui->spinBox_ps2->setValue((int)ps2);
    ui->lineEdit_caseForm->setText(caseForm);
    ui->spinBox_ext5_25->setValue((int)ext5_25);
    ui->spinBox_ext3_5->setValue((int)ext3_5);
    ui->spinBox_int3_5->setValue((int)int3_5);
    ui->comboBox_integrPsu->setCurrentText(integrPsu ? "Да" : "Нет");
    ui->lineEdit_psuPower->setText(QString::number(psuPower));
    this->platformForEdit = forEdit;
}

addEditPlatformDialog::~addEditPlatformDialog()
{
    delete ui;
    qDebug() << "Вызов деструктора для окна создания платформы";
}

void addEditPlatformDialog::on_lineEdit_name_textChanged(const QString &arg1)
{
    ui->pushButton_ok->setEnabled(!arg1.isEmpty());
}

void addEditPlatformDialog::on_pushButton_cancel_clicked()
{
    this->close();
}

void addEditPlatformDialog::on_pushButton_ok_clicked()
{
    QListIterator<Platform*> i(listForCheck);
    while (i.hasNext())
    {
        if(ui->lineEdit_name->text() == i.next()->getName())
        {
            QMessageBox::warning(this, "Совпадение имен",
                                 "Платформа с таким именем уже существует.", QMessageBox::Ok);
            ui->lineEdit_name->setFocus();
            ui->lineEdit_name->selectAll();
            return;
        }
    }

    if(this->isAdd)
    {
        Platform* platf = new Platform(ui->lineEdit_name->text(),
                                       ui->textEdit_description->toPlainText(),
                                       ui->lineEdit_chipset->text(),
                                       ui->lineEdit_socket->text().toInt(),
                                       ui->lineEdit_sound->text(),
                                       ui->lineEdit_lan->text(),
                                       ui->spinBox_usb2->value(),
                                       ui->spinBox_usb3->value(),
                                       ui->spinBox_sata->value(),
                                       ui->spinBox_sata3->value(),
                                       ui->spinBox_dimm->value(),
                                       ui->spinBox_ram->value(),
                                       ui->comboBox_integrVideo->currentText() == "Да" ? true : false,
                                       ui->comboBox_vga->currentText() == "Да" ? true : false,
                                       ui->comboBox_dvi->currentText() == "Да" ? true : false,
                                       ui->comboBox_hdmi->currentText() == "Да" ? true : false,
                                       ui->spinBox_pcie1->value(),
                                       ui->spinBox_pcie4->value(),
                                       ui->spinBox_pcie8->value(),
                                       ui->spinBox_pcie16->value(),
                                       ui->spinBox_ps2->value(),
                                       ui->lineEdit_caseForm->text(),
                                       ui->spinBox_ext5_25->value(),
                                       ui->spinBox_ext3_5->value(),
                                       ui->spinBox_int3_5->value(),
                                       ui->comboBox_integrPsu->currentText() == "Да" ? true : false,
                                       ui->lineEdit_psuPower->text().toInt());
        emit sendPlatform(platf);
        this->close();
    }
    else
    {
        platformForEdit->editPlatform(ui->textEdit_description->toPlainText(),
                                      ui->lineEdit_chipset->text(),
                                      ui->lineEdit_socket->text().toInt(),
                                      ui->lineEdit_sound->text(),
                                      ui->lineEdit_lan->text(),
                                      ui->spinBox_usb2->value(),
                                      ui->spinBox_usb3->value(),
                                      ui->spinBox_sata->value(),
                                      ui->spinBox_sata3->value(),
                                      ui->spinBox_dimm->value(),
                                      ui->spinBox_ram->value(),
                                      ui->comboBox_integrVideo->currentText() == "Да" ? true : false,
                                      ui->comboBox_vga->currentText() == "Да" ? true : false,
                                      ui->comboBox_dvi->currentText() == "Да" ? true : false,
                                      ui->comboBox_hdmi->currentText() == "Да" ? true : false,
                                      ui->spinBox_pcie1->value(),
                                      ui->spinBox_pcie4->value(),
                                      ui->spinBox_pcie8->value(),
                                      ui->spinBox_pcie16->value(),
                                      ui->spinBox_ps2->value(),
                                      ui->lineEdit_caseForm->text(),
                                      ui->spinBox_ext5_25->value(),
                                      ui->spinBox_ext3_5->value(),
                                      ui->spinBox_int3_5->value(),
                                      ui->comboBox_integrPsu->currentText() == "Да" ? true : false,
                                      ui->lineEdit_psuPower->text().toInt());
        emit refreshPlatforms();
        this->close();
    }
}

