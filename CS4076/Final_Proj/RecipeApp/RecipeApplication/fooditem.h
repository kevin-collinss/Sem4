#ifndef FOODITEM_H
#define FOODITEM_H

#include "quantity.h"
#include <QString>

class FoodItem {
public:
    FoodItem(const QString& name);
    FoodItem(const FoodItem& other); // Copy constructor declaration

    //VIRTUAL FUNCTIONS
    virtual ~FoodItem();
    virtual QString getName() const;

private:
    QString m_name;
};

class FoodItemWithQuantity : public FoodItem { //INHERITANCE
public:
    FoodItemWithQuantity(const QString& name, const Quantity& quantity);
    FoodItemWithQuantity(const FoodItemWithQuantity& other); // Copy constructor declaration

    ~FoodItemWithQuantity(); // DESTRUCTOR
    const Quantity& getQuantity() const;

    friend class MainWindow; // FRIEND CLASS

private:
    Quantity m_quantity;
};

#endif // FOODITEM_H
