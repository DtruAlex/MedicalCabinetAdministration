//
// Created by dumi on 10.06.2023.
//

#ifndef C__PROJECT_BILL_H
#define C__PROJECT_BILL_H

#include <string>
#include <vector>
#include "json.hpp"
#include "Patient.h"
#include "Inventory.h"

class Bill{
private:
    Patient patient;
    Inventory listOfProducts;
    double totalPrice;
    bool payed = false;
public:
    const Patient &getPatient() const;
    void setPatient(const Patient &patient);


    const Inventory &getListOfUsedProducts() const;
    void setListOfProducts(const Inventory &listOfProducts);

    void addProductToBill(Inventory &hospitalInventory,std::string product,int quantity);
    void removeProductFromBill(Inventory &hospitalInventory,const std::string& product);

    void calulateTotalPrice();

    double getTotalPrice() const;
    void setTotalPrice(const double totalPrice);

    bool getPayed() const;
    void setPayed(bool state);
    void pay();

    nlohmann::json serialize();
    static Bill deserialize(nlohmann::json dataToUnpack);

    void writeTofile(const std::string& fileName);
    void readFromFile(const std::string& fileName);
    friend bool operator== (const Bill& b1, const Bill& b2);

};


#endif //C__PROJECT_BILL_H
