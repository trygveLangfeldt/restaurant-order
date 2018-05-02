
/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#ifndef DELIVERYWINDOW_H
#define DELIVERYWINDOW_H

#include <QWidget>
#include <baseheader.h>
#include "QGroupBox"
#include "QLineEdit"
#include "shoppingcart.h"


class DeliveryWindow : public QWidget
{
    Q_OBJECT

public:
    DeliveryWindow(QWidget *parent = 0);
    QString GetName();
    QString GetPhone();
    QString GetAddress();
    QString GetZip();
    QString GetState();
    void UpdateCity();
    void ClearText();
    void AllocateZipCode();
    bool IsDelivery();

private:
    QMap<QString, QString> zipCode;
    QLabel *chosenAlternative;
    QGroupBox *addressGroup;
    QLineEdit *nameLine;
    QLineEdit *phoneLine;
    QLineEdit *addressLine;
    QLineEdit *zipCodeLine;
    QLineEdit *stateLine;
    bool delivery;

private slots:
    void HomeDelivery();
    void PickUp();
};

#endif // DELIVERYWINDOW_H
