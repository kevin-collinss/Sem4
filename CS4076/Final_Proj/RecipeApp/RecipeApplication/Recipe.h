#ifndef RECIPE_H
#define RECIPE_H

#include <QString>
#include <QList>
#include "fooditem.h"

class Recipe
{
public:
    Recipe(QString name, QString description, QList<FoodItem*> ingredients);
    Recipe(const Recipe& other) noexcept; // Add noexcept here

    ~Recipe();
    QString getName() const;
    QString getDescription() const;
    QList<FoodItem*> getIngredients() const;

    void addIngredient(FoodItem* ingredient); // Add this new function


private:
    QString m_name;
    QString m_description;
    QList<FoodItem*> m_ingredients;
};

#endif // RECIPE_H
