#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, const int countOfComponents) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    arrayCount(countOfComponents)
{
    ui->setupUi(this);
    this->setWindowTitle("Конфигуратор ПК[*] - для заказчика");
    platformsList = new QList<Platform*>;
    arrayOfComponentsLists = new const QList<Component*>*[arrayCount];
    arrayOfComponentsLists = NULL;

    configuratorWidget = new ConfiguratorWidget(this);
    connect(this, SIGNAL(queryForConnectConfigurator(const QList<Platform*>*,
                                                     const QList<Component*>**,
                                                     double)),
            configuratorWidget, SLOT(connectConfigurator(const QList<Platform*>*,
                                                         const QList<Component*>**,
                                                         double)));
    connect(configuratorWidget, SIGNAL(configurationChanged()),
            this, SLOT(currentConfigurationChange()));
    setCentralWidget(configuratorWidget);

    loadAll();
    configuratorWidget->refreshPlatformBox();
    configuratorWidget->loadOtherSettings();

    this->setWindowModified(false);

    mainSettings = new QSettings(this);
    loadMainSettings();
}

void MainWindow::clearAndDeletePlatforms(QList<Platform*>* list)
{
    qDeleteAll(list->begin(), list->end());
    list->clear();
    delete list;
}

void MainWindow::clearAndDeleteComponents(const QList<Component*>** list)
{

    if(!list) return;

    for(int i = 0; i < arrayCount; ++i)
    {
        QList<Component*>* curList = const_cast<QList<Component*>*>(list[i]);

        qDeleteAll(curList->begin(), curList->end());
        curList->clear();
        delete curList;
    }
    delete[] list;
}

MainWindow::~MainWindow()
{
    clearAndDeletePlatforms(platformsList);
    clearAndDeleteComponents(arrayOfComponentsLists);
    delete ui;
}

void MainWindow::currentConfigurationChange()
{
    this->setWindowModified(true);
}

void MainWindow::saveAccountData(QString organization, QString account)
{
    mainSettings->setValue("organization", organization);
    mainSettings->setValue("account_name", account);
    configuratorWidget->setOrganizationName(organization);
    configuratorWidget->setAccountName(account);    
    ui->statusBar->showMessage("Пользовательские данные изменены");
}

void MainWindow::saveMainSettings()
{
    mainSettings->setValue("geometry", saveGeometry());
    mainSettings->setValue("offer_number", configuratorWidget->getOfferNumber());
    mainSettings->setValue("organization", configuratorWidget->getOrganizationName());
    mainSettings->setValue("account_name", configuratorWidget->getAccountName());
}

void MainWindow::loadMainSettings()
{
    restoreGeometry(mainSettings->value("geometry").toByteArray());
    if(mainSettings->value("current_date").toDate() == QDate::currentDate())
    {
        configuratorWidget->setOfferNumber(mainSettings->value("offer_number").toInt());
    }
    else
    {
        mainSettings->setValue("current_date", QDate::currentDate());
        mainSettings->setValue("offer_number", 1);
        configuratorWidget->setOfferNumber(1);
    }
    if(mainSettings->contains("organization") && mainSettings->contains("account_name"))
    {
        configuratorWidget->setOrganizationName(mainSettings->value("organization").toString());
        configuratorWidget->setAccountName(mainSettings->value("account_name").toString());
    }
    else
    {
        AccountDialog accountDialog(this);
        connect(&accountDialog, SIGNAL(sendAccountData(QString,QString)),
                this, SLOT(saveAccountData(QString,QString)));
        accountDialog.exec();
    }
}

void MainWindow::on_actionLoadData_triggered()
{
    int ret = QMessageBox::warning(this, "Загрузка новых данных",
                          "Внимание! Текущая сохраненная конфигурация будет потеряна. Продолжить?",
                                   QMessageBox::Ok | QMessageBox::Cancel);
    if(ret == QMessageBox::Ok)
    {
        QString archive = QFileDialog::getOpenFileName(this, "Открытие архива базы данных", "",
                          "DB Compressed Files (*.dbc)");

        if (!archive.isEmpty())
        {
            decompressFiles(archive);
            loadAll();
            configuratorWidget->refreshPlatformBox();
            configuratorWidget->clearOtherSettings();
            this->setWindowModified(false);
        }
        else
        {
            qDebug() << "архив не выбран";
            ui->statusBar->showMessage("архив не выбран");
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    configuratorWidget->saveOtherSettings();
    this->setWindowModified(false);
    ui->statusBar->showMessage("Конфигурация сохранена");
}

void MainWindow::on_actionLoad_triggered()
{
    configuratorWidget->loadOtherSettings();
    this->setWindowModified(false);
    ui->statusBar->showMessage("Конфигурация загружена");
}

void MainWindow::on_actionEditAccount_triggered()
{
    AccountDialog accountDialog(configuratorWidget->getOrganizationName(),
                                configuratorWidget->getAccountName(), this);
    connect(&accountDialog, SIGNAL(sendAccountData(QString,QString)),
            this, SLOT(saveAccountData(QString,QString)));
    accountDialog.exec();
}

QList<Platform *> *MainWindow::loadPlatforms(QString filePath)
{
    QList<Platform*>* platfList = new QList<Platform*>;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_3);
        while(!stream.atEnd())
        {
            Platform* platf = new Platform(this);
            stream >> platf;
            platfList->append(platf);
            qDebug() << "Платформа" << platf->getName() << "загружена";
        }
        if (stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка чтения файла";
            ui->statusBar->showMessage("Ошибка чтения файла");
        }
        else
        {
            qDebug() << "Все платформы загружены";
            ui->statusBar->showMessage("Все платформы загружены");
        }
    }
    else
    {
        qDebug() << "Ошибка открытия файла при чтении: " << file.errorString();
        ui->statusBar->showMessage("Ошибка открытия файла при чтении: " + file.errorString());
    }

    file.close();
    return platfList;
}

