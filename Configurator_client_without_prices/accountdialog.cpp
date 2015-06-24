#include "accountdialog.h"
#include "ui_accountdialog.h"

AccountDialog::AccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
    this->setFixedSize(460, 85);
    this->setWindowTitle("Введите регистрационные данные");
    ui->pushButton_Cancel->setEnabled(false);
}

AccountDialog::AccountDialog(QString organization, QString account, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
    this->setFixedSize(460, 85);
    this->setWindowTitle("Редактирование регистрационных данных");

    ui->lineEdit_Organization->setText(organization);
    ui->lineEdit_Name->setText(account);
}

AccountDialog::~AccountDialog()
{
    delete ui;
}

void AccountDialog::on_pushButton_Ok_clicked()
{
    if(ui->lineEdit_Organization->text() != "" && ui->lineEdit_Name->text() != "")
    {
        emit sendAccountData(ui->lineEdit_Organization->text(), ui->lineEdit_Name->text());
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "Не все поля заполнены",
                             "Заполните все поля.", QMessageBox::Ok);
        return;
    }
}

void AccountDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}
