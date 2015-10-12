#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QObject>
#include <QDebug>
#include <cmath>
#include <QTreeWidget>
#include "platform.h"

enum ComponentType
{
    COMPONENT_DEFAULT,
    COMPONENT_MB,
    COMPONENT_CASE,
    COMPONENT_CPU,
    COMPONENT_COOLER,
    COMPONENT_PSU,
    COMPONENT_RAM,
    COMPONENT_HDD,
    COMPONENT_VIDEO,
    COMPONENT_DVD,
    COMPONENT_KB_MOUSE,
    COMPONENT_SOFT,
    COMPONENT_OTHERS
};

//Default component
class Component : public QObject
{
    Q_OBJECT
public:
    explicit Component(QObject *parent = 0):
        QObject(parent), name(""), cost(0.0), price(0.0), margin(0.0),
        connectedPlatforms(new QList<QString>){}

    explicit Component(QString name, double cost, double price, double margin, QObject *parent = 0,
                       QList<QString>* connectedPlatforms = new QList<QString>):
        QObject(parent), name(name), cost(cost), price(price), margin(margin),
        connectedPlatforms(connectedPlatforms){}

    void editCost(double cost);
    void editMargin(double margin);
    void editPrice(double price);

    void addPlatform(QString platformName);
    void delPlatform(QString platformName);

    QString getName() const {return name;}
    double getCost() const {return cost;}
    double getPrice() const {return price;}
    double getMargin() const {return margin;}
    QList<QString>* getConnectedPlatforms() const {return connectedPlatforms;}

    // template method
    QTreeWidgetItem* getTreeWidgetItem();

    virtual void setAdvancedParameter(QTreeWidgetItem* item, int column)
    {Q_UNUSED(item) Q_UNUSED(column)}

    virtual QDataStream& saveComponent(QDataStream &stream);
    virtual QDataStream& loadComponent(QDataStream &stream);

    virtual QDataStream& uploadComponent(QDataStream &stream);

    virtual ~Component();

private:
    QString name;
    double cost;
    double price;
    double margin;
    QList<QString>* connectedPlatforms;

    void setPrice();
    void setCost();
    void setMargin();

    // hook for template method
    virtual void setAdditionalColumns(QTreeWidgetItem* item) {Q_UNUSED(item)}
};

Q_DECLARE_METATYPE(Component*)

//PSU
class PSU : public Component
{
    Q_OBJECT
public:
    explicit PSU(QObject *parent = 0):
        Component(parent), power(0){}

    explicit PSU(QString name, double cost, double price, double margin, int power,
                 QObject *parent = 0, QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, cost, price, margin, parent, connectedPlatforms), power(power){}

    void setPower(int power){this->power = power;}
    int getPower() const {return power;}

    virtual void setAdvancedParameter(QTreeWidgetItem* item, int column) override;

    virtual QDataStream& saveComponent(QDataStream &stream) override;
    virtual QDataStream& loadComponent(QDataStream &stream) override;

    virtual QDataStream& uploadComponent(QDataStream &stream) override;

    virtual void setAdditionalColumns(QTreeWidgetItem* item) override;

private:
    int power;
};

Q_DECLARE_METATYPE (PSU*)

//RAM
class RAM : public Component
{
    Q_OBJECT
public:
    explicit RAM(QObject *parent = 0):
        Component(parent), countOfModules(0), capacity(0){}

    explicit RAM(QString name, double cost, double price,  double margin,
                 short countOfModules, short capacity, QObject *parent = 0,
                 QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, cost, price, margin, parent, connectedPlatforms),
        countOfModules(countOfModules), capacity(capacity){}

    void setCountOfModules(short countOfModules){this->countOfModules = countOfModules;}
    void setCapacity(short capacity){this->capacity = capacity;}
    short getCountOfModules() const {return countOfModules;}
    short getCapacity() const {return capacity;}

    virtual void setAdvancedParameter(QTreeWidgetItem* item, int column) override;

    virtual QDataStream& saveComponent(QDataStream &stream) override;
    virtual QDataStream& loadComponent(QDataStream &stream) override;

    virtual QDataStream& uploadComponent(QDataStream &stream) override;

    virtual void setAdditionalColumns(QTreeWidgetItem* item) override;

private:
    short countOfModules;
    short capacity;
};

Q_DECLARE_METATYPE(RAM*)

