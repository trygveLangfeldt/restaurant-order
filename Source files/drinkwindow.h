
/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#ifndef DRINKWINDOW_H
#define DRINKWINDOW_H

#include <QWidget>
#include <QListWidget>
#include "baseheader.h"
#include "shoppingcart.h"

class DrinkWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DrinkWindow(ShoppingCart *cartPtr, QWidget *parent = 0);

private:
    ShoppingCart *cart;
    QComboBox *numComboBox;
    QListView *drinkListView;

public slots:
    void AddItemToCart();
};

#endif // DRINKWINDOW_H
