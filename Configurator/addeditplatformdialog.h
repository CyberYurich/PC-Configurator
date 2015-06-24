#ifndef ADDEDITPLATFORMDIALOG_H
#define ADDEDITPLATFORMDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "platform.h"
#include "platformswidget.h"

namespace Ui {
class addEditPlatformDialog;
}

class addEditPlatformDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addEditPlatformDialog(QList<Platform*> listForCheck, QWidget *parent = 0);
    explicit addEditPlatformDialog(QString name, QString description, QString chipset, int socket,
                                   QString sound, QString lan, short usb2, short usb3, short sata,
                                   short sata3, short dimm, short ram, bool integrVideo, bool vga,
                                   bool dvi, bool hdmi, short pcie1, short pcie4, short pcie8,
                                   short pcie16, short ps2, QString caseForm, short ext5_25,
                                   short ext3_5,short int3_5, bool integrPsu, int psuPower,
                                   Platform* forEdit, QWidget *parent = 0);
    ~addEditPlatformDialog();

private slots:

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_pushButton_cancel_clicked();

    void on_pushButton_ok_clicked();

signals:
    void sendPlatform(Platform* platf);
    void refreshPlatforms();

private:
    Ui::addEditPlatformDialog *ui;
    bool isAdd;
    QList<Platform*> listForCheck;
    Platform* platformForEdit;
};

#endif // ADDEDITPLATFORMDIALOG_H
