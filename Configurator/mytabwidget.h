#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QWidget>
#include <QTabBar>
#include <QTabWidget>
#include <QStylePainter>
#include <QStyleOptionTabV3>

class MyTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit MyTabBar(QWidget* parent = 0);

protected:
    QSize tabSizeHint(int) const;
    void paintEvent(QPaintEvent *);
};

class MyTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MyTabWidget(QWidget *parent = 0);
    ~MyTabWidget();
private:
    MyTabBar* TabBar;
};

#endif // MYTABWIDGET_H