//Video
//enum PowerRank {POWER_ONE, POWER_TWO, POWER_THREE};
class Video : public Component
{
    Q_OBJECT
public:
    explicit Video(QObject *parent = 0):
        Component(parent), powerRank("Первый"){}

    explicit Video(QString name, double cost, double price, double margin, QString powerRank,
                   QObject *parent = 0, QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, cost, price, margin, parent, connectedPlatforms), powerRank(powerRank){}

    void setPowerRank(QString powerRank){this->powerRank = powerRank;}
    QString getPowerRank() const {return powerRank;}

    virtual void setAdvancedParameter(QTreeWidgetItem* item, int column) override;

    virtual QDataStream& saveComponent(QDataStream &stream) override;
    virtual QDataStream& loadComponent(QDataStream &stream) override;

    virtual QDataStream& uploadComponent(QDataStream &stream) override;

    virtual void setAdditionalColumns(QTreeWidgetItem* item) override;

private:
    QString powerRank;
};

Q_DECLARE_METATYPE(Video*)

//KB and Mouse
//enum TypeKbMouse {KB, MOUSE};
//enum Connector {PS2, USB};
class KbMouse : public Component
{
    Q_OBJECT
public:
    explicit KbMouse(QObject *parent = 0):
        Component(parent), type("Клавиатура"), connector("PS/2"){}

    explicit KbMouse(QString name, double cost, double price, double margin,
                     QString type, QString connector, QObject *parent = 0,
                     QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, cost, price, margin, parent, connectedPlatforms),
        type(type), connector(connector){}

    void setTypeKbMouse(QString type){this->type = type;}
    void setConnector(QString connector){this->connector = connector;}
    QString getTypeKbMouse() const {return type;}
    QString getConnector() const {return connector;}

    virtual void setAdvancedParameter(QTreeWidgetItem* item, int column) override;

    virtual QDataStream& saveComponent(QDataStream &stream) override;
    virtual QDataStream& loadComponent(QDataStream &stream) override;

    virtual QDataStream& uploadComponent(QDataStream &stream) override;

    virtual void setAdditionalColumns(QTreeWidgetItem* item) override;

private:
    QString type;
    QString connector;
};

Q_DECLARE_METATYPE(KbMouse*)

//Soft
//enum TypeSoft {SOFT_OS, SOFT_LIC, SOFT_OTHER};
class Soft : public Component
{
    Q_OBJECT
public:
    explicit Soft(QObject *parent = 0):
        Component(parent), type("ОС"){}

    explicit Soft(QString name, double cost, double price, double margin, QString type,
                  QObject *parent = 0, QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, cost, price, margin, parent, connectedPlatforms), type(type){}

    void setTypeSoft(QString type){this->type = type;}
    QString getTypeSoft() const {return type;}

    virtual void setAdvancedParameter(QTreeWidgetItem* item, int column) override;

    virtual QDataStream& saveComponent(QDataStream &stream) override;
    virtual QDataStream& loadComponent(QDataStream &stream) override;

    virtual QDataStream& uploadComponent(QDataStream &stream) override;

    virtual void setAdditionalColumns(QTreeWidgetItem* item) override;

private:
    QString type;
};

Q_DECLARE_METATYPE(Soft*)

//Others (PCIe)
//enum SizeOfPcie {PCIE_1, PCIE_4, PCIE_8, PCIE_16};
class Others : public Component
{
    Q_OBJECT
public:
    explicit Others(QObject *parent = 0):
        Component(parent), pcie("x1"){}

    explicit Others(QString name, double cost, double price, double margin, QString pcie,
                    QObject *parent = 0, QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, cost, price, margin, parent, connectedPlatforms), pcie(pcie){}

    void setPcie(QString pcie){this->pcie = pcie;}
    QString getPcie() const {return pcie;}

    virtual void setAdvancedParameter(QTreeWidgetItem* item, int column) override;

    virtual QDataStream& saveComponent(QDataStream &stream) override;
    virtual QDataStream& loadComponent(QDataStream &stream) override;

    virtual QDataStream& uploadComponent(QDataStream &stream) override;

    virtual void setAdditionalColumns(QTreeWidgetItem* item) override;

private:
    QString pcie;
};

Q_DECLARE_METATYPE(Others*)

#endif // COMPONENTS_H
