#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QDebug>

class Platform : public QObject
{
    Q_OBJECT
public:
    explicit Platform(QObject *parent = 0):
        QObject(parent), name(""), description(""), chipset(""), socket(0), sound(""), lan(""),
        usb2(0), usb3(0), sata(0), sata3(0), dimm(0), ram(0), integrVideo(false), vga(false),
        dvi(false), hdmi(false),pcie1(0), pcie4(0), pcie8(0), pcie16(0), ps2(0), caseForm(""),
        ext5_25(0), ext3_5(0),int3_5(0), integrPsu(false), psuPower(0){}

    explicit Platform(QString name, QString description, QString chipset, int socket, QString sound,
                      QString lan, short usb2 ,short usb3, short sata, short sata3, short dimm,
                      short ram, bool integrVideo, bool vga, bool dvi, bool hdmi, short pcie1,
                      short pcie4, short pcie8, short pcie16, short ps2, QString caseForm,
                      short ext5_25, short ext3_5, short int3_5, bool integrPsu, int psuPower,
                      QObject *parent = 0):
        QObject(parent), name(name), description(description), chipset(chipset), socket(socket),
        sound(sound), lan(lan), usb2(usb2), usb3(usb3), sata(sata), sata3(sata3), dimm(dimm),
        ram(ram), integrVideo(integrVideo), vga(vga), dvi(dvi), hdmi(hdmi), pcie1(pcie1),
        pcie4(pcie4), pcie8(pcie8), pcie16(pcie16), ps2(ps2), caseForm(caseForm), ext5_25(ext5_25),
        ext3_5(ext3_5), int3_5(int3_5), integrPsu(integrPsu), psuPower(psuPower){}

    QString getName() const {return name;}
    QString getDescription() const {return description;}
    QString getChipset() const {return chipset;}
    int getSocket() const {return socket;}
    QString getSound() const {return sound;}
    QString getLan() const {return lan;}
    short getUsb2() const {return usb2;}
    short getUsb3() const {return usb3;}
    short getSata() const {return sata;}
    short getSata3() const {return sata3;}
    short getDimm() const {return dimm;}
    short getRam() const {return ram;}
    bool getIntegrVideo() const {return integrVideo;}
    bool getVga() const {return vga;}
    bool getDvi() const {return dvi;}
    bool getHdmi() const {return hdmi;}
    short getPcie1() const {return pcie1;}
    short getPcie4() const {return pcie4;}
    short getPcie8() const {return pcie8;}
    short getPcie16() const {return pcie16;}
    short getPs2() const {return ps2;}
    QString getCaseForm() const {return caseForm;}
    short getExt5_25() const {return ext5_25;}
    short getExt3_5() const {return ext3_5;}
    short getInt3_5() const {return int3_5;}
    bool getIntegrPsu() const {return integrPsu;}
    int getPsuPower() const {return psuPower;}

    friend QDataStream &operator >>(QDataStream &stream, Platform* platf);

    ~Platform() {qDebug() << "Удаление платформы:" << this->getName();}

signals:

public slots:

private:
    QString name;
    QString description;
    QString chipset;
    int socket;
    QString sound;
    QString lan;
    short usb2;
    short usb3;
    short sata;
    short sata3;
    short dimm;
    short ram;
    bool integrVideo;
    bool vga;
    bool dvi;
    bool hdmi;
    short pcie1;
    short pcie4;
    short pcie8;
    short pcie16;
    short ps2;
    QString caseForm;
    short ext5_25;
    short ext3_5;
    short int3_5;
    bool integrPsu;
    int psuPower;
};

Q_DECLARE_METATYPE(Platform*)

#endif // PLATFORM_H
