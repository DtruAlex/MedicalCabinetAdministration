//
// Created by dumi on 10.06.2023.
//

#ifndef C__PROJECT_PRODUCT_H
#define C__PROJECT_PRODUCT_H


#include <string>
#include <vector>
#include "json.hpp"

class Product{
public:
    Product();
    Product(const std::string &name, std::string categories, int quantity, double price);

private:
    std::string name;
    std::string categories;
    int quantity;
    double price;

public:
    const std::string &getName() const;
    void setName(const std::string &name);

    std::string getCategories() const;
    void setCategories(std::string categories);

    int getQuantity() const;
    void setQuantity(int quantity);
    void addQuantity(int quantity);
    void sellQuantity(int quantity);

    double getPrice() const;
    void setPrice(double price);

    nlohmann::json serialize();
    static Product deserialize( nlohmann::json data);
    friend std::ostream& operator<<(std::ostream& os, const Product& data);
    friend bool operator== (const Product& p1, const Product& p2);

};

#endif //C__PROJECT_PRODUCT_H
