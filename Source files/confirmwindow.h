/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */

#ifndef CONFIRMWINDOW_H
#define CONFIRMWINDOW_H
#include "baseheader.h"
#include <QWidget>
#include <QGroupBox>

class ConfirmWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmWindow(CustomerInformation *clientPtr,QWidget *parent = 0);
    void SetCustomerInfo();

private:
    CustomerInformation *clientInfo;
    QLabel *name;
    QLabel *phone;
    QLabel *address;
    QLabel *state;
    QLabel *zip;
    QGroupBox *infoGroup;
    QGroupBox *deliveryGroup;
};

#endif // CONFIRMWINDOW_H
