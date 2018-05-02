/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#ifndef PLACEORDERMENU_H
#define PLACEORDERMENU_H


#include <QWidget>
#include <QStackedWidget>
#include "baseheader.h"
#include "deliverywindow.h"
#include "chosepizzawindow.h"
#include "shoppingcart.h"
#include "drinkwindow.h"
#include "confirmwindow.h"


class PlaceOrderMenu : public QWidget
{
    Q_OBJECT

public:
    PlaceOrderMenu(QWidget *parent = 0);
    ~PlaceOrderMenu();

private:
    QString getState(QString search);
    void EnterLastWindow();
    void ExitLastWindow();
    void SetupData();

    QStackedWidget *stackedWidget;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QPushButton *cartButton;
    QVBoxLayout *mainLayout;
    CustomerInformation *customerInfo;
    DrinkWindow *drinkPage;
    ChoosePizzaWindow *pizzaPage;
    DeliveryWindow *deliveryPage;
    ShoppingCart *cart;
    ConfirmWindow *confirmPage;
    bool lastWindow = false;

private slots:
    void ConfirmOrder();
    void NextPage();
    void PrevPage();
    void ShowShoppingCart();
};

#endif // PLACEORDERMENU_H
