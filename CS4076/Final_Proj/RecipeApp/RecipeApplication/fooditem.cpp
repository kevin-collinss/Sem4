#include "fooditem.h"
#include "quantity.h"

FoodItem::FoodItem(const QString& name)
    : m_name(name)
{}

FoodItem::FoodItem(const FoodItem& other) // COPY CONSTRUCTOR
    : m_name(other.m_name)
{}

QString FoodItem::getName() const
{
    return m_name;
}

FoodItemWithQuantity::FoodItemWithQuantity(const QString& name, const Quantity& quantity)
    : FoodItem(name), m_quantity(quantity) {}

FoodItemWithQuantity::FoodItemWithQuantity(const FoodItemWithQuantity& other) // Copy constructor definition
    : FoodItem(other), m_quantity(other.m_quantity)
{}

const Quantity& FoodItemWithQuantity::getQuantity() const
{
    return m_quantity;
}

FoodItem::~FoodItem() {
    // No explicit cleanup needed in this case
}

FoodItemWithQuantity::~FoodItemWithQuantity() {
}
