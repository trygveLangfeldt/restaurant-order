
/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#include "deliverywindow.h"
#include <fstream>
#include <QDebug>
#include <QFile>
#include <QDir>

using namespace std;


DeliveryWindow::DeliveryWindow(QWidget *parent) : QWidget(parent)
{
    /*
    This widget contains the data wheter the costumer wants to take away og get home delivery. It consists
    mainly of QLabels, QLineEdits and QPushButtons. A QGroupBox is also chosen so the delivery inputs gets hidden
    if takeaway is chosen.
    */


    // ----------------------------------------------------------------- //
    // ------------------- Delivery/pickup selection ------------------- //
    QLabel *header = new QLabel(tr("Choose home delivery or pickup at restaurant"));
    QFont font;
    font.setPointSize(15);
    header->setFont(font);

    QPushButton *deliveryButton = new QPushButton(tr("Home delivery"));
    QPushButton *pickUpButton = new QPushButton(tr("Pickup at restaurant"));

    pickUpButton->setFixedSize(130, 30);
    deliveryButton->setFixedSize(100, 30);

    connect(deliveryButton, SIGNAL(released()), this, SLOT(HomeDelivery()));
    connect(pickUpButton, SIGNAL(released()), this, SLOT(PickUp()));


    // ----------------------------------------------------------------- //
    // --------------------- Contact details input --------------------- //
    QGroupBox *infoGroup = new QGroupBox(tr("Name and phone number"));
    QVBoxLayout *infoLayout = new QVBoxLayout;

    QLabel *nameLabel = new QLabel(tr("Name"));
    QLabel *phoneLabel = new QLabel(tr("Phone"));

    nameLine = new QLineEdit;
    nameLine->setFixedSize(300, 20);
    phoneLine = new QLineEdit;
    phoneLine->setFixedSize(300, 20);

    // Limit input to numeric characters only (also, phone numbers have eight digits)
    QIntValidator* numberValidator = new QIntValidator(10000000, 99999999, this);
    phoneLine->setValidator(numberValidator);

    QHBoxLayout *nameRow = new QHBoxLayout;
    nameRow->addWidget(nameLabel);
    nameRow->addStretch(1);
    nameRow->addWidget(nameLine);

    QHBoxLayout *phoneRow = new QHBoxLayout;
    phoneRow->addWidget(phoneLabel);
    phoneRow->addStretch(1);
    phoneRow->addWidget(phoneLine);

    infoLayout->addLayout(nameRow);
    infoLayout->addLayout(phoneRow);
    infoGroup->setLayout(infoLayout);


    // ----------------------------------------------------------------- //
    // ------------------------- Address input ------------------------- //
    addressGroup = new QGroupBox(tr("Delivery details"));
    QVBoxLayout *addressLayout = new QVBoxLayout;

    QLabel *adressLabel = new QLabel(tr("Address"));
    QLabel *zipCodeLabel = new QLabel(tr("Zip code"));
    QLabel *stateLabel = new QLabel(tr("City/state"));

    addressLine = new QLineEdit;
    addressLine->setFixedSize(300, 20);

    zipCodeLine = new QLineEdit;
    zipCodeLine->setFixedSize(300, 20);

    // Limit input to numeric characters only (also, zip codes have no more than four digits)
    QIntValidator* zipCodeValidator = new QIntValidator(0, 9999, this);
    zipCodeLine->setValidator(zipCodeValidator);

    stateLine = new QLineEdit;
    stateLine->setFixedSize(300, 20);
    stateLine->setEnabled(false);

    QHBoxLayout *addressRow = new QHBoxLayout;
    addressRow->addWidget(adressLabel);
    addressRow->addStretch();
    addressRow->addWidget(addressLine);

    QHBoxLayout *zipCodeRow = new QHBoxLayout;
    zipCodeRow->addWidget(zipCodeLabel);
    zipCodeRow->addStretch();
    zipCodeRow->addWidget(zipCodeLine);

    QHBoxLayout *stateRow = new QHBoxLayout;
    stateRow->addWidget(stateLabel);
    stateRow->addStretch();
    stateRow->addWidget(stateLine);

    addressLayout->addLayout(addressRow);
    addressLayout->addLayout(zipCodeRow);
    addressLayout->addLayout(stateRow);

    addressGroup->setLayout(addressLayout);
    addressGroup->hide();



    // ----------------------------------------------------------------- //
    // -------------------- Delivery/pickup display -------------------- //
    QHBoxLayout *chooseRow = new QHBoxLayout;
    chooseRow->addWidget(deliveryButton);
    chooseRow->addWidget(pickUpButton);

    QHBoxLayout *alternativeRow = new QHBoxLayout;
    QLabel *text = new QLabel(tr("You have chosen: "));
    chosenAlternative = new QLabel(tr(""));
    alternativeRow->addWidget(text);
    alternativeRow->addWidget(chosenAlternative);


    // ----------------------------------------------------------------- //
    // -------------------------- Main layout -------------------------- //
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(header);
    mainLayout->addLayout(chooseRow);
    mainLayout->addWidget(infoGroup);
    mainLayout->addWidget(addressGroup);
    mainLayout->addLayout(alternativeRow);

    mainLayout->setAlignment(header,Qt::AlignTop);
    mainLayout->setAlignment(chooseRow,Qt::AlignLeft);
    setLayout(mainLayout);

    // Delivery/pickup selection defaults to pickup:
    PickUp();

    // Load zip code/city combinations
    AllocateZipCode();

    // Update city/state text when typing something into the zip code editbox
    connect(zipCodeLine, QLineEdit::textChanged,
    [this]
    {
        UpdateCity();
    });
}

QString DeliveryWindow::GetName()
{
    return nameLine->text();
}

QString DeliveryWindow::GetPhone()
{
    return phoneLine->text();
}

QString DeliveryWindow::GetAddress()
{
    return addressLine->text();
}

QString DeliveryWindow::GetZip()
{
    return zipCodeLine->text();
}

QString DeliveryWindow::GetState()
{
    return stateLine->text();
}

void DeliveryWindow::UpdateCity()
{
    // Updates city/state, based on the entered zip code.
    auto it = zipCode.find(GetZip());

    if (it != zipCode.end())
    {
        stateLine->setText(it.value());
    }
    else
    {
        stateLine->setText("");
    }
}

void DeliveryWindow::ClearText()
{
    nameLine->clear();
    phoneLine->clear();
    addressLine->clear();
    stateLine->clear();
    zipCodeLine->clear();
}

void DeliveryWindow::AllocateZipCode()
{
    // Parses the file containing the zip code/city combinations
    // and loads it into memory.

    QDir path = QDir::currentPath();
    QFile file(path.absoluteFilePath("zipcodes.txt"));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open zip code file.";
        return;
    }

    QTextStream input(&file);
    while (!input.atEnd())
    {
        QString line = input.readLine();
        QStringList list = line.split('\t');

        zipCode[list.at(0)] = list.at(1);
    }

    file.close();
}

bool DeliveryWindow::IsDelivery()
{
    return delivery;
}

void DeliveryWindow::PickUp()
{
    delivery = false;
    addressGroup->hide();
    chosenAlternative->setText(tr("Pickup at restaurant"));
}

void DeliveryWindow::HomeDelivery()
{
    delivery = true;
    addressGroup->show();
    chosenAlternative->setText(tr("Home delivery"));
}














