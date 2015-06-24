#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, const int countOfComponents) :
    QMainWindow(parent), ui(new Ui::MainWindow), arrayCount(countOfComponents)
{
    ui->setupUi(this);
    this->setWindowTitle("Конфигуратор ПК[*] - для поставщика");
    mainStackWidget = new QStackedWidget(this);

    platformsWidget = new PlatformsWidget(this);
    connect(this, SIGNAL(queryForLoadPlatforms(QList<Platform*>*)),
            platformsWidget, SLOT(loadPlatforms(QList<Platform*>*)));

    componentsWidget = new ComponentsWidget(this);
    connect(this, SIGNAL(queryForRefreshPlatformsList(const QList<Platform*>*)),
            componentsWidget, SLOT(refreshPlatformsList(const QList<Platform*>*)));
    //Temp
    connect(this, SIGNAL(queryForLoadComponents(QList<Component*>*, QList<Component*>*,
                                                QList<Component*>*, QList<Component*>*,
                                                QList<Component*>*, QList<Component*>*,
                                                QList<Component*>*, QList<Component*>*,
                                                QList<Component*>*, QList<Component*>*,
                                                QList<Component*>*, QList<Component*>*, double)),
            componentsWidget, SLOT(loadComponents(QList<Component*>*, QList<Component*>*,
                                                  QList<Component*>*, QList<Component*>*,
                                                  QList<Component*>*, QList<Component*>*,
                                                  QList<Component*>*, QList<Component*>*,
                                                  QList<Component*>*, QList<Component*>*,
                                                  QList<Component*>*, QList<Component*>*, double)));

    connect(platformsWidget, SIGNAL(removePlatformFromComponents(QString)),
            componentsWidget, SLOT(removePlatform(QString)));

    configuratorWidget = new ConfiguratorWidget(this, arrayCount);
    connect(this, SIGNAL(queryForConnectConfigurator(const QList<Platform*>*,
                                                     const QList<Component*>**,
                                                     const QDoubleSpinBox*)),
            configuratorWidget, SLOT(connectConfigurator(const QList<Platform*>*,
                                                         const QList<Component*>**,
                                                         const QDoubleSpinBox*)));

    connect(platformsWidget, SIGNAL(platformsChanged()), this, SLOT(platformsChanged()));
    connect(componentsWidget, SIGNAL(componentsChanged()), this, SLOT(componentsChanged()));

    mainStackWidget->addWidget(platformsWidget);
    mainStackWidget->addWidget(componentsWidget);
    mainStackWidget->addWidget(configuratorWidget);
    setCentralWidget(mainStackWidget);

    loadAll();

    mainSettings = new QSettings(this);
    loadMainSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

const QList<Component*>** MainWindow::getComponentsArray() const
{
    const QList<Component*>** result = new const QList<Component*>*[arrayCount];

    result[0] = componentsWidget->getComponentsList(COMPONENT_MB);
    result[1] = componentsWidget->getComponentsList(COMPONENT_CASE);
    result[2] = componentsWidget->getComponentsList(COMPONENT_CPU);
    result[3] = componentsWidget->getComponentsList(COMPONENT_COOLER);
    result[4] = componentsWidget->getComponentsList(COMPONENT_PSU);
    result[5] = componentsWidget->getComponentsList(COMPONENT_RAM);
    result[6] = componentsWidget->getComponentsList(COMPONENT_HDD);
    result[7] = componentsWidget->getComponentsList(COMPONENT_VIDEO);
    result[8] = componentsWidget->getComponentsList(COMPONENT_DVD);
    result[9] = componentsWidget->getComponentsList(COMPONENT_KB_MOUSE);
    result[10] = componentsWidget->getComponentsList(COMPONENT_SOFT);
    result[11] = componentsWidget->getComponentsList(COMPONENT_OTHERS);

    return result;
}

void MainWindow::saveMainSettings()
{
    mainSettings->setValue("geometry", saveGeometry());
    mainSettings->setValue("current_widget", mainStackWidget->currentIndex());
    mainSettings->setValue("offer_number", configuratorWidget->getOfferNumber());
}

void MainWindow::loadMainSettings()
{
    restoreGeometry(mainSettings->value("geometry").toByteArray());
    switch(mainSettings->value("current_widget").toInt())
    {
        case 0: ui->actionPlatforms->triggered(); break;
        case 1: ui->actionComponents->triggered(); break;
        case 2: ui->actionConfigurator->triggered(); break;
    }
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
}

void MainWindow::platformsChanged()
{
    isPlatformsChanged = true;
    this->setWindowModified(true);
}

void MainWindow::componentsChanged()
{
    isComponentsChanged = true;
    this->setWindowModified(true);
}

void MainWindow::on_actionPlatforms_triggered()
{
    mainStackWidget->setCurrentIndex(0);
    ui->actionPlatforms->setChecked(true);
    ui->actionComponents->setChecked(false);
    ui->actionConfigurator->setChecked(false);
}

void MainWindow::on_actionComponents_triggered()
{
    mainStackWidget->setCurrentIndex(1);
    ui->actionComponents->setChecked(true);
    ui->actionPlatforms->setChecked(false);
    ui->actionConfigurator->setChecked(false);

    emit queryForRefreshPlatformsList(platformsWidget->getPlatformsList());
}

void MainWindow::on_actionConfigurator_triggered()
{
    mainStackWidget->setCurrentIndex(2);
    ui->actionConfigurator->setChecked(true);
    ui->actionComponents->setChecked(false);
    ui->actionPlatforms->setChecked(false);

    if(isPlatformsChanged || isComponentsChanged)
    {
        configuratorWidget->refreshPlatformBox();
        isPlatformsChanged = false;
        isComponentsChanged = false;
    }
}

void MainWindow::on_actionSave_triggered()
{
    saveAll();
    configuratorWidget->saveOtherSettings();
    this->setWindowModified(false);
}

void MainWindow::on_actionLoad_triggered()
{
    loadAll();
}

void MainWindow::on_actionUpload_triggered()
{
    QDir dir = QDir::current();
    if(dir.exists("Uploads"))
        dir.cd("Uploads");
    else
    {
        if(dir.mkdir("Uploads"))
            dir.cd("Uploads");
        else
        {
            qDebug() << "Невозможно создать директорию Uploads";
            ui->statusBar->showMessage("Невозможно создать директорию Uploads");
        }
    }

    QString curDate = QDate::currentDate().toString("dd-MM-yy");

    QString archive = QFileDialog::getSaveFileName(this, "Сохранение базы данных",
                                                   dir.filePath(curDate + ".dbc"),
                                                   "DB Compressed Files (*.dbc)");
    if(!archive.isEmpty())
        uploadAllForClient(archive);
    else
    {
        qDebug() << "Имя архива не выбрано";
        ui->statusBar->showMessage("Имя архива не выбрано");
    }
}

QString MainWindow::savePlatforms(QString filePath)
{
    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_3);

        const QList<Platform*>* platfList = platformsWidget->getPlatformsList();
        QListIterator<Platform*> i(*platfList);
        while(i.hasNext())
        {
            stream << i.next();
            file.flush();
            qDebug() << "Платформа" << i.peekPrevious()->getName() << "сохранена";
        }
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка записи файла";
            ui->statusBar->showMessage("Ошибка записи файла");
        }
        else
        {
            qDebug() << "Все платформы сохранены";
            ui->statusBar->showMessage("Все платформы сохранены");
        }
    }
    else
    {
        qDebug() << "Ошибка открытия файла при записи: " << file.errorString();
        ui->statusBar->showMessage("Ошибка открытия файла при записи: " + file.errorString());
    }

    file.close();
    return file.fileName();
}

