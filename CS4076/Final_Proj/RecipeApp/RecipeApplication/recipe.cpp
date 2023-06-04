#include "recipe.h"
#include "fooditem.h"

Recipe::Recipe(QString name, QString description, QList<FoodItem*> ingredients) //INITIALISER LIST
    : m_name(name), m_description(description), m_ingredients(ingredients)
{
}

Recipe::Recipe(const Recipe& other) noexcept// Copy constructor definition with deep copy
    : m_name(other.m_name), m_description(other.m_description)
{
    for (const auto& item : other.m_ingredients) {
        if (auto itemWithQuantity = dynamic_cast<FoodItemWithQuantity*>(item)) {
            m_ingredients.append(new FoodItemWithQuantity(*itemWithQuantity));
        } else {
            m_ingredients.append(new FoodItem(*item));
        }
    }
}

void Recipe::addIngredient(FoodItem* ingredient) {
    m_ingredients.append(ingredient);
}

QString Recipe::getName() const
{
    return m_name;
}

QString Recipe::getDescription() const
{
    return m_description;
}

QList<FoodItem*> Recipe::getIngredients() const
{
    return m_ingredients;
}

Recipe::~Recipe() {
    // Clean up the ingredients
    for (auto ingredient : m_ingredients) {
        delete ingredient;
    }
}
