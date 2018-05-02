/*
 @author: Trygve Sigurdsson Langfeldt, s305106
 */
#include "placeordermenu.h"
#include "windows.h"
#include "PizzaClasses.h"
#include <fstream>
#include <string>

void PlaceOrderMenu::SetupData()
{
    // -------------------------- Setup stuff -------------------------- //
    // ----------------------------------------------------------------- //

    // Creates the information that makes up the menu items.
    // Numbers used here are fairly arbitrary, and represents dimensions
    // such as price and size.

    // Non-components
    auto salt = Ingredient::AddNew(tr("Salt"), Ingredient::NON_COMPONENT);
    auto yeast = Ingredient::AddNew(tr("Yeast"), Ingredient::NON_COMPONENT);

    // Flours
    auto riceFlour = Ingredient::AddNew(tr("Rice flour"), Ingredient::FLOUR);
    auto wheatFlour = Ingredient::AddNew(tr("Wheat flour"), Ingredient::FLOUR);

    // Pizza crusts
    auto italian = PizzaCrust::AddNew(tr("Italian"), 1);
    auto american = PizzaCrust::AddNew(tr("American"), 1.3);
    auto hotPocket = PizzaCrust::AddNew(tr("Hot Pocket"), 1.2);

    // Pizza sizes
    auto small = PizzaSize::AddNew(tr("Small"), 0.7);
    auto medium = PizzaSize::AddNew(tr("Medium"), 1);
    auto large = PizzaSize::AddNew(tr("Large"), 1.3);

    // Toppings
    auto ham = Ingredient::AddNew(tr("Ham"), 20, Ingredient::TOPPING, Ingredient::MEAT);
    auto beef = Ingredient::AddNew(tr("Beef"), 20, Ingredient::TOPPING, Ingredient::MEAT);
    auto mince = Ingredient::AddNew(tr("Mince"), 20, Ingredient::TOPPING, Ingredient::MEAT);
    auto bacon = Ingredient::AddNew(tr("Bacon"), 20, Ingredient::TOPPING, Ingredient::MEAT);
    auto chicken = Ingredient::AddNew(tr("Chicken"), 20, Ingredient::TOPPING, Ingredient::MEAT);
    auto pepperoni = Ingredient::AddNew(tr("Pepperoni"), 20, Ingredient::TOPPING, Ingredient::MEAT);

    auto tacoMarinade = Ingredient::AddNew(tr("Taco marinade"), 4, Ingredient::TOPPING, Ingredient::MARINADE);
    auto kebabMarinade = Ingredient::AddNew(tr("Kebab marinade"), 4, Ingredient::TOPPING, Ingredient::MARINADE);
    auto tandooriMarinade = Ingredient::AddNew(tr("Tandoori marinade"), 4, Ingredient::TOPPING, Ingredient::MARINADE);

    auto corn = Ingredient::AddNew(tr("Corn"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);
    auto onions = Ingredient::AddNew(tr("Onions"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);
    auto tomatoes = Ingredient::AddNew(tr("Tomatoes"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);
    auto jalapenos = Ingredient::AddNew(tr("Jalapenos"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);
    auto mushrooms = Ingredient::AddNew(tr("Mushrooms"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);
    auto pineapples = Ingredient::AddNew(tr("Pineapples"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);
    auto blackOlives = Ingredient::AddNew(tr("Black olives"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);
    auto bellPeppers = Ingredient::AddNew(tr("Bell peppers"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);
    auto tortillaChips = Ingredient::AddNew(tr("Tortilla chips"), 10, Ingredient::TOPPING, Ingredient::VEGETABLE);

    auto cheddar = Ingredient::AddNew(tr("Cheddar"), 20, Ingredient::TOPPING, Ingredient::CHEESE);
    auto mozzarella = Ingredient::AddNew(tr("Mozzarella"), 20, Ingredient::TOPPING, Ingredient::CHEESE);

    auto basil = Ingredient::AddNew(tr("Basil"), Ingredient::TOPPING, Ingredient::GARNISH);
    auto chili = Ingredient::AddNew(tr("Chili"), Ingredient::TOPPING, Ingredient::GARNISH);
    auto oregano = Ingredient::AddNew(tr("Oregano"), Ingredient::TOPPING, Ingredient::GARNISH);
    auto garlicParmesanOil = Ingredient::AddNew(tr("Garlic/parmesan oil"), 0, Ingredient::TOPPING, Ingredient::GARNISH);

    // Drinks
    auto urge = Drink::AddNew(tr("Urge"), 19);
    auto cocaCola = Drink::AddNew(tr("Coca Cola"), 20);
    auto gingerAle = Drink::AddNew(tr("Ginger ale"), 21);


    // Default Margherita
    Pizza& margherita = Pizza::AddNew(tr("Margherita"));
    margherita.SetSize(medium);
    margherita.SetCrust(wheatFlour, italian);
    // Todo: Non-optional ingredients should probably use a different function
    margherita.AddComponent(yeast);
    margherita.AddComponent(salt);
    margherita.AddComponent(mozzarella);
    margherita.AddComponent(basil);
    margherita.AddComponent(garlicParmesanOil);


    // Default Happy Chicken
    Pizza& happyChicken = Pizza::AddNew(tr("Happy Chicken"));
    happyChicken.SetSize(medium);
    happyChicken.SetCrust(wheatFlour, italian);
    happyChicken.AddComponent(yeast);
    happyChicken.AddComponent(salt);
    happyChicken.AddComponent(mozzarella);
    happyChicken.AddComponent(chicken);
    happyChicken.AddComponent(jalapenos);
    happyChicken.AddComponent(onions);
    happyChicken.AddComponent(tacoMarinade);


    // Default Kebab Pizza
    Pizza& kebabPizza = Pizza::AddNew(tr("Kebab Pizza"));
    kebabPizza.SetSize(medium);
    kebabPizza.SetCrust(wheatFlour, american);
    kebabPizza.AddComponent(yeast);
    kebabPizza.AddComponent(salt);
    kebabPizza.AddComponent(mozzarella);
    kebabPizza.AddComponent(chicken);
    kebabPizza.AddComponent(bellPeppers);
    kebabPizza.AddComponent(onions);
    kebabPizza.AddComponent(chili);
    kebabPizza.AddComponent(kebabMarinade);


    // Default Cat Free
    Pizza& catFreePizza = Pizza::AddNew(tr("Cat Free Pizza"));
    catFreePizza.SetSize(medium);
    catFreePizza.SetCrust(wheatFlour, hotPocket);
    catFreePizza.AddComponent(yeast);
    catFreePizza.AddComponent(salt);
    catFreePizza.AddComponent(mozzarella);
    catFreePizza.AddComponent(cheddar);
    catFreePizza.AddComponent(beef);
    catFreePizza.AddComponent(pineapples);
    catFreePizza.AddComponent(tomatoes);
    catFreePizza.AddComponent(oregano);
    catFreePizza.AddComponent(blackOlives);


    // Default Cow Hugger's
    Pizza& cowHuggersPizza = Pizza::AddNew(tr("Cow Hugger's Pizza"));
    cowHuggersPizza.SetSize(medium);
    cowHuggersPizza.SetCrust(wheatFlour, italian);
    cowHuggersPizza.AddComponent(yeast);
    cowHuggersPizza.AddComponent(salt);
    cowHuggersPizza.AddComponent(pineapples);
    cowHuggersPizza.AddComponent(mushrooms);
    cowHuggersPizza.AddComponent(corn);
    cowHuggersPizza.AddComponent(tomatoes);


    // Default Tree Hugger's
    Pizza& treeHuggersPizza = Pizza::AddNew(tr("Tree Hugger's Pizza"));
    treeHuggersPizza.SetSize(medium);
    treeHuggersPizza.SetCrust(wheatFlour, italian);
    treeHuggersPizza.AddComponent(yeast);
    treeHuggersPizza.AddComponent(salt);
    treeHuggersPizza.AddComponent(beef);
    treeHuggersPizza.AddComponent(ham);
    treeHuggersPizza.AddComponent(pepperoni);
    treeHuggersPizza.AddComponent(mince);
    treeHuggersPizza.AddComponent(chicken);
    treeHuggersPizza.AddComponent(bacon);
    treeHuggersPizza.AddComponent(tandooriMarinade);
}


PlaceOrderMenu::PlaceOrderMenu(QWidget *parent)
    : QWidget(parent)
{
    /*
    PlaceOrderMenu is the framework of this application. It contains all of the windows in a QStackedWidget
    and has the ability to change windows. There are a few exeptions though, the shoppingCart(cart) is always
    available for the user as well as the nextButton, prevButton and the cartButton. The widget has three widgets/layouts
    topRow, pageLayout, cart and buttonsRow.
    */


    // Initialize the menu items
    SetupData();

    // ----------------------------------------------------------------- //
    // ---------------------- Create page widgets ---------------------- //
    customerInfo = new CustomerInformation;
    cart = new ShoppingCart;
    deliveryPage = new DeliveryWindow(cart);
    deliveryPage->AllocateZipCode();
    pizzaPage = new ChoosePizzaWindow(cart);
    drinkPage = new DrinkWindow(cart);
    confirmPage = new ConfirmWindow(customerInfo);
    cart->hide();


    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(deliveryPage);
    stackedWidget->addWidget(pizzaPage);
    stackedWidget->addWidget(drinkPage);
    stackedWidget->addWidget(confirmPage);


    // ----------------------------------------------------------------- //
    // ---------------------- Navigation buttons ----------------------- //
    nextButton = new QPushButton(tr("Next"));
    prevButton = new QPushButton(tr("Back"));

    prevButton->setEnabled(false);
    connect(nextButton, SIGNAL(released()), this, SLOT(NextPage()));
    connect(prevButton, SIGNAL(released()), this, SLOT(PrevPage()));


    // ----------------------------------------------------------------- //
    // --------------------- Shopping cart button ---------------------- //
    cartButton = new QPushButton(tr("Shopping cart"));
    QDir cartunoPath = QDir::currentPath();
    cartunoPath.cd("img");
    // Todo: File path constant
    cartButton->setIcon(QIcon(QPixmap(cartunoPath.filePath("cartuno.png"))));
    cartButton->setIconSize(QSize(15, 15));
    cartButton->setCheckable(true);
    connect(cartButton, SIGNAL(released()), this, SLOT(ShowShoppingCart()));


    // ----------------------------------------------------------------- //
    // ------------------ Navigation buttons continued ----------------- //
    QHBoxLayout * topRowLayout = new QHBoxLayout;
    topRowLayout->addWidget(cartButton);
    topRowLayout->setAlignment(cartButton, Qt::AlignRight);

    QHBoxLayout *pageLayout = new QHBoxLayout;
    pageLayout->addWidget(stackedWidget);

    QHBoxLayout *buttonsRow = new QHBoxLayout;
    buttonsRow->addWidget(prevButton);
    buttonsRow->addStretch(1);
    buttonsRow->addWidget(nextButton);


    // ----------------------------------------------------------------- //
    // ------------------------- Main layout --------------------------- //
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topRowLayout);
    mainLayout->addLayout(pageLayout);
    mainLayout->addWidget(cart);
    mainLayout->addLayout(buttonsRow);

    QDir pizzaLogo2Path = QDir::currentPath();
    pizzaLogo2Path.cd("img");
    // Todo: File path constant
    // Todo: Ensure image files are in the proper location after installing
    // Sets the window Icon and size of widget:
    this->setWindowIcon(QIcon(QPixmap(pizzaLogo2Path.filePath("pizzaLogo2.png"))));
    this->setFixedSize(500, 600);
    setLayout(mainLayout);
}

PlaceOrderMenu::~PlaceOrderMenu()
{

}

void PlaceOrderMenu::EnterLastWindow()
{
    // This funciton is activated when entering the last window.
    // It handles and displays data as well as changing the user interface.

    connect(nextButton, SIGNAL(released()), this, SLOT(ConfirmOrder()));
    lastWindow = true;
    cartButton->hide();
    cart->show();

    // Get data from delivery page:
    customerInfo->name = deliveryPage->GetName();
    customerInfo->number = deliveryPage->GetPhone();
    customerInfo->delivery = deliveryPage->IsDelivery();
    customerInfo->zipCode = deliveryPage->GetZip();
    customerInfo->address = deliveryPage->GetAddress();
    customerInfo->state = deliveryPage->GetZip();

    if (customerInfo->IsDataValid() && cart->GetNumItems() > 0)
    {
        nextButton->setEnabled(true);
    }
    else
    {
        nextButton->setEnabled(false);
    }

    // Add the delivery fee to the cart:
    cart->DeliveryFee(customerInfo->delivery);

    // Display customer info:
    confirmPage->SetCustomerInfo();
    nextButton->setText(tr("Confirm order"));
}

void PlaceOrderMenu::ExitLastWindow()
{
    // This function sets the user interface back to the original settings if the
    // customer want to go back and change something in the order:
    disconnect(nextButton, SIGNAL(released()), this, SLOT(ConfirmOrder()));
    lastWindow = false;

    cartButton->show();
    cart->hide();
    nextButton->setText(tr("Next"));
}

void PlaceOrderMenu::NextPage()
{
    stackedWidget->setCurrentIndex(stackedWidget->currentIndex() + 1);

    if (stackedWidget->currentIndex() == stackedWidget->count() - 1)
    {
        EnterLastWindow();
    }
    else if (stackedWidget->currentIndex() != 0)
    {
        prevButton->setEnabled(true);
    }
}

void PlaceOrderMenu::PrevPage()
{
    // Sets respective buttons inactive or active if the currentwindow is the first or last:
    stackedWidget->setCurrentIndex(stackedWidget->currentIndex() - 1);

    if (lastWindow)
    {
        nextButton->setEnabled(true);
        ExitLastWindow();
    }
}

void PlaceOrderMenu::ShowShoppingCart()
{
     cartButton->isChecked() ? cart->show() : cart->hide();
}

void PlaceOrderMenu::ConfirmOrder(){

    // This function gather all data and creates a receipt. It also deletes the client's
    // data allow a new customer to place an order, and sets the window back to the
    // first page (deliveryPage).

    QString fName = customerInfo->name;
    QString linkToFile = QDir::currentPath();
    linkToFile.append("/receipts");
    QDir dir = linkToFile;

    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    linkToFile = dir.absolutePath();

    // Sets current directory to chosen one, this way you can gather all of your receipts:
    SetCurrentDirectoryA(linkToFile.toStdString().c_str());

    // Data handling for later:
    fName.append(".txt");
    std::ofstream receipt;
    receipt.open(fName.toStdString().c_str());

    // Just an empty statement so the CreateReceipt function works
    receipt << "";
    cart->CreateReceipt(receipt);
    //receipt.close();
    linkToFile.append("/");

    // Data handling so the function knows which file to open:
    linkToFile.append(fName);
    ShellExecuteA(NULL, "open", linkToFile.toStdString().c_str() , NULL, NULL, SW_SHOW);

    // Delete old client data
    delete customerInfo;
    delete cart;

    // Create blank ShoppingCart and CustomerInformation
    cart = new ShoppingCart;
    customerInfo = new CustomerInformation;

    // Inserts cart at right position:
    mainLayout->insertWidget(mainLayout->count()-1,cart);
    ExitLastWindow();
    deliveryPage->ClearText();

    // Goes to first page(deliveryWindow):
    stackedWidget->setCurrentIndex(0);

    exit(0);
}


