QList<Platform*>* MainWindow::loadPlatforms()
{
    QList<Platform*>* platfList = new QList<Platform*>;
    QString fileName("platforms.bin");
    QFile file(fileName);
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

QString MainWindow::saveComponentsList(QString filePath, ComponentType type, bool isUploadForClient)
{
    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_3);

        const QList<Component*>* compList = componentsWidget->getComponentsList(type);
        QListIterator<Component*> i(*compList);
        while(i.hasNext())
        {
            if(isUploadForClient)
                i.next()->uploadComponent(stream);
            else
                i.next()->saveComponent(stream);

            file.flush();
            qDebug() << "Комплектующая" << i.peekPrevious()->getName() << "сохранена";
        }
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка записи файла";
            ui->statusBar->showMessage("Ошибка записи файла");
        }
        else
        {
            qDebug() << "Список комплектующих сохранен";
            ui->statusBar->showMessage("Список комплектующих сохранен");
        }
    }
    else
    {
        qDebug() << "Ошибка открытия файла при записи: " << file.errorString();
        ui->statusBar->showMessage("Ошибка открытия файла при записи: " + file.errorString());
    }

    file.close();
    return file.fileName();
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

QString MainWindow::saveCardReader(QString filePath)
{
    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_3);

        double readerPrice = componentsWidget->getCardReaderPriceDSpinbox()->value();

        stream << readerPrice;
        file.flush();

        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка записи файла";
            ui->statusBar->showMessage("Ошибка записи файла");
        }
        else
        {
            qDebug() << "Цена картридера сохранена";
            ui->statusBar->showMessage("Цена картридера сохранена");
        }
    }
    else
    {
        qDebug() << "Ошибка открытия файла при записи: " << file.errorString();
        ui->statusBar->showMessage("Ошибка открытия файла при записи: " + file.errorString());
    }

    file.close();
    return file.fileName();
}

