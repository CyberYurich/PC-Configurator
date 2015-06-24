#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QObject>
#include <QDebug>
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
        QObject(parent), name(""), price(0.0), connectedPlatforms(new QList<QString>){}

    explicit Component(QString name, double price, QObject *parent = 0,
                       QList<QString>* connectedPlatforms = new QList<QString>):
        QObject(parent), name(name), price(price), connectedPlatforms(connectedPlatforms){}

    QString getName() const {return name;}
    double getPrice() const {return price;}
    QList<QString>* getConnectedPlatforms() const {return connectedPlatforms;}

    virtual QDataStream& loadComponent(QDataStream &stream);

    virtual ~Component();

private:
    QString name;
    double price;
    QList<QString>* connectedPlatforms;
};

Q_DECLARE_METATYPE(Component*)

//PSU
class PSU : public Component
{
    Q_OBJECT
public:
    explicit PSU(QObject *parent = 0):
        Component(parent), power(0){}

    explicit PSU(QString name, double price, int power, QObject *parent = 0,
                 QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, price, parent, connectedPlatforms), power(power){}

    int getPower() const {return power;}

    virtual QDataStream& loadComponent(QDataStream &stream) override;

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

    explicit RAM(QString name, double price,  short countOfModules, short capacity,
                 QObject *parent = 0, QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, price, parent, connectedPlatforms),
        countOfModules(countOfModules), capacity(capacity){}

    short getCountOfModules() const {return countOfModules;}
    short getCapacity() const {return capacity;}

    virtual QDataStream& loadComponent(QDataStream &stream) override;

private:
    short countOfModules;
    short capacity;
};

Q_DECLARE_METATYPE(RAM*)

//Video
class Video : public Component
{
    Q_OBJECT
public:
    explicit Video(QObject *parent = 0):
        Component(parent), powerRank("Первый"){}

    explicit Video(QString name, double price, QString powerRank, QObject *parent = 0,
                   QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, price, parent, connectedPlatforms), powerRank(powerRank){}

    QString getPowerRank() const {return powerRank;}

    virtual QDataStream& loadComponent(QDataStream &stream) override;

private:
    QString powerRank;
};

Q_DECLARE_METATYPE(Video*)

//KB and Mouse
class KbMouse : public Component
{
    Q_OBJECT
public:
    explicit KbMouse(QObject *parent = 0):
        Component(parent), type("Клавиатура"), connector("PS/2"){}

    explicit KbMouse(QString name, double price, QString type, QString connector,
                     QObject *parent = 0, QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, price, parent, connectedPlatforms), type(type), connector(connector){}

    QString getTypeKbMouse() const {return type;}
    QString getConnector() const {return connector;}

    virtual QDataStream& loadComponent(QDataStream &stream) override;

private:
    QString type;
    QString connector;
};

Q_DECLARE_METATYPE(KbMouse*)

//Soft
class Soft : public Component
{
    Q_OBJECT
public:
    explicit Soft(QObject *parent = 0):
        Component(parent), type("ОС"){}

    explicit Soft(QString name, double price, QString type, QObject *parent = 0,
                  QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, price, parent, connectedPlatforms), type(type){}

    QString getTypeSoft() const {return type;}

    virtual QDataStream& loadComponent(QDataStream &stream) override;

private:
    QString type;
};

Q_DECLARE_METATYPE(Soft*)

//Others (PCIe)
class Others : public Component
{
    Q_OBJECT
public:
    explicit Others(QObject *parent = 0):
        Component(parent), pcie("x1"){}

    explicit Others(QString name, double price, QString pcie, QObject *parent = 0,
                    QList<QString>* connectedPlatforms = new QList<QString>):
        Component(name, price, parent, connectedPlatforms), pcie(pcie){}

    QString getPcie() const {return pcie;}

    virtual QDataStream& loadComponent(QDataStream &stream) override;

private:
    QString pcie;
};

Q_DECLARE_METATYPE(Others*)

#endif // COMPONENTS_H
