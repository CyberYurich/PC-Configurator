#ifndef CONFIGURATORWIDGET_H
#define CONFIGURATORWIDGET_H

#include <QWidget>
#include <QList>
#include <QDebug>
#include <QComboBox>
#include <QSpinBox>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QDate>
#include <QAxObject>
#include "platform.h"
#include "components.h"

namespace Ui {
class ConfiguratorWidget;
}

class ConfiguratorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfiguratorWidget(QWidget *parent = 0, const int countOfComponents = 12);
    ~ConfiguratorWidget();

    void refreshPlatformBox();

    void saveOtherSettings();
    void loadOtherSettings();

    int getOfferNumber() const {return offerNumber;}
    void setOfferNumber(int number) {offerNumber = number;}

public slots:
    void connectConfigurator(const QList<Platform*>* platformsList,
                             const QList<Component *> **ComponentsArray,
                             const QDoubleSpinBox* cardReaderPriceDSpinbox);

private slots:
    void on_comboBox_Platform_currentIndexChanged(const QString &arg1);

    void on_comboBox_MB_currentIndexChanged(const QString &arg1);

    void on_comboBox_Case_currentIndexChanged(const QString &arg1);

    void on_comboBox_CPU_currentIndexChanged(const QString &arg1);

    void on_comboBox_Cooler_currentIndexChanged(const QString &arg1);

    void on_comboBox_PSU_currentIndexChanged(const QString &arg1);

    void on_comboBox_RAM_currentIndexChanged(const QString &arg1);

    void on_comboBox_HDD1_currentIndexChanged(const QString &arg1);

    void on_comboBox_HDD2_currentIndexChanged(const QString &arg1);

    void on_comboBox_HDD3_currentIndexChanged(const QString &arg1);

    void on_comboBox_HDD4_currentIndexChanged(const QString &arg1);

    void on_comboBox_Video_currentIndexChanged(const QString &arg1);

    void on_comboBox_DVD_currentIndexChanged(const QString &arg1);

    void on_checkBox_Reader_stateChanged(int arg1);

    void on_comboBox_KB_currentIndexChanged(const QString &arg1);

    void on_comboBox_Mouse_currentIndexChanged(const QString &arg1);

    void on_comboBox_OS_currentIndexChanged(const QString &arg1);

    void on_comboBox_Lic_currentIndexChanged(const QString &arg1);

    void on_comboBox_Soft1_currentIndexChanged(const QString &arg1);

    void on_comboBox_Soft2_currentIndexChanged(const QString &arg1);

    void on_comboBox_Other1_currentIndexChanged(const QString &arg1);

    void on_comboBox_Other2_currentIndexChanged(const QString &arg1);

    void on_comboBox_Other3_currentIndexChanged(const QString &arg1);

    void on_comboBox_Other4_currentIndexChanged(const QString &arg1);

    void calculate_lineEdit_cost_All(const QString& arg1);

    void calculate_lineEdit_price_All(const QString& arg1);

    void on_lineEdit_cost_All_textChanged(const QString &arg1);

    void on_lineEdit_price_All_textChanged(const QString &arg1);

    void on_lineEdit_cost_Total_textChanged(const QString &arg1);

    void on_pushButton_offer_clicked();

private:
    Ui::ConfiguratorWidget *ui;
    const QList<Platform*>* platformsList;
    const QList<Component*>** ComponentsArray;
    const QDoubleSpinBox* cardReaderPriceDSpinbox;
    QSettings* otherSettings;
    const int arrayCount;
    int offerNumber;

    int PSUcurrentIndex;
    int RAMcurrentIndex;
    int HDD1currentIndex;
    int HDD2currentIndex;
    int HDD3currentIndex;
    int HDD4currentIndex;
    int VideoCurrentIndex;
    int DVDcurrentIndex;
    int KBcurrentIndex;
    int MouseCurrentIndex;
    int Other1currentIndex;
    int Other2currentIndex;
    int Other3currentIndex;
    int Other4currentIndex;

    int RAMcurrentQuantity;
    int HDD1currentQuantity;
    int HDD2currentQuantity;
    int HDD3currentQuantity;
    int HDD4currentQuantity;
    int VideoCurrentQuantity;
    int DVDcurrentQuantity;
    int KBcurrentQuantity;
    int MouseCurrentQuantity;
    int Other1currentQuantity;
    int Other2currentQuantity;
    int Other3currentQuantity;
    int Other4currentQuantity;

    void clearCombobox(QComboBox* box);
    void clearSpinbox(QSpinBox* box);
    void refreshDescription();
    void refreshCombobox(QComboBox* box, int compArrIndex, bool isRequired = false);
    void refreshCostAndPrice(QLineEdit *lineCost, QLineEdit *linePrice, QComboBox *curItem,
                             QSpinBox *quantity);
    void refreshAllComponents();
    bool eventFilter(QObject* obj, QEvent* event);

    bool checkPSU();
    bool checkRAM();
    bool checkHDDandDVD();
    bool checkVideo();
    bool checkKBandMouse();
    bool checkOthers();

    QString printComponent(QString compName, QComboBox* combobox, QSpinBox* spinbox = NULL);
    void printOptionalComponent(QTextStream& stream, QString compName, QComboBox* combobox,
                                QSpinBox* spinbox);
    void saveOfferToTxt(QString fileName);

    void printTextToBookmark(QAxObject* activeDoc, QString bookmarkName, QString text);
    QString getComponentForDoc(QComboBox *combobox, bool isTemplateExist, QSpinBox *spinbox = NULL);
    QString getOptionalComponentForDoc(QComboBox *combobox,bool isTemplateExist,QSpinBox *spinbox);
    QString getAllComponentsForDoc(bool isTemplateExist);
    void saveOfferToDoc(QString fileName);
};

#endif // CONFIGURATORWIDGET_H
