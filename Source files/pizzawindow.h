
/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#ifndef PIZZAWINDOW_H
#define PIZZAWINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QtWidgets>
#include "baseheader.h"
#include "shoppingcart.h"

class PizzaWindow : public QWidget
{
    Q_OBJECT
public:
    PizzaWindow(ShoppingCart *cartPtr, QWidget *parent = 0);
    ~PizzaWindow();

private:
    Pizza pizza;
    int quantity = 1;
    QVBoxLayout *mainLayout;
    ShoppingCart *cart;

    QComboBox *numPizza;
    QComboBox *pizzaSize;
    QComboBox *pizzaCrust;
    QLabel *priceDisplay;
    QLabel *quantityDisplay;
    QGridLayout *ingredientGroup;

private slots:
    void Exit();
    void AddOrder();
    void CalculatePrice();
};

#endif // PIZZAWINDOW_H
