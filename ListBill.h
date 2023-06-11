//
// Created by dumi on 10.06.2023.
//

#ifndef C__PROJECT_LISTBILL_H
#define C__PROJECT_LISTBILL_H
#include "Bill.h"
#include <string>
#include <vector>
#include "json.hpp"

class ListBill{
private:
    std::vector<Bill> listOfBills;
public:
    ListBill();
    explicit ListBill(const std::vector<Bill> &listOfBills);

    const std::vector<Bill> &getListOfBills() const;
    void setListOfBills(const std::vector<Bill> &listOfBills);

    virtual ~ListBill();

    void addBillToList(const Bill& billToAdd);
    void removeBillFromList(const Bill& billToAdd);

    void writeTofile(const std::string& fileName);
    void readFromFile(const std::string& fileName);
};

#endif //C__PROJECT_LISTBILL_H
