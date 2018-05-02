#include "PizzaClasses.h"

using namespace std;







// ----------------------------------------------------------------- //
// -------------------------- Merchandise -------------------------- //

Merchandise::Merchandise()
    :name(""), price(0), quantity(1)
{
}

Merchandise::Merchandise(QString _name, int _price)
    :name(_name), price(_price), quantity(1)
{
}

void Merchandise::SetPrice(int newValue)
{
    price = newValue;
}

int Merchandise::GetPrice()
{
    return price;
}

int Merchandise::GetQuantity()
{
    return quantity;
}

int Merchandise::SetQuantity(int newValue)
{
    quantity = newValue;

    if (quantity > maxQuantity)
        quantity = maxQuantity;
    else if (quantity < minQuantity)
        quantity = minQuantity;

    return quantity;
}

int Merchandise::IncrementQuantity(int increment)
{
    return SetQuantity(quantity + increment);
}

int Merchandise::DecrementQuantity(int decrement)
{
    return SetQuantity(quantity - decrement);
}

Merchandise::~Merchandise()
{
}

QString Merchandise::GetNameText()
{
    return name;
}

QString Merchandise::GetDescriptionText()
{
    return "";
}

QString Merchandise::GetPriceText()
{
    return QString::number(GetPrice());
}

QString Merchandise::GetQuantityText()
{
    return QString::number(GetQuantity());
}






// ----------------------------------------------------------------- //
// -------------------------- PizzaCrust --------------------------- //

QVector<PizzaCrust> PizzaCrust::pizzaCrustList = QVector<PizzaCrust>();

QVector<PizzaCrust>& PizzaCrust::GetPizzaCrustList()
{
    return pizzaCrustList;
}

PizzaCrust PizzaCrust::AddNew(QString _name, double _flourAmountFactor)
{
    PizzaCrust p = PizzaCrust(_name, _flourAmountFactor, pizzaCrustList.size());
    pizzaCrustList.push_back(p);
    return p;
}

double PizzaCrust::GetFlourAmountFactor() const
{
    return flourAmountFactor;
}

QString PizzaCrust::GetName() const
{
    return name;
}

int PizzaCrust::GetId()
{
    return pizzaCrustId;
}

PizzaCrust::PizzaCrust(QString _name, double _flourAmountFactor, int _id)
    : name(_name), pizzaCrustId(_id), flourAmountFactor(_flourAmountFactor)
{
}

PizzaCrust::PizzaCrust()
    : name(""), pizzaCrustId(-1), flourAmountFactor(0)
{
}







// ----------------------------------------------------------------- //
// --------------------------- PizzaSize --------------------------- //

QVector<PizzaSize> PizzaSize::pizzaSizeList = QVector<PizzaSize>();

QVector<PizzaSize>& PizzaSize::GetPizzaSizeList()
{
    return pizzaSizeList;
}

PizzaSize PizzaSize::AddNew(QString _name, double _sizeFactor)
{
    PizzaSize p = PizzaSize(_name, _sizeFactor, pizzaSizeList.size());
    pizzaSizeList.push_back(p);
    return p;
}

PizzaSize::PizzaSize()
    :name(""), pizzaSizeId(-1), diameterFactor(0)
{
}

PizzaSize::PizzaSize(QString _name, double _sizeFactor, int _id)
    : name(_name), pizzaSizeId(_id), diameterFactor(_sizeFactor)
{
}

QString PizzaSize::GetName()
{
    return name;
}

QString PizzaSize::GetNameAndDiameterString()
{
    QString s = name;
    s.append(" (");
    s.append(QString::number(GetDiameter()));
    s.append(" cm)");
    return s;
}

int PizzaSize::GetId()
{
    return pizzaSizeId;
}

int PizzaSize::GetDiameter()
{
    return (int)(defaultDiameter * diameterFactor);
}

double PizzaSize::GetPriceFactor()
{
    // This could be some fancy formula, but no.
    return diameterFactor;
}







// ----------------------------------------------------------------- //
// -------------------------- Ingredient --------------------------- //

QVector<Ingredient> Ingredient::ingredientList = QVector<Ingredient>();
const QMap<Ingredient::ToppingType, QString> Ingredient::toppingCategoryNames = {
    {Ingredient::NO_TOPPING, QString("No topping")},
    {Ingredient::MEAT, QString("Meat")},
    {Ingredient::MARINADE, QString("Marinade")},
    {Ingredient::VEGETABLE, QString("Vegetables")},
    {Ingredient::CHEESE, QString("Cheese")},
    {Ingredient::GARNISH, QString("Garnish")},
};

