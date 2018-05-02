/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#include "confirmwindow.h"

ConfirmWindow::ConfirmWindow(CustomerInformation *clientPtr, QWidget *parent)
    : QWidget(parent),clientInfo(clientPtr)
{
    /*
    The confirmwindow is the last window before the order is set. The widget displays the name of the costumer
    and if delivery is chosen it will also display delivery information. This data was set in the deliverywindow.

    This widget consists mainly of QLabels.
    */

    // ----------------------------------------------------------------- //
    // ------------------------- Header labels ------------------------- //
    QLabel *nameLabel = new QLabel(tr("Name"));
    QLabel *phoneLabel = new QLabel(tr("Phone number"));
    QLabel *addressLabel = new QLabel(tr("Delivery address"));
    QLabel *zipLabel = new QLabel(tr("Zip code"));
    QLabel *stateLabel = new QLabel(tr("City/state"));

    name = new QLabel;
    phone = new QLabel;
    address = new QLabel;
    state = new QLabel;
    zip = new QLabel;

    QHBoxLayout *nameRow = new QHBoxLayout;
    nameRow->addWidget(nameLabel);
    nameRow->addWidget(name);

    QHBoxLayout *zipRow = new QHBoxLayout;
    zipRow->addWidget(zipLabel);
    zipRow->addWidget(zip);

    QHBoxLayout *addressRow = new QHBoxLayout;
    addressRow->addWidget(addressLabel);
    addressRow->addWidget(address);

    QHBoxLayout *stateRow = new QHBoxLayout;
    stateRow->addWidget(stateLabel);
    stateRow->addWidget(state);

    QHBoxLayout *phoneRow = new QHBoxLayout;
    phoneRow->addWidget(phoneLabel);
    phoneRow->addWidget(phone);


    // ----------------------------------------------------------------- //
    // -------------------------- Name/phone --------------------------- //
    infoGroup = new QGroupBox;
    QVBoxLayout *infoLayout = new QVBoxLayout;

    infoLayout->addLayout(nameRow);
    infoLayout->addLayout(phoneRow);

    infoGroup->setLayout(infoLayout);
    infoGroup->setFixedSize(400,50);


    // ----------------------------------------------------------------- //
    // ---------------------- Delivery information --------------------- //
    deliveryGroup = new QGroupBox;
    QVBoxLayout *deliveryLayout = new QVBoxLayout;
    deliveryLayout->addLayout(addressRow);
    deliveryLayout->addLayout(stateRow);
    deliveryLayout->addLayout(zipRow);

    deliveryGroup->setLayout(deliveryLayout);
    deliveryGroup->setFixedSize(400,80);


    // ----------------------------------------------------------------- //
    // -------------------------- Main layout -------------------------- //
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(infoGroup);
    mainLayout->addWidget(deliveryGroup);
    setLayout(mainLayout);   
}

void ConfirmWindow::SetCustomerInfo()
{
    // This funtion sets client information on to the user interface:

    name->setText(clientInfo->name);
    phone->setText(clientInfo->number);
    state->setText(clientInfo->state);
    address->setText(clientInfo->address);
    zip->setText(clientInfo->zipCode);

    // Shows deliveryGroup if delivery is chosen hide otherwise:
    clientInfo->delivery?deliveryGroup->show():deliveryGroup->hide();
}













