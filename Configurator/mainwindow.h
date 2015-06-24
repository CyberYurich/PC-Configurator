#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QFileDialog>
#include "platformswidget.h"
#include "componentswidget.h"
#include "configuratorwidget.h"
#include "JlCompress.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, const int countOfComponents = 12);
    ~MainWindow();

    const QList<Component*>** getComponentsArray() const;

signals:
    void queryForLoadPlatforms(QList<Platform*>* platformsList);

    void queryForLoadComponents(QList<Component*>* ListMB, QList<Component*>* ListCase,
                                QList<Component*>* ListCPU, QList<Component*>* ListCooler,
                                QList<Component*>* ListPSU, QList<Component*>* ListRAM,
                                QList<Component*>* ListHDD, QList<Component*>* ListVideo,
                                QList<Component*>* ListDVD, QList<Component*>* ListKbMouse,
                                QList<Component*>* ListSoft, QList<Component*>* ListOthers,
                                double readerPrice);

    void queryForRefreshPlatformsList(const QList<Platform*>* platformsList);

    void queryForConnectConfigurator(const QList<Platform*>* platformsList,
                                     const QList<Component*>** ComponentsArray,
                                     const QDoubleSpinBox* cardReaderPriceDSpinbox);

public slots:
    void platformsChanged();
    void componentsChanged();

private slots:
    void on_actionPlatforms_triggered();

    void on_actionConfigurator_triggered();

    void on_actionComponents_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionUpload_triggered();

private:
    Ui::MainWindow *ui;
    QStackedWidget* mainStackWidget;
    PlatformsWidget* platformsWidget;
    ComponentsWidget* componentsWidget;
    ConfiguratorWidget* configuratorWidget;
    QSettings* mainSettings;
    const int arrayCount;    
    bool isPlatformsChanged;
    bool isComponentsChanged;

    QString savePlatforms(QString filePath);
    QList<Platform *> *loadPlatforms();
    QString saveComponentsList(QString filePath, ComponentType type, bool isUploadForClient);
    QList<Component*>* loadComponentsList(QString filePath, ComponentType type);
    QString saveCardReader(QString filePath);
    double loadCardReader();
    void saveAll();
    void loadAll();
    void closeEvent(QCloseEvent *event);
    void saveMainSettings();
    void loadMainSettings();
    void uploadAllForClient(const QString &archiveName);
    void compressFiles(const QStringList& files, const QString& archiveName);

};

#endif // MAINWINDOW_H
