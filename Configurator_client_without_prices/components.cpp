#include "components.h"

QDataStream &Component::loadComponent(QDataStream &stream)
{
    stream >> this->name;
    stream >> this->price;

    this->connectedPlatforms->clear();
    stream >> *(this->connectedPlatforms);

    return stream;
}

Component::~Component()
{
    qDebug() << "Удаление комплектующей:" << this->getName();
    delete connectedPlatforms;
}

QDataStream &PSU::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->power;

    return streamTemp;
}

QDataStream &RAM::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->countOfModules;
    streamTemp >> this->capacity;

    return streamTemp;
}

QDataStream &Video::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->powerRank;

    return streamTemp;
}

QDataStream &KbMouse::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->type;
    streamTemp >> this->connector;

    return streamTemp;
}

QDataStream &Soft::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->type;

    return streamTemp;
}

QDataStream &Others::loadComponent(QDataStream &stream)
{
    QDataStream& streamTemp = Component::loadComponent(stream);
    streamTemp >> this->pcie;

    return streamTemp;
}
