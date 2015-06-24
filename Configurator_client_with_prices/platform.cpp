#include "platform.h"

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

