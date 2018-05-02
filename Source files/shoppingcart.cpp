/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#include "shoppingcart.h"
#include "PizzaClasses.h"
#include <iomanip>
#include <iostream>

using namespace  std;


ShoppingCart::ShoppingCart(QWidget *parent) : QWidget(parent)
{
    /*
    This widget contains all the chosen products in a QTreeWidget. The QTreeWidget consists of three coloumns,
    one for number of elements, description and total price(elementsxsingle price). Its also possible to delete
    an Item, the only exeption is if the costumer
    */


    // ----------------------------------------------------------------- //
    // ------------------- Shopping list basic setup ------------------- //
    shoppingList = new QTreeWidget;
    deliveryItem = new QTreeWidgetItem;
    deliveryItem->setText(0, "1");
    deliveryItem->setText(1, "Delivery charge");

    // 50 is the default delivery charge amount:
    deliveryItem->setText(2, "50");


    // ----------------------------------------------------------------- //
    // ----------------------- Display widgets ------------------------- //
    QPushButton *deleteButton = new QPushButton(tr("Remove from basket"));
    QLabel *sumLabel = new QLabel(tr("Total price"));
    sumNumLabel = new QLabel(tr("0"));
    QHBoxLayout *sumRow = new QHBoxLayout;
    sumRow->addWidget(sumLabel);
    sumRow->addWidget(sumNumLabel);


    // ----------------------------------------------------------------- //
    // ----------------- Shopping list layout settings ----------------- //
    shoppingList->setColumnCount(3);
    shoppingList->setHeaderHidden(true);
    shoppingList->setColumnWidth(0, 50);
    shoppingList->setColumnWidth(1, 300);
    shoppingList->setColumnWidth(2, 50);


    // ----------------------------------------------------------------- //
    // -------------------------- Main layout -------------------------- //
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(shoppingList);
    mainLayout->addLayout(sumRow);
    mainLayout->addWidget(deleteButton);
    mainLayout->setAlignment(deleteButton, Qt::AlignRight);
    connect(deleteButton, SIGNAL(released()), this, SLOT(DeleteLine()));
    setLayout(mainLayout);
}

ShoppingCart::~ShoppingCart()
{
    delete shoppingList;
    delete sumNumLabel;
}

void ShoppingCart::AddToCart(Merchandise* m)
{
    QTreeWidgetItem *newItem = new QTreeWidgetItem;
    newItem->setText(0, m->GetQuantityText());
    newItem->setText(1, m->GetNameText());
    newItem->setText(2, m->GetPriceText());
    newItem->setText(3, m->GetDescriptionText());
    shoppingList->addTopLevelItem(newItem);
    UpdateSum();
}

void ShoppingCart::UpdateSum()
{
    // Updates sum on the shopping cart
    QString amount;
    int sum = 0;

    for(int i = 0; i < shoppingList->topLevelItemCount(); i++)
    {
         amount = shoppingList->topLevelItem(i)->text(2);
         sum += amount.toInt();
    }

    sumNumLabel->setText(QString::number(sum));
}

void ShoppingCart::DeliveryFee(bool delivery)
{
    //This function adds the delivery fee to the shopping list if delivery is chosen
    if (delivery)
    {
        if (deliveryItem == NULL)
        {
            deliveryItem = new QTreeWidgetItem;//If deliveryItem is not initialized the function will make a new Item
            deliveryItem->setText(0,"1");
            deliveryItem->setText(1,"Delivery charge");
            deliveryItem->setText(2,"50");
        }

        shoppingList->addTopLevelItem(deliveryItem);
    }
    else
    {
        delete deliveryItem;
        deliveryItem = NULL;
    }
}

