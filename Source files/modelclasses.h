#ifndef MODELCLASSES_H
#define MODELCLASSES_H

#include <QAbstractListModel>
#include <QObject>
#include "PizzaClasses.h"

// Todo: Make a template out of these


class PizzaSizeListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    PizzaSizeListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};




class PizzaCrustListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    PizzaCrustListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};




class DrinkListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    DrinkListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};


#endif // MODELCLASSES_H
