/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#include "drinkwindow.h"
#include "modelclasses.h"

DrinkWindow::DrinkWindow(ShoppingCart *cartPtr,QWidget *parent) : QWidget(parent),cart(cartPtr)
{
    /*
    This widget will add chosen drink to the shopping cart. It consists of a QListWidget and a QPushButton. The selected item
    on the QListWidget will get added to the shopping cart when the button is pressed.
    */


    // Todo: There is no visual cue that an item has been added to the cart.

    // ----------------------------------------------------------------- //
    // -------------------------- Header label ------------------------- //
    QLabel *header = new QLabel(tr("Select drink"));
    header->setAlignment(Qt::AlignHCenter);
    QFont font;
    font.setPointSize(15);
    header->setFont(font);


    // ----------------------------------------------------------------- //
    // ------------------------ Drink list view ------------------------ //
    drinkListView = new QListView;
    drinkListView->setModel(new DrinkListModel);


    // ----------------------------------------------------------------- //
    // ---------------------- Add to cart button ----------------------- //
    QPushButton *addButton = new QPushButton(tr("Add to basket"));
    connect(addButton,SIGNAL(released()),this,SLOT(AddItemToCart()));


    // ----------------------------------------------------------------- //
    // ------------------------- Main layout --------------------------- //
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *actionLayout = new QVBoxLayout;

    actionLayout->addWidget(addButton);
    mainLayout->addWidget(header);
    mainLayout->addWidget(drinkListView);
    mainLayout->addLayout(actionLayout);

    setLayout(mainLayout);
}
void DrinkWindow::AddItemToCart()
{
    Drink d = drinkListView->model()->data(drinkListView->currentIndex(), Qt::UserRole).value<Drink>();
    cart->AddToCart(&d);
}





















