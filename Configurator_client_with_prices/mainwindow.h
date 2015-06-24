#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QCloseEvent>
#include <QFileDialog>
#include "configuratorwidget.h"
#include "accountdialog.h"
#include "JlCompress.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0,
                        const int countOfComponents = 12);
    ~MainWindow();

signals:

    void queryForConnectConfigurator(const QList<Platform*>* platformsList,
                                     const QList<Component*>** arrayOfComponentsLists,
                                     double cardReaderPrice);

public slots:
    void currentConfigurationChange();
    void saveAccountData(QString organization, QString account);

private slots:

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionLoadData_triggered();

    void on_actionEditAccount_triggered();

private:
    Ui::MainWindow *ui;
    ConfiguratorWidget* configuratorWidget;
    QSettings* mainSettings;

    QList<Platform*>* platformsList;
    const int arrayCount;
    const QList<Component*>** arrayOfComponentsLists;
    double cardReaderPrice;

    QList<Platform*>* loadPlatforms(QString filePath);
    QList<Component*>* loadComponentsList(QString filePath, ComponentType type);
    double loadCardReader(QString filePath);
    void loadAll();
    void closeEvent(QCloseEvent *event);
    void saveMainSettings();
    void loadMainSettings();
    void decompressFiles(const QString& archive);

    void clearAndDeletePlatforms(QList<Platform*>* list);
    void clearAndDeleteComponents(const QList<Component*>** list);
};

#endif // MAINWINDOW_H
