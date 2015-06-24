#include "components.h"

void Component::editCost(double cost)
{
    this->cost = cost;
    if(this->cost < this->price)
        setMargin();
    else
    {
        this->price = this->cost;
        this->margin = 0.0;
    }
}

void Component::editPrice(double price)
{
    this->price = price;
    if(this->cost < this->price)
        setMargin();
    else
    {
        this->cost = this->price;
        this->margin = 0.0;
    }
}

void Component::editMargin(double margin)
{
    this->margin = margin;
    setPrice();
}

void Component::addPlatform(QString platformName)
{
    connectedPlatforms->append(platformName);
}

void Component::delPlatform(QString platformName)
{
    int i = connectedPlatforms->indexOf(platformName);
    if (i != -1)
        connectedPlatforms->removeAt(i);
}

QDataStream &Component::saveComponent(QDataStream &stream)
{
    stream << this->name;
    stream << this->cost;
    stream << this->price;
    stream << this->margin;

    stream << *(this->connectedPlatforms);

    return stream;
}

QDataStream &Component::loadComponent(QDataStream &stream)
{
    stream >> this->name;
    stream >> this->cost;
    stream >> this->price;
    stream >> this->margin;

    this->connectedPlatforms->clear();
    stream >> *(this->connectedPlatforms);

    return stream;
}

QDataStream &Component::uploadComponent(QDataStream &stream)
{
    stream << this->name;
    stream << this->price;

    stream << *(this->connectedPlatforms);

    return stream;
}

Component::~Component()
{
    qDebug() << "Удаление комплектующей: " << this->getName();
    delete connectedPlatforms;
}

void Component::setPrice()
{
    price = cost / (1.0 - (margin / 100.0));
    /*qDebug() << "Cost = " << cost;
    qDebug() << "Price = " << price;
    qDebug() << "Margin = " << margin;*/

    //Rounding
    price = floor(price * 100 + 0.5) / 100;
    /*qDebug() << "Rounded Cost = " << cost;
    qDebug() << "Rounded Price = " << price;
    qDebug() << "Rounded Margin = " << margin;*/
}

void Component::setCost()
{
    cost = price - (price * (margin / 100.0));
    /*qDebug() << "Cost = " << cost;
    qDebug() << "Price = " << price;
    qDebug() << "Margin = " << margin;*/

    //Rounding
    cost = floor(cost * 100 + 0.5) / 100;
    /*qDebug() << "Rounded Cost = " << cost;
    qDebug() << "Rounded Price = " << price;
    qDebug() << "Rounded Margin = " << margin;*/
}

void Component::setMargin()
{
    margin = ((price - cost) / price) * 100;
    /*qDebug() << "Cost = " << cost;
    qDebug() << "Price = " << price;
    qDebug() << "Margin = " << margin;*/

    //Rounding
    margin = floor(margin * 100 + 0.5) / 100;
    /*qDebug() << "Rounded Cost = " << cost;
    qDebug() << "Rounded Price = " << price;
    qDebug() << "Rounded Margin = " << margin;*/
}

QDataStream &PSU::saveComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::saveComponent(stream);
    streamTemp << this->power;

    return streamTemp;
}

QDataStream &PSU::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->power;

    return streamTemp;
}

QDataStream &PSU::uploadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::uploadComponent(stream);
    streamTemp << this->power;

    return streamTemp;
}

QDataStream &RAM::saveComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::saveComponent(stream);
    streamTemp << this->countOfModules;
    streamTemp << this->capacity;

    return streamTemp;
}

QDataStream &RAM::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->countOfModules;
    streamTemp >> this->capacity;

    return streamTemp;
}

QDataStream &RAM::uploadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::uploadComponent(stream);
    streamTemp << this->countOfModules;
    streamTemp << this->capacity;

    return streamTemp;
}

QDataStream &Video::saveComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::saveComponent(stream);
    streamTemp << this->powerRank;

    return streamTemp;
}

QDataStream &Video::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->powerRank;

    return streamTemp;
}

QDataStream &Video::uploadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::uploadComponent(stream);
    streamTemp << this->powerRank;

    return streamTemp;
}

QDataStream &KbMouse::saveComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::saveComponent(stream);
    streamTemp << this->type;
    streamTemp << this->connector;

    return streamTemp;
}

QDataStream &KbMouse::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->type;
    streamTemp >> this->connector;

    return streamTemp;
}

QDataStream &KbMouse::uploadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::uploadComponent(stream);
    streamTemp << this->type;
    streamTemp << this->connector;

    return streamTemp;
}

QDataStream &Soft::saveComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::saveComponent(stream);
    streamTemp << this->type;

    return streamTemp;
}

QDataStream &Soft::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->type;

    return streamTemp;
}

QDataStream &Soft::uploadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::uploadComponent(stream);
    streamTemp << this->type;

    return streamTemp;
}

QDataStream &Others::saveComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::saveComponent(stream);
    streamTemp << this->pcie;

    return streamTemp;
}

QDataStream &Others::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->pcie;

    return streamTemp;
}

QDataStream &Others::uploadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::uploadComponent(stream);
    streamTemp << this->pcie;

    return streamTemp;
}

