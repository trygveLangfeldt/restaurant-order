/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#include "placeordermenu.h"
#include <QApplication>



/*
 * Readme:
 * Build the project with Qt creator, and place the folder named "Paste contents in build folder"
 * in the build folder created, in my case: "D:\Qt Projects\build-PizzaOrder-Desktop_Qt_5_10_0_MinGW_32bit-Debug")
 *
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlaceOrderMenu w;
    w.show();

    return a.exec();
}