double MainWindow::loadCardReader()
{
    double readerPrice;
    QString fileName("cardreader.bin");
    QFile file(fileName);
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
    QList<Platform*>* listPlatforms = loadPlatforms();

    emit queryForLoadPlatforms(listPlatforms);

    QList<Component*>* listMB = loadComponentsList("mb.bin", COMPONENT_MB);
    QList<Component*>* listCase = loadComponentsList("case.bin", COMPONENT_CASE);
    QList<Component*>* listCPU = loadComponentsList("cpu.bin", COMPONENT_CPU);
    QList<Component*>* listCooler = loadComponentsList("cooler.bin", COMPONENT_COOLER);
    QList<Component*>* listPSU = loadComponentsList("psu.bin", COMPONENT_PSU);
    QList<Component*>* listRAM = loadComponentsList("ram.bin", COMPONENT_RAM);
    QList<Component*>* listHDD = loadComponentsList("hdd.bin", COMPONENT_HDD);
    QList<Component*>* listVideo = loadComponentsList("video.bin", COMPONENT_VIDEO);
    QList<Component*>* listDVD = loadComponentsList("dvd.bin", COMPONENT_DVD);
    QList<Component*>* listKbMouse = loadComponentsList("kbmouse.bin", COMPONENT_KB_MOUSE);
    QList<Component*>* listSoft = loadComponentsList("soft.bin", COMPONENT_SOFT);
    QList<Component*>* listOthers = loadComponentsList("others.bin", COMPONENT_OTHERS);

    double readerPrice = loadCardReader();

    emit queryForLoadComponents(listMB, listCase, listCPU, listCooler, listPSU, listRAM, listHDD,
                                listVideo, listDVD, listKbMouse, listSoft, listOthers, readerPrice);

    emit queryForConnectConfigurator(platformsWidget->getPlatformsList(),
                                     this->getComponentsArray(),
                                     componentsWidget->getCardReaderPriceDSpinbox());

    configuratorWidget->refreshPlatformBox();
    configuratorWidget->loadOtherSettings();
    isPlatformsChanged = false;
    isComponentsChanged = false;
    this->setWindowModified(false);

    ui->statusBar->showMessage("Данные загружены");
}

