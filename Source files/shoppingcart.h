/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QWidget>
#include <QTreeWidget>
#include "baseheader.h"
#include "PizzaClasses.h"
#include <fstream>
#include <ctime>


class ShoppingCart : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCart(QWidget *parent = 0);
    ~ShoppingCart();
    void AddToCart(Merchandise* m);
    void UpdateSum();
    void DeliveryFee(bool delivery);
    void CreateReceipt(std::ofstream &reciept);
    int GetNumItems();

private:
    QTreeWidget *shoppingList;
    QLabel *sumNumLabel;
    QTreeWidgetItem *deliveryItem;

    // Todo: Transition to Qt's file I/O class
    std::string GetQuantityString(int itemIndex);
    std::string GetNameString(int itemIndex);
    std::string GetPriceString(int itemIndex);
    std::string GetDescriptionString(int itemIndex);
    void ReceiptHeader(std::ofstream &reciept);
    void ReceiptFooter(std::ofstream &reciept);

public slots:
    void DeleteLine();
};

#endif // SHOPPINGCART_H