QList<Component*>* MainWindow::loadComponentsList(QString filePath, ComponentType type)
{
    QList<Component*>* compList = new QList<Component*>;

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_3);
        while(!stream.atEnd())
        {
            Component* comp;
            switch(type)
            {
                case COMPONENT_MB:
                case COMPONENT_CASE:
                case COMPONENT_CPU:
                case COMPONENT_COOLER:
                case COMPONENT_HDD:
                case COMPONENT_DVD:         {comp = new Component(this); break;}
                case COMPONENT_PSU:         {comp = new PSU(this); break;}
                case COMPONENT_RAM:         {comp = new RAM(this); break;}
                case COMPONENT_VIDEO:       {comp = new Video(this); break;}
                case COMPONENT_KB_MOUSE:    {comp = new KbMouse(this); break;}
                case COMPONENT_SOFT:        {comp = new Soft(this); break;}
                case COMPONENT_OTHERS:      {comp = new Others(this); break;}
                case COMPONENT_DEFAULT:     {qDebug() << "Неверный параметр в loadComponentsList";}
            }
            comp->loadComponent(stream);
            compList->append(comp);
            qDebug() << "Комплектующая" << comp->getName() << "загружена";
        }
        if (stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка чтения файла";
            ui->statusBar->showMessage("Ошибка чтения файла");
        }
        else
        {
            qDebug() << "Список комплектующих загружен";
            ui->statusBar->showMessage("Список комплектующих загружен");
        }
    }
    else
    {
        qDebug() << "Ошибка открытия файла при чтении: " << file.errorString();
        ui->statusBar->showMessage("Ошибка открытия файла при чтении: " + file.errorString());
    }

    file.close();
    return compList;
}

double MainWindow::loadCardReader(QString filePath)
{
    double readerPrice;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_3);

        stream >> readerPrice;

        if (stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка чтения файла";
            ui->statusBar->showMessage("Ошибка чтения файла");
        }
        else
        {
            qDebug() << "Цена картридера загружена";
            ui->statusBar->showMessage("Цена картридера загружена");
        }
    }
    else
    {
        qDebug() << "Ошибка открытия файла при чтении: " << file.errorString();
        ui->statusBar->showMessage("Ошибка открытия файла при чтении: " + file.errorString());
    }

    file.close();
    return readerPrice;
}

void MainWindow::loadAll()
{
    QDir dir = QDir::current();

    clearAndDeletePlatforms(platformsList);
    platformsList = loadPlatforms(dir.filePath("platforms.upl"));

    clearAndDeleteComponents(arrayOfComponentsLists);
    arrayOfComponentsLists = new const QList<Component*>*[arrayCount];

    arrayOfComponentsLists[0] = loadComponentsList(dir.filePath("mb.upl"), COMPONENT_MB);
    arrayOfComponentsLists[1] = loadComponentsList(dir.filePath("case.upl"), COMPONENT_CASE);
    arrayOfComponentsLists[2] = loadComponentsList(dir.filePath("cpu.upl"), COMPONENT_CPU);
    arrayOfComponentsLists[3] = loadComponentsList(dir.filePath("cooler.upl"), COMPONENT_COOLER);
    arrayOfComponentsLists[4] = loadComponentsList(dir.filePath("psu.upl"), COMPONENT_PSU);
    arrayOfComponentsLists[5] = loadComponentsList(dir.filePath("ram.upl"), COMPONENT_RAM);
    arrayOfComponentsLists[6] = loadComponentsList(dir.filePath("hdd.upl"), COMPONENT_HDD);
    arrayOfComponentsLists[7] = loadComponentsList(dir.filePath("video.upl"), COMPONENT_VIDEO);
    arrayOfComponentsLists[8] = loadComponentsList(dir.filePath("dvd.upl"), COMPONENT_DVD);
    arrayOfComponentsLists[9] = loadComponentsList(dir.filePath("kbmouse.upl"), COMPONENT_KB_MOUSE);
    arrayOfComponentsLists[10] = loadComponentsList(dir.filePath("soft.upl"), COMPONENT_SOFT);
    arrayOfComponentsLists[11] = loadComponentsList(dir.filePath("others.upl"), COMPONENT_OTHERS);

    cardReaderPrice = loadCardReader(dir.filePath("cardreader.upl"));

    emit queryForConnectConfigurator(platformsList, arrayOfComponentsLists, cardReaderPrice);

    ui->statusBar->showMessage("Данные загружены");
}

void MainWindow::decompressFiles(const QString& archive)
{
    QStringList files = JlCompress::extractDir(archive);

    foreach(QString item, files)
    {
        qDebug() << "Извлечен файл:" << item;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(this->isWindowModified())
    {
        int ret = QMessageBox::question(this, "Выход из программы",
                                        "Конфигурация была изменена. Сохранить?",
                                        "Да", "Нет", "Отмена", 0, 2);
        if(ret == 0)
        {
            saveMainSettings();
            configuratorWidget->saveOtherSettings();
            event->accept();
        }
        else if(ret == 1)
        {
            saveMainSettings();
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        saveMainSettings();
        event->accept();
    }
}
