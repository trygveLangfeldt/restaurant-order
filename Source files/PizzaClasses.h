#pragma once
#include <QString>
#include <QVector>
#include <QDebug>
#include <QMetaType>
#include <QMap>







// ----------------------------------------------------------------- //
// -------------------------- Merchandise -------------------------- //

class Merchandise
{
protected:
    QString name;
    int price;
    int quantity;

    // 1 as minimum quantity makes sense:
    int minQuantity = 1;

    // 9 was picked as maximum quantity because the quantity number
    // is then ensured to be single digit only, which simplifies
    // layout design:
    int maxQuantity = 9;

public:
    Merchandise();
    Merchandise(QString _name, int _price = 0);
    void SetPrice(int newValue);
    int GetQuantity();
    int SetQuantity(int newValue);
    int IncrementQuantity(int increment = 1);
    int DecrementQuantity(int decrement = 1);
    virtual int GetPrice();
    virtual ~Merchandise();
    virtual QString GetNameText();
    virtual QString GetDescriptionText();
    virtual QString GetPriceText();
    virtual QString GetQuantityText();
};







// ----------------------------------------------------------------- //
// -------------------------- PizzaCrust --------------------------- //

class PizzaCrust
{
private:	// Static private members
    static QVector<PizzaCrust> pizzaCrustList;

public:     // Static public members
    static QVector<PizzaCrust>& GetPizzaCrustList();
    static PizzaCrust AddNew(QString _name, double _flourAmountFactor);

private:
    QString name;
    int pizzaCrustId;
    double flourAmountFactor;

public:
    double GetFlourAmountFactor() const;
    QString GetName() const;
    int GetId();
    PizzaCrust(QString _name, double _flourAmountFactor, int _id);
    PizzaCrust();
};

Q_DECLARE_METATYPE(PizzaCrust)







// ----------------------------------------------------------------- //
// --------------------------- PizzaSize --------------------------- //

class PizzaSize
{
private:	// Static private members
    static QVector<PizzaSize> pizzaSizeList;

    // defaultDiameter is the standard size. Different pizza size types multiply this
    // value by different factors, which produces the different pizza sizes.
    static constexpr double defaultDiameter = 28;

public:		// Static public members
    static QVector<PizzaSize>& GetPizzaSizeList();
    static PizzaSize AddNew(QString _name, double _sizeFactor);


private:
    QString name;
    int pizzaSizeId;
    double diameterFactor;

public:
    PizzaSize();
    PizzaSize(QString _name, double _sizeFactor, int _id);

    QString GetName();
    QString GetNameAndDiameterString();
    int GetId();
    int GetDiameter();
    double GetPriceFactor();
};

Q_DECLARE_METATYPE(PizzaSize)





// ----------------------------------------------------------------- //
// -------------------------- Ingredient --------------------------- //

class Ingredient : public Merchandise
{
public:
    enum IngredientType {
        NO_INGREDIENT,
        NON_COMPONENT,
        TOPPING,
        FLOUR,

        TOTAL_NUM_INGREDIENT_TYPES,
    };

    // Todo: Replace by container class?
    enum ToppingType {
        NO_TOPPING,
        MEAT,
        MARINADE,
        VEGETABLE,
        CHEESE,
        GARNISH,

        TOTAL_NUM_TOPPING_TYPES,
    };

private:	// Static private members
    static QVector<Ingredient> ingredientList;
    static const QMap<ToppingType, QString> toppingCategoryNames;

public:     // Static public members
    static QVector<Ingredient>& GetIngredientList();
    static Ingredient AddNew(QString _name, int _price, IngredientType _ingredientType, ToppingType _toppingCategory = NO_TOPPING);
    static Ingredient AddNew(QString _name, IngredientType _ingredientType, ToppingType _toppingCategory = NO_TOPPING);
    static QString GetToppingTypeString(ToppingType _toppingType);

private:
    int productNumber;
    int defaultComponentAmount = 0;
    IngredientType ingredientType;
    ToppingType toppingType;

public:
    Ingredient();
    Ingredient(QString _name, int price_, IngredientType _ingredientType, ToppingType _toppingCategory);

    ToppingType GetToppingType();
    QString GetToppingTypeString();
    IngredientType GetIngredientType();
    QString GetName();
    int GetProductNumber();
    int GetDefaultComponentAmount();
    friend bool operator==(const Ingredient& l, const Ingredient& r);
    friend bool operator!=(const Ingredient& l, const Ingredient& r);
};







// ----------------------------------------------------------------- //
// --------------------------- Component --------------------------- //

// Todo: This should probably be called ingredient, and Ingredient should probably
// be called something like FoodItem or Consumable, or something equivalent
// to the Norwegian "råvare", maybe?
class Component
{
    Ingredient ingredient;
    int amount;

public:
    Component(Ingredient _ingredient, int _amount);
    Component();

    int GetPrice();
    int GetAmount();
    QString GetName();
    Ingredient::IngredientType GetType();
    Ingredient GetIngredient();
};







// ----------------------------------------------------------------- //
// ----------------------------- Pizza ----------------------------- //

class Pizza : public Merchandise
{
private:	// Static private members
    static QVector<Pizza> pizzaList;
    static Pizza selectedPizza;

public:     // Static public members
    static Pizza GetSelectedPizza();
    static QVector<Pizza>& GetPizzaList();
    static Pizza& AddNew(QString _name);

private:
    PizzaSize pizzaSize;
    PizzaCrust pizzaCrust;
    Component crustFlourType;

    // Todo: Create a separate vector for non-topping ingredients? Ought to, probably.
    QVector<Component> components;

public:
    Pizza(QString _name);
    Pizza();

    QVector<Component>& GetComponents();
    bool ContainsIngredient(Ingredient ingredient);
    void Select();
    void AddComponent(Ingredient ingredient, int amount);
    void AddComponent(Ingredient ingredient);
    void RemoveComponent(Ingredient ingredient);
    void SetCrust(Ingredient _crustFlourType, PizzaCrust _crustVariant);
    void SetCrust(PizzaCrust _crustVariant);
    void SetSize(PizzaSize _size);
    void CompareWithSelectedPizza(QVector<Ingredient>& addedIngredients, QVector<Ingredient>& removedIngredients);
    int GetDiameter();
    PizzaCrust GetPizzaCrust();
    PizzaSize GetPizzaSize();
    QString GetName() const;

    QString GetNameText();
    QString GetDescriptionText();
    int GetPrice();
};







// ----------------------------------------------------------------- //
// ----------------------------- Drink ---------------------------- //

class Drink : public Merchandise
{
private:
    static QVector<Drink> drinkList;

public:
    static Drink& AddNew(QString _name, int _price);
    static QVector<Drink> &GetDrinkList();

public:
    Drink();
    Drink(QString _name, int _price);

    QString GetNameText();
    QString GetName();
    QString GetNameAndPriceString();
};

Q_DECLARE_METATYPE(Drink)












