//
// Created by dumi on 10.06.2023.
//

#ifndef C__PROJECT_INVENTORY_H
#define C__PROJECT_INVENTORY_H

#include <string>
#include <vector>
#include "json.hpp"
#include "Product.h"

class Inventory{
private:
    std::vector<Product> listOfProducts;
public:
    const std::vector<Product> &getListOfProducts() const;
    void setListOfProducts(const std::vector<Product> &listOfProducts);

    void addProductToList(const Product& product);
    void removeProductFromList(const Product& product);

    void writeTofile(const std::string& fileName);
    void readFromFile(const std::string& fileName);
    void deserialize(const nlohmann::json& dataToUnpack);
    nlohmann::json serialize();
};

#endif //C__PROJECT_INVENTORY_H
