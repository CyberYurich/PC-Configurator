#ifndef PLATFORMSWIDGET_H
#define PLATFORMSWIDGET_H

#include <QWidget>
#include <QList>
#include <QDebug>
#include <QTreeWidgetItem>
#include "platform.h"
#include "addeditplatformdialog.h"

namespace Ui {
class PlatformsWidget;
}

class PlatformsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlatformsWidget(QWidget *parent = 0);
    ~PlatformsWidget();

    const QList<Platform*>* getPlatformsList() const {return platformsList;}

signals:
    void removePlatformFromComponents(QString platformForRemove);
    void platformsChanged();

public slots:
    void addPlatform(Platform* platf);
    void refreshPlatforms();
    void loadPlatforms(QList<Platform*>* platformsList);

private slots:
    void on_btnAddPlatform_clicked();

    void on_btnDeletePlatform_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item);

private:
    Ui::PlatformsWidget *ui;
    QList<Platform*>* platformsList;

    void clearAndDeletePlatforms(QList<Platform*>* list);
};

#endif // PLATFORMSWIDGET_H
