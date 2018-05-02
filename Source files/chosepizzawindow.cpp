
/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#include "chosepizzawindow.h"
#include "PizzaClasses.h"
#include <iostream>
#include <QDebug>

ChoosePizzaWindow::ChoosePizzaWindow(ShoppingCart *cartPtr, QWidget *parent) : QWidget(parent),cart(cartPtr)
{
    /*
     This widget displays buttons with the standard pizza types of Pauls Pizza house. By clicking a button
     the pizza window will pop open. The widget consists mainly of QPushButtons and the header label.
    */

    QVBoxLayout *mainLayout = new QVBoxLayout;


    // ----------------------------------------------------------------- //
    // -------------------------- Header label ------------------------- //
    QLabel *header = new QLabel(tr("Select a pizza"));
    header->setAlignment(Qt::AlignHCenter);
    QFont font;
    font.setPointSize(22);
    header->setFont(font);
    mainLayout->addWidget(header);


    // ----------------------------------------------------------------- //
    // -------------------------- PushButtons -------------------------- //
    for (int i = 0; i < Pizza::GetPizzaList().size(); ++i)
    {
        QPushButton *button = new QPushButton(Pizza::GetPizzaList()[i].GetName());
        button->setFont(QFont("Sans Serif", 14));
        button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        connect(button, QPushButton::released, [i, this] {Pizza::GetPizzaList()[i].Select(); ShowWindow();});
        mainLayout->addWidget(button);
    }

    setLayout(mainLayout);
}

void ChoosePizzaWindow::ShowWindow(){
    PizzaWindow *addPizza = new PizzaWindow(cart);
    addPizza->show();
}
