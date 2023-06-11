//
// Created by dumi on 10.06.2023.
//

#include "Bill.h"
#include <iostream>
#include <fstream>

const Patient &Bill::getPatient() const {
    return patient;
}
void Bill::setPatient(const Patient &patientToPay) {
    Bill::patient = patientToPay;
}
const Inventory &Bill::getListOfUsedProducts() const {
    return listOfProducts;
}
void Bill::setListOfProducts(const Inventory &listOfUsedProducts) {
    Bill::listOfProducts = listOfUsedProducts;
}


double Bill::getTotalPrice() const {
    return totalPrice;
}
void Bill::setTotalPrice(const double totalPriceOfBill){
    Bill::totalPrice = totalPriceOfBill;
}

void Bill::addProductToBill(Inventory &hospitalInventory,std::string productName,int quantity) {
    auto hospitalListOfProducts= hospitalInventory.getListOfProducts();
    Product productToAdd=Product();
    for(int i=0;i<hospitalListOfProducts.size();i++) {
        if (hospitalListOfProducts[i].getName() == productName) {
            if (hospitalListOfProducts[i].getQuantity() >= quantity) {
                hospitalListOfProducts[i].sellQuantity(quantity);
                productToAdd.setName(productName);
                productToAdd.setQuantity(quantity);
                productToAdd.setCategories(hospitalListOfProducts[i].getCategories());
                productToAdd.setPrice(hospitalListOfProducts[i].getPrice());
            }
        }
    }
    hospitalInventory.setListOfProducts(hospitalListOfProducts);
    Bill::listOfProducts.addProductToList(productToAdd);
}

void Bill::removeProductFromBill(Inventory &hospitalInventory, const std::string& productName) {
    bool ok = false;
    int quantityToAdd = 0;
    do {
        for (auto i: getListOfUsedProducts().getListOfProducts())
            if (productName == i.getName()) {
                quantityToAdd = i.getQuantity();
                std::cout << "quantityToAdd: " << quantityToAdd << "\n";
                ok = true;
                listOfProducts.removeProductFromList(i);
            }
    } while (!ok);
    int ct=0;
    for (auto i: hospitalInventory.getListOfProducts()) {

        if (productName == i.getName()) {
            std::cout << "name: " << i.getName() << " quant: " << i.getQuantity() << "\n";
            auto x= hospitalInventory.getListOfProducts();
            x[ct].addQuantity(quantityToAdd);
            hospitalInventory.setListOfProducts(x);
            return;
        }
        ct++;
    }
}

void Bill::pay(){
    payed = true;
}

void Bill::calulateTotalPrice() {
    double total=0;
    for(auto productL:listOfProducts.getListOfProducts())
    {
        total += productL.getPrice()*productL.getQuantity();
    }
    Bill:totalPrice = total;
}

nlohmann::json Bill::serialize() {
    nlohmann::json data;
    data["bill"]["usedProducts"]=listOfProducts.serialize();
    data["bill"]["patient"]=patient.serialize();
    data["bill"]["totalPrice"]=totalPrice;
    data["bill"]["payed"]=payed;
//    std::cout << std::setw(4) << data << std::endl;
    return data;
}

Bill Bill::deserialize(nlohmann::json dataToUnpack) {
    Bill x;
    x.setPayed(dataToUnpack["payed"].get<bool>());
    x.setTotalPrice( dataToUnpack["totalPrice"].get<double>());
    x.setPatient(Patient::deserialize(dataToUnpack["patient"]));
    Inventory inv;
    inv.deserialize(dataToUnpack["usedProducts"]);
    x.setListOfProducts(inv);
    return x;

}

void Bill::writeTofile(const std::string &fileName) {
    std::ofstream fout(fileName);
    fout << std::setw(4) << serialize() << std::endl;
}

void Bill::readFromFile(const std::string &fileName) {
    std::ifstream f(fileName);
    nlohmann::json data = nlohmann::json::parse(f);
    deserialize(data);
}

bool operator==(const Bill &b1, const Bill &b2) {
    return (b1.getPatient()==b2.getPatient() &&
            b1.getTotalPrice()==b2.getTotalPrice() &&
            b1.getPayed() == b2.getPayed());
}

void Bill::setPayed(bool state) {
    this->payed=state;
}

bool Bill::getPayed() const {
    return payed;
}
