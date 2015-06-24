#ifndef MYDELEGATES_H
#define MYDELEGATES_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QSpinBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QList>

class NoEditorDelegate : public QStyledItemDelegate
{
public:
    NoEditorDelegate(QObject *parent):
        QStyledItemDelegate(parent){}

    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)

        return NULL;
    }
};

class MyDoubleSpinboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MyDoubleSpinboxDelegate (QObject *parent = 0):
        QStyledItemDelegate(parent){}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

};

class MySpinboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MySpinboxDelegate (QObject *parent = 0):
        QStyledItemDelegate(parent){}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

};

class MyComboboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MyComboboxDelegate (QStringList list, QObject *parent = 0):
        QStyledItemDelegate(parent), list(list){}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
private:
    QStringList list;
};

#endif // MYDELEGATES_H
