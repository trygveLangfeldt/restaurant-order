
/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */

#ifndef CHOSEPIZZAWINDOW_H
#define CHOSEPIZZAWINDOW_H
#include "baseheader.h"
#include "pizzawindow.h"
#include "shoppingcart.h"
#include <QWidget>

class ChoosePizzaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChoosePizzaWindow(ShoppingCart *cartPtr,QWidget *parent = 0);
    void GetPizzaOrder();

private:
    ShoppingCart *cart;
    std::vector<QPushButton*> buttons;
    std::vector<QHBoxLayout*> rows;

public slots:
    void ShowWindow();
};

#endif // CHOSEPIZZAWINDOW_H