QVector<Ingredient>& Ingredient::GetIngredientList()
{
    return ingredientList;
}

Ingredient Ingredient::AddNew(QString _name, int _price, IngredientType _ingredientType, ToppingType _toppingCategory)
{
    Ingredient i = Ingredient(_name, _price, _ingredientType, _toppingCategory);
    ingredientList.push_back(i);
    return i;
}

Ingredient Ingredient::AddNew(QString _name, IngredientType _ingredientType, ToppingType _toppingCategory)
{
    Ingredient i = Ingredient(_name, 0, _ingredientType, _toppingCategory);
    ingredientList.push_back(i);
    return i;
}

QString Ingredient::GetToppingTypeString(ToppingType _toppingType)
{
    return toppingCategoryNames.value(_toppingType);
}

Ingredient::Ingredient()
    : Merchandise(""), productNumber(0), ingredientType(NO_INGREDIENT), toppingType(NO_TOPPING)
{
}

Ingredient::Ingredient(QString _name, int _price, IngredientType _ingredientType, ToppingType _toppingCategory)
    : Merchandise(_name, _price), productNumber(ingredientList.size()), ingredientType(_ingredientType), toppingType(_toppingCategory)
{
}

Ingredient::ToppingType Ingredient::GetToppingType()
{
    return toppingType;
}

QString Ingredient::GetToppingTypeString()
{
    return toppingCategoryNames.value(toppingType);
}

Ingredient::IngredientType Ingredient::GetIngredientType()
{
    return ingredientType;
}

QString Ingredient::GetName() {
    return name;
}

int Ingredient::GetProductNumber() {
    return productNumber;
}

int Ingredient::GetDefaultComponentAmount()
{
    return defaultComponentAmount;
}

bool operator==(const Ingredient & l, const Ingredient & r)
{
    return l.productNumber == r.productNumber;
}

bool operator!=(const Ingredient & l, const Ingredient & r)
{
    return !(l == r);
}







// ----------------------------------------------------------------- //
// --------------------------- Component --------------------------- //

Component::Component(Ingredient _ingredient, int _amount)
    : ingredient(_ingredient), amount(_amount)
{
}

Component::Component()
    :ingredient(), amount(0)
{
}

int Component::GetPrice()
{
    return ingredient.GetPrice();
}

int Component::GetAmount()
{
    return amount;
}

QString Component::GetName()
{
    return ingredient.GetName();
}

Ingredient::IngredientType Component::GetType()
{
    return ingredient.GetIngredientType();
}

Ingredient Component::GetIngredient()
{
    return ingredient;
}







// ----------------------------------------------------------------- //
// ----------------------------- Pizza ----------------------------- //

QVector<Pizza> Pizza::pizzaList = QVector<Pizza>();
Pizza Pizza::selectedPizza = Pizza();

Pizza Pizza::GetSelectedPizza()
{
    return selectedPizza;
}

QVector<Pizza>& Pizza::GetPizzaList()
{
    return pizzaList;
}

Pizza& Pizza::AddNew(QString _name)
{
    Pizza p = Pizza(_name);
    pizzaList.push_back(p);
    return pizzaList.back();
}

Pizza::Pizza(QString _name)
    :Merchandise(_name)
{
}

Pizza::Pizza()
    : pizzaSize(), pizzaCrust(), crustFlourType()
{
}

QVector<Component>& Pizza::GetComponents()
{
    return components;
}

bool Pizza::ContainsIngredient(Ingredient ingredient)
{
    for (Component c : components)
    {
        if (ingredient == c.GetIngredient())
        {
            return true;
        }
    }

    return false;
}

void Pizza::Select()
{
    qDebug() << "Selecting " << name;
    selectedPizza = *this;
}

void Pizza::AddComponent(Ingredient ingredient, int amount)
{
    Component c = Component(ingredient, amount);
    qDebug() << "Added " << c.GetName();
    components.push_back(c);
}

void Pizza::AddComponent(Ingredient ingredient)
{
    AddComponent(ingredient, ingredient.GetDefaultComponentAmount());
}