void ShoppingCart::CreateReceipt(ofstream &receipt)
{
    // Creates a receipt using the items from shoppingList(QTreeWidget)
    if (receipt.is_open())
    {
        ReceiptHeader(receipt);

        for (int i = 0; i < shoppingList->topLevelItemCount(); i++)
        {
            receipt << setw(8) << left << GetQuantityString(i)
                    << setw(40) << left << GetNameString(i)
                    << setw(7) << right << GetPriceString(i)
                       // 13% is the tax on food items:
                    << setw(7) << right << "13%"
                    << "\n"
                    << GetDescriptionString(i)
                    << "\n";
        }

        ReceiptFooter(receipt);
    }
    else
    {
        qDebug() << "Could not open file.";
    }
}

int ShoppingCart::GetNumItems()
{
    return shoppingList->topLevelItemCount();
}

string ShoppingCart::GetQuantityString(int itemIndex)
{
    return shoppingList->topLevelItem(itemIndex)->text(0).toStdString().append(" x");
}

string ShoppingCart::GetNameString(int itemIndex)
{
    return shoppingList->topLevelItem(itemIndex)->text(1).toStdString();
}

string ShoppingCart::GetPriceString(int itemIndex)
{
    return shoppingList->topLevelItem(itemIndex)->text(2).toStdString().append("kr");
}

string ShoppingCart::GetDescriptionString(int itemIndex)
{
    std::string description = shoppingList->topLevelItem(itemIndex)->text(3).toStdString();
    return description;
}

void ShoppingCart::ReceiptHeader(ofstream &receipt)
{
    time_t time = std::time(0);

    // Adjust two hours forward to account for time zone (yes, it's a hack).
    time = time + 2 * 60 * 60;

    // Todo: Generate actual order numbers.
    // 35 was picked at random to temporarily represent the order number:
    unsigned int orderNumber = 35;

    receipt << "***********************************************************************\n";

    receipt << "                                                                       \n";

    receipt << "                          Paul's Pizza Place                           \n";

    receipt << "                           Phone: 450 450 00                           \n";

    receipt << "                          Address: Mordor 10                           \n";

    receipt << "                          Org.no: 111 222 333                          \n";

    receipt << "                                                                       \n";

    receipt << "***********************************************************************\n";

    // These numbers worked out, so we used them.
    receipt << setw(54) << left << QString("Order number: ").append(QString::number(orderNumber)).toStdString()

            << setw(71) << right << std::put_time(std::gmtime(&time), "%c") <<"\n\n\n\n";

    receipt << setw(8) << left << "Qty" << setw(40) << left << "Item" << setw(7) << right << "Price" << setw(7) << right << "Tax" << "\n";

    receipt << "-----------------------------------------------------------------------\n";

}

void ShoppingCart::ReceiptFooter(ofstream &receipt)
{
    // 0.13 = 13% is the tax on food items
    static double tax  = 0.13;
    receipt << "\n\n\n";

    receipt << "-----------------------------------------------------------------------\n\n";

    receipt << "\t\t\t\t\t\tTotal\n";

    receipt << "\t\t\t\t\t\t-------------\n";

    receipt << "\t\t\t\t\t\t" << sumNumLabel->text().toStdString() << "\n\n";

    receipt << "\t\t\t\t\t\tSubtotal\n";

    receipt << "\t\t\t\t\t\t-------------\n";

    receipt << "\t\t\t\t\t\t" << QString::number(sumNumLabel->text().toInt() - sumNumLabel->text().toInt()*tax).toStdString() << "\n\n";

    receipt << "\t\t\t\t\t\tTax\n";

    receipt << "\t\t\t\t\t\t-------------\n";

    receipt << "\t\t\t\t\t\t" << QString::number(sumNumLabel->text().toInt()*tax).toStdString();

    receipt << "\n\n\n";

    receipt << "***********************************************************************\n";

    receipt << "                       Thank you for your purchase                     \n";

    receipt << "                            Enjoy your meal!                           \n";

    receipt << "***********************************************************************\n\n";
}


void ShoppingCart::DeleteLine()
{
    if (shoppingList->currentItem() != deliveryItem)
    {
        delete shoppingList->currentItem();
    }

    UpdateSum();
}

