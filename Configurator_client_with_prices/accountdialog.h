#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AccountDialog;
}

class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = 0);
    explicit AccountDialog(QString organization, QString account, QWidget *parent = 0);
    ~AccountDialog();

signals:
    void sendAccountData(QString organization, QString account);

private slots:
    void on_pushButton_Ok_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::AccountDialog *ui;
};

#endif // ACCOUNTDIALOG_H
