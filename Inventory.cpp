//
// Created by dumi on 10.06.2023.
//

#include "Inventory.h"
#include <fstream>

const std::vector<Product> &Inventory::getListOfProducts() const {
    return listOfProducts;
}

void Inventory::setListOfProducts(const std::vector<Product> &newListOfProducts) {
    Inventory::listOfProducts = newListOfProducts;
}

void Inventory::addProductToList(const Product& product){
    this->listOfProducts.push_back(product);
}

void Inventory::removeProductFromList(const Product& product) {
    listOfProducts.erase(std::remove(listOfProducts.begin(), listOfProducts.end(), product), listOfProducts.end());
}

void Inventory::writeTofile(const std::string &fileName) {
    nlohmann::json data;
    std::ofstream fout(fileName);
    for(int i=0;i<this->getListOfProducts().size();i++)
    {
        data["inventory"].push_back(this->listOfProducts[i].serialize());
    }
    fout << std::setw(4) << data << std::endl;
}

void Inventory::readFromFile(const std::string &fileName) {
    std::ifstream f(fileName);
    nlohmann::json data = nlohmann::json::parse(f);
    listOfProducts.clear();
    auto tempList = data["inventory"].get<std::vector<nlohmann::json>>();
    for(int i=0;i<tempList.size();i++) {

        addProductToList(Product::deserialize(tempList[i]));
    }

}

void Inventory::deserialize(const nlohmann::json& dataToUnpack){
    listOfProducts.clear();
    auto tempList = dataToUnpack["Products"].get<std::vector<nlohmann::json>>();
    for(int i=0;i<tempList.size();i++) {

        addProductToList(Product::deserialize(tempList[i]));
    }
}

nlohmann::json Inventory::serialize() {
    nlohmann::json data;;
    for(int i=0;i<this->getListOfProducts().size();i++)
    {
        data["Products"].push_back(this->listOfProducts[i].serialize());
    }
    return data;
}