void Pizza::RemoveComponent(Ingredient ingredient)
{
    // Todo: This function is kind of shitty! :D
    // Map?

    for (int i = 0; i < components.size(); ++i)
    {
        if (ingredient == components[i].GetIngredient())
        {
            qDebug() << "Removed " << ingredient.GetName();
            components.erase(components.begin() + i);
            break;
        }
    }

    // Todo: If the component didn't exist, throw exception? It should never
    // happen, after all. It's not very dangerous if it does happen, but it may
    // mean some other bad thing happened.
}

void Pizza::SetCrust(Ingredient _crustFlourIngredient, PizzaCrust _crustVariant)
{
    // The number 40 is the default amount of flour used in a pizza,
    // but it is currently not used in any way. Still, we left it here
    // in case we had time to expand on it:
    crustFlourType = Component(_crustFlourIngredient, 40);
    pizzaCrust = PizzaCrust(_crustVariant);
}

void Pizza::SetCrust(PizzaCrust _crustVariant)
{
    pizzaCrust = _crustVariant;
}

void Pizza::SetSize(PizzaSize _size)
{
    pizzaSize = _size;
}

PizzaSize Pizza::GetPizzaSize()
{
    return pizzaSize;
}

void Pizza::CompareWithSelectedPizza(QVector<Ingredient>& addedIngredients, QVector<Ingredient>& removedIngredients)
{
    // Todo: Shit function here, find a better search algorithm, please. Or better container.

    // Iterate through the components of the _source_ pizza.
    // For each component, iterate through this pizza's components, to see if
    // any of them has that same ingredient associated with it.

    for (Component source : selectedPizza.GetComponents())
    {
        bool contains = false;

        for (Component current : components)
        {
            if (current.GetIngredient() == source.GetIngredient())
            {
                contains = true;
                break;
            }
        }

        if (!contains)
        {
            removedIngredients.push_back(source.GetIngredient());
        }
    }


    // Now do the same, but the outer loop iterates through
    // the components of the _current_ pizza.

    for (Component current : components)
    {
        bool contains = false;

        for (Component source : selectedPizza.GetComponents())
        {
            if (current.GetIngredient() == source.GetIngredient())
            {
                contains = true;
                break;
            }
        }

        if (!contains)
        {
            addedIngredients.push_back(current.GetIngredient());
        }
    }
}

int Pizza::GetDiameter()
{
    return pizzaSize.GetDiameter();
}

PizzaCrust Pizza::GetPizzaCrust()
{
    return pizzaCrust;
}

QString Pizza::GetName() const
{
    return name;
}

QString Pizza::GetNameText()
{
    return name;
}

int Pizza::GetPrice()
{
    // Price-changing factors are size, quantity and topping
    // The number 75 is the starting price of a medium-sized pizza:
    int price = 75;

    for (Component c : components)
    {
        price += c.GetPrice();
    }

    price *= pizzaSize.GetPriceFactor();
    price *= quantity;

    return price;
}

QString Pizza::GetDescriptionText()
{
    QString descriptionText = "";

    QVector<Ingredient> addedIngredients;
    QVector<Ingredient> removedIngredients;
    CompareWithSelectedPizza(addedIngredients, removedIngredients);

    descriptionText.append("\t");
    descriptionText.append(pizzaSize.GetNameAndDiameterString());
    descriptionText.append("\n\t");
    descriptionText.append(pizzaCrust.GetName());
    descriptionText.append("\n");

    for (Ingredient c : addedIngredients)
    {
        descriptionText.append("\t+ ");
        descriptionText.append(c.GetName());
        descriptionText.append("\n");
    }

    for (Ingredient c : removedIngredients)
    {
        descriptionText.append("\t- ");
        descriptionText.append(c.GetName());
        descriptionText.append("\n");
    }

    return descriptionText;
}







// ----------------------------------------------------------------- //
// ----------------------------- Drink ----------------------------- //

QVector<Drink> Drink::drinkList = QVector<Drink>();

Drink &Drink::AddNew(QString _name, int _price)
{
    Drink d = Drink(_name, _price);
    drinkList.push_back(d);
    return drinkList.back();
}

QVector<Drink> &Drink::GetDrinkList()
{
    return drinkList;
}

Drink::Drink()
    :Merchandise("No name")
{
}

Drink::Drink(QString _name, int _price)
    :Merchandise(_name, _price)
{
}

QString Drink::GetNameText()
{
    return name;
}

QString Drink::GetName()
{
    return name;
}
