void MainWindow::saveAll()
{
    if(isPlatformsChanged || isComponentsChanged)
    {
        configuratorWidget->refreshPlatformBox();
        isPlatformsChanged = false;
        isComponentsChanged = false;
    }

    savePlatforms("platforms.bin");
    saveComponentsList("mb.bin", COMPONENT_MB, false);
    saveComponentsList("case.bin", COMPONENT_CASE, false);
    saveComponentsList("cpu.bin", COMPONENT_CPU, false);
    saveComponentsList("cooler.bin", COMPONENT_COOLER, false);
    saveComponentsList("psu.bin", COMPONENT_PSU, false);
    saveComponentsList("ram.bin", COMPONENT_RAM, false);
    saveComponentsList("hdd.bin", COMPONENT_HDD, false);
    saveComponentsList("video.bin", COMPONENT_VIDEO, false);
    saveComponentsList("dvd.bin", COMPONENT_DVD, false);
    saveComponentsList("kbmouse.bin", COMPONENT_KB_MOUSE, false);
    saveComponentsList("soft.bin", COMPONENT_SOFT, false);
    saveComponentsList("others.bin", COMPONENT_OTHERS, false);
    saveCardReader("cardreader.bin");

    ui->statusBar->showMessage("Данные сохранены");
}

void MainWindow::uploadAllForClient(const QString& archiveName)
{
    QDir dir = QDir::tempPath();

    QStringList files;
    files.append(savePlatforms(dir.filePath("platforms.upl")));
    files.append(saveComponentsList(dir.filePath("mb.upl"), COMPONENT_MB, true));
    files.append(saveComponentsList(dir.filePath("case.upl"), COMPONENT_CASE, true));
    files.append(saveComponentsList(dir.filePath("cpu.upl"), COMPONENT_CPU, true));
    files.append(saveComponentsList(dir.filePath("cooler.upl"), COMPONENT_COOLER, true));
    files.append(saveComponentsList(dir.filePath("psu.upl"), COMPONENT_PSU, true));
    files.append(saveComponentsList(dir.filePath("ram.upl"), COMPONENT_RAM, true));
    files.append(saveComponentsList(dir.filePath("hdd.upl"), COMPONENT_HDD, true));
    files.append(saveComponentsList(dir.filePath("video.upl"), COMPONENT_VIDEO, true));
    files.append(saveComponentsList(dir.filePath("dvd.upl"), COMPONENT_DVD, true));
    files.append(saveComponentsList(dir.filePath("kbmouse.upl"), COMPONENT_KB_MOUSE, true));
    files.append(saveComponentsList(dir.filePath("soft.upl"), COMPONENT_SOFT, true));
    files.append(saveComponentsList(dir.filePath("others.upl"), COMPONENT_OTHERS, true));
    files.append(saveCardReader(dir.filePath("cardreader.upl")));

    compressFiles(files, archiveName);

    foreach(QString file, files)
    {
        if(QFile::remove(file))
            qDebug() << "Удален файл: " << file;
        else
            qDebug() << "Ошибка удаления файла: " << file;
    }

    ui->statusBar->showMessage("Данные выгружены");
}

void MainWindow::compressFiles(const QStringList& files, const QString& archiveName)
{
    if(JlCompress::compressFiles(archiveName, files))
        qDebug() << "Успешная архивация";
    else
        qDebug() << "Ошибка архивации";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(this->isWindowModified())
    {
        int ret = QMessageBox::question(this, "Выход из программы",
                                        "Данные были изменены. Сохранить?",
                                        "Да", "Нет", "Отмена", 0, 2);
        if(ret == 0)
        {
            saveMainSettings();
            configuratorWidget->saveOtherSettings();
            saveAll();
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
        configuratorWidget->saveOtherSettings();
        event->accept();
    }
}
