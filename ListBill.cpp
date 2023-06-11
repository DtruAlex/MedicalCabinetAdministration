//
// Created by dumi on 10.06.2023.
//

#include "ListBill.h"
#include <fstream>
#include <iostream>

const std::vector<Bill> &ListBill::getListOfBills() const {
    return listOfBills;
}

void ListBill::setListOfBills(const std::vector<Bill> &listOfBills) {
    ListBill::listOfBills = listOfBills;
}

ListBill::ListBill(const std::vector<Bill> &listOfBills) : listOfBills(listOfBills) {}

ListBill::ListBill() {}

ListBill::~ListBill() {

}

void ListBill::addBillToList(const Bill& billToAdd) {
    this->listOfBills.push_back(billToAdd);
}

void ListBill::removeBillFromList(const Bill &billToRemove) {
    listOfBills.erase(std::remove(listOfBills.begin(), listOfBills.end(), billToRemove), listOfBills.end());
}

void ListBill::writeTofile(const std::string &fileName) {
    nlohmann::json data;
    std::ofstream fout(fileName);

    for(int i=0;i<this->listOfBills.size();i++)
    {
        data["bills"].push_back(this->listOfBills[i].serialize());
    }
    fout << std::setw(4) << data << std::endl;

}

void ListBill::readFromFile(const std::string &fileName) {
    std::ifstream f(fileName);
    nlohmann::json data = nlohmann::json::parse(f);
    std::cout<<std::setw(4)<<data<<"\n";
    listOfBills.clear();
    auto tempList = data["bills"].get<std::vector<nlohmann::json>>();
    for(int i=0;i<tempList.size();i++) {
        Bill x;
        nlohmann::json bill=tempList[i]["bill"];
        addBillToList(x.deserialize(bill));
    }
}
