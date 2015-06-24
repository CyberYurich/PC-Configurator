#include "mytabwidget.h"

MyTabBar::MyTabBar(QWidget *parent) :
    QTabBar(parent)
{
    setIconSize(QSize(18, 18));
}

QSize MyTabBar::tabSizeHint(int) const
{
    return QSize(160, 30);
}

void MyTabBar::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    for (int index = 0; index < count(); index++)
    {
        QStyleOptionTabV3 tab;
        initStyleOption(&tab, index);
        QIcon tempIcon = tab.icon;
        QString tempText = tab.text;
        tab.icon = QIcon();
        tab.text = QString();
        p.drawControl(QStyle::CE_TabBarTab, tab);
        QPainter painter;
        painter.begin(this);
        QRect tabrect = tabRect(index);
        tabrect.adjust(0, 8, 0, -8);
        painter.drawText(tabrect, Qt::AlignBottom | Qt::AlignHCenter, tempText);
        tempIcon.paint(&painter, 0, tabrect.top(), tab.iconSize.width(), tab.iconSize.height(),
                       Qt::AlignTop | Qt::AlignHCenter);
        painter.end();
    }
}

MyTabWidget::MyTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    TabBar = new MyTabBar(this);
    this->setTabBar(TabBar);
}

MyTabWidget::~MyTabWidget()
{
    delete TabBar;
}
