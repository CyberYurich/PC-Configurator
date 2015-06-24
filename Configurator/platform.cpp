#include "platform.h"

void Platform::editPlatform(QString description, QString chipset, int socket, QString sound,
                            QString lan, short usb2, short usb3, short sata, short sata3,
                            short dimm, short ram, bool integrVideo, bool vga, bool dvi, bool hdmi,
                            short pcie1, short pcie4, short pcie8, short pcie16, short ps2,
                            QString caseForm, short ext5_25, short ext3_5, short int3_5,
                            bool integrPsu, int psuPower)
{
    this->description = description;
    this->chipset = chipset;
    this->socket = socket;
    this->sound = sound;
    this->lan = lan;
    this->usb2 = usb2;
    this->usb3 = usb3;
    this->sata = sata;
    this->sata3 = sata3;
    this->dimm = dimm;
    this->ram = ram;
    this->integrVideo = integrVideo;
    this->vga = vga;
    this->dvi = dvi;
    this->hdmi = hdmi;
    this->pcie1 = pcie1;
    this->pcie4 = pcie4;
    this->pcie8 = pcie8;
    this->pcie16 = pcie16;
    this->ps2 = ps2;
    this->caseForm = caseForm;
    this->ext5_25 = ext5_25;
    this->ext3_5 = ext3_5;
    this->int3_5 = int3_5;
    this->integrPsu = integrPsu;
    this->psuPower = psuPower;
}

QDataStream& operator <<(QDataStream &stream, const Platform *platf)
{
    stream << platf->name;
    stream << platf->description;
    stream << platf->chipset;
    stream << QString::number(platf->socket);
    stream << platf->sound;
    stream << platf->lan;
    stream << QString::number(platf->usb2);
    stream << QString::number(platf->usb3);
    stream << QString::number(platf->sata);
    stream << QString::number(platf->sata3);
    stream << QString::number(platf->dimm);
    stream << QString::number(platf->ram);
    stream << (platf->integrVideo ? QString("true") : QString("false"));
    stream << (platf->vga ? QString("true") : QString("false"));
    stream << (platf->dvi ? QString("true") : QString("false"));
    stream << (platf->hdmi ? QString("true") : QString("false"));
    stream << QString::number(platf->pcie1);
    stream << QString::number(platf->pcie4);
    stream << QString::number(platf->pcie8);
    stream << QString::number(platf->pcie16);
    stream << QString::number(platf->ps2);
    stream << platf->caseForm;
    stream << QString::number(platf->ext5_25);
    stream << QString::number(platf->ext3_5);
    stream << QString::number(platf->int3_5);
    stream << (platf->integrPsu ? QString("true") : QString("false"));
    stream << QString::number(platf->psuPower);

    return stream;
}

QDataStream& operator >>(QDataStream &stream, Platform *platf)
{
    QString strTemp;
    stream >> platf->name;
    stream >> platf->description;
    stream >> platf->chipset;

    stream >> strTemp;
    platf->socket = strTemp.toInt();

    stream >> platf->sound;
    stream >> platf->lan;

    stream >> strTemp;
    platf->usb2 = strTemp.toShort();
    stream >> strTemp;
    platf->usb3 = strTemp.toShort();
    stream >> strTemp;
    platf->sata = strTemp.toShort();
    stream >> strTemp;
    platf->sata3 = strTemp.toShort();
    stream >> strTemp;
    platf->dimm = strTemp.toShort();
    stream >> strTemp;
    platf->ram = strTemp.toShort();

    stream >> strTemp;
    platf->integrVideo = (strTemp == "true" ? true : false);
    stream >> strTemp;
    platf->vga = (strTemp == "true" ? true : false);
    stream >> strTemp;
    platf->dvi = (strTemp == "true" ? true : false);
    stream >> strTemp;
    platf->hdmi = (strTemp == "true" ? true : false);

    stream >> strTemp;
    platf->pcie1 = strTemp.toShort();
    stream >> strTemp;
    platf->pcie4 = strTemp.toShort();
    stream >> strTemp;
    platf->pcie8 = strTemp.toShort();
    stream >> strTemp;
    platf->pcie16 = strTemp.toShort();
    stream >> strTemp;
    platf->ps2 = strTemp.toShort();

    stream >> platf->caseForm;

    stream >> strTemp;
    platf->ext5_25 = strTemp.toShort();
    stream >> strTemp;
    platf->ext3_5 = strTemp.toShort();
    stream >> strTemp;
    platf->int3_5 = strTemp.toShort();

    stream >> strTemp;
    platf->integrPsu = (strTemp == "true" ? true : false);

    stream >> strTemp;
    platf->psuPower = strTemp.toInt();

    return stream;
}

