#include "modelclasses.h"
#include "PizzaClasses.h"



// ----------------------------------------------------------------- //
// --------------------------- PizzaSize --------------------------- //
PizzaSizeListModel::PizzaSizeListModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

int PizzaSizeListModel::rowCount(const QModelIndex &parent) const
{
    return PizzaSize::GetPizzaSizeList().size();
}

QVariant PizzaSizeListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= PizzaSize::GetPizzaSizeList().size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return PizzaSize::GetPizzaSizeList()[index.row()].GetNameAndDiameterString();
    else if (role == Qt::UserRole)
    {
        QVariant var;
        var.setValue(PizzaSize::GetPizzaSizeList()[index.row()]);
        return var;
    }
    else
        return QVariant();
}





// ----------------------------------------------------------------- //
// ------------------------- Pizza Crust --------------------------- //
PizzaCrustListModel::PizzaCrustListModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

int PizzaCrustListModel::rowCount(const QModelIndex &parent) const
{
    return PizzaCrust::GetPizzaCrustList().size();
}

QVariant PizzaCrustListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= PizzaCrust::GetPizzaCrustList().size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return PizzaCrust::GetPizzaCrustList()[index.row()].GetName();

    else if (role == Qt::UserRole)
    {
        QVariant var;
        var.setValue(PizzaCrust::GetPizzaCrustList()[index.row()]);
        return var;
    }
    else
        return QVariant();
}





// ----------------------------------------------------------------- //
// ----------------------------- Drink ----------------------------- //
DrinkListModel::DrinkListModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

int DrinkListModel::rowCount(const QModelIndex &parent) const
{
    return Drink::GetDrinkList().size();
}

QVariant DrinkListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= Drink::GetDrinkList().size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return Drink::GetDrinkList()[index.row()].GetName();

    else if (role == Qt::UserRole)
    {
        QVariant var;
        var.setValue(Drink::GetDrinkList()[index.row()]);
        return var;
    }
    else
        return QVariant();
}







