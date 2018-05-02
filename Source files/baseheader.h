#ifndef BASEHEADER_H
#define BASEHEADER_H
/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <iostream>


struct CustomerInformation {
    // Data structure for handling customer information

    QString name;
    QString number;
    QString address;
    QString zipCode;
    QString state;
    bool delivery;

    bool CheckNumber()
    {
        for (int i = 0; i < number.size(); i++)
        {
            if (!number[i].isDigit() && !number[i].isSpace())
            {
                return false;
            }
        }

        return true;
    }

    bool CheckZipCode()
    {
        for (int i = 0; i < zipCode.size(); ++i)
        {
            if (!zipCode[i].isDigit() && !zipCode[i].isSpace())
            {
                return false;
            }
        }

        return true;
    }

    bool IsDataValid()
    {
        return true;

        QString s = "Invalid input";
        bool b = true;

        if (name.isEmpty()){name = s; b = false;}
        if (!CheckNumber()){number = s; b = false;}

        if (delivery) {
            if (address.isEmpty()){address = s; b = false;}
            if (!CheckZipCode()) {zipCode = s; b = false;}
            if (state.isEmpty()){state = s; b = false;}
        }

        return b;
    }
};



#endif // BASEHEADER_H


















