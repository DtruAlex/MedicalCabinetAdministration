#include <iostream>
#include <fstream>

#include "Patient.h"
#include "ListPatients.h"
#include "Product.h"
#include "Inventory.h"
#include "Bill.h"
#include "ListBill.h"

#include "json.hpp"
using json = nlohmann::json;

Inventory cabinetInventory;
ListPatients listOfPatients;
ListBill listOfBills;

//Utilities
S
void printBill(Bill x){
    std::cout<<x.getPatient()<<"\n";
    for(auto i:x.getListOfUsedProducts().getListOfProducts()){
        std::cout<<i<<"\n";
    }
    std::cout<<"Total Price: "<<x.getTotalPrice()<<"\n";
    std::cout<<"Payed: "<<x.getPayed()<<"\n";
}

void showBills(){
    system("clear");
    std::cout<<"List of Bills:\n";
    int ct=1;
    for(auto i:listOfBills.getListOfBills())
    {
        std::cout<<ct<<".Bill"<<"\n";
        printBill(i);
        ct++;
    }
}


std::vector<std::string> stringToList(std::string stringToSplit){
    std::vector<std::string>result;
    std::string token = ",";
    while(stringToSplit.size()){
        int index = stringToSplit.find(token);
        if(index!=std::string::npos){
            result.push_back(stringToSplit.substr(0,index));
            stringToSplit = stringToSplit.substr(index+token.size());
            if(stringToSplit.size()==0)result.push_back(stringToSplit);
        }else{
            result.push_back(stringToSplit);
            stringToSplit = "";
        }
    }
    return result;
}



//Code

void showProducts(){
    system("clear");
    std::cout<<"List of Products:\n";
    int ct=1;
    for(auto i:cabinetInventory.getListOfProducts())
    {
        std::cout<<ct<<". "<<i<<"\n";
        ct++;
    }
}

void showPatients(){
    system("clear");
    std::cout<<"List of Patients:\n";
    int ct=1;
    for(auto i:listOfPatients.getListOfPatients())
    {
        std::cout<<ct<<". "<<i<<"\n";
        ct++;
    }
}

void addPatient(){
    Patient x= *new Patient;
    std::string temp;
    getchar();
    std::cout<<"Name of New Patient: ";
    std::getline(std::cin,temp);
    x.setName(temp);
    std::cout<<"CNP of New Patient: ";
    std::cin>>temp;
    x.setCnp(temp);
    listOfPatients.addPatientToList(x);
    return;
}

void modifyPatient() {
    int i=0,choice;
    std::string temp;
    showPatients();
    auto list=listOfPatients.getListOfPatients();
    std::cout<<"Select patient to modify";std::cin>>i;
    i-=1;
    std::cout<<"Select what to modify\n"
               "1.Name\n"
               "2.CNP\n"
               "3.Diagnosis\n"
               "4.Chronic Diseases\n"
               "5.Past Interventions\n";
    std::cin>>choice;
    switch(choice)
    {
        case 1:{
            std::cout<<"Modify name";std::cin>>temp;
            list[i].setName(temp);
            break;
        }
        case 2:{
            std::cout<<"Modify CNP";std::cin>>temp;
            list[i].setCnp(temp);
            break;
        }
        case 3:{
            std::cout<<"Modify Diagnostic: ";
            getchar();
            getline(std::cin,temp);
            list[i].setDiagnosis(stringToList(temp));
            break;
        }
        case 4:{
            std::cout<<"Modify ChronicDisease: ";
            getchar();
            getline(std::cin,temp);
            list[i].setChronicDisease(stringToList(temp));
           break;
        }
        case 5:{
            std::cout<<"Modify Past Interventions: ";
            getchar();
            getline(std::cin,temp);
            list[i].setPastInterventions(stringToList(temp));
           break;
        }
    }
     listOfPatients.setListOfPatients(list);
}

void removePatient(){
    int i=0;
    std::string temp;
    showPatients();
    auto list=listOfPatients.getListOfPatients();
    std::cout<<"Select patient to remove: ";std::cin>>i;
    i-=1;
    listOfPatients.removePatientFromList(list[i]);
    std::cout<<"Patient Removed\n";
}

void seePatients(){
    showPatients();
    std::cin.get();
    std::cout<<"Press any key to go back\n";
    std::cin.get();
}

void addProduct(){
    Product x= *new Product;
    std::string temp;
    double price;
    getchar();
    std::cout<<"Name of New Product: ";
    std::getline(std::cin,temp);
    x.setName(temp);
    std::cout<<"Category of New Product: ";
    std::cin>>temp;
    x.setCategories(temp);
    std::cout<<"Price of New Product: ";
    std::cin>>price;
    x.setPrice(price);
    cabinetInventory.addProductToList(x);
    return;
}

void seeProducts(){
    showProducts();
    std::cin.get();
    std::cout<<"Press any key to go back\n";
    std::cin.get();
}

void addQuantityToProduct(){
    int i,quantity;
    showProducts();
    auto list=cabinetInventory.getListOfProducts();
    std::cout<<"Select product to add quantity : ";std::cin>>i;
    i-=1;
    std::cout<<"Quantity to add: ";std::cin>>quantity;
    list[i].addQuantity(quantity);
    cabinetInventory.setListOfProducts(list);

}

void removeQuantityFromProduct(){
    int i,quantity;
    showProducts();
    auto list=cabinetInventory.getListOfProducts();
    std::cout<<"Select product to remove quantity : ";std::cin>>i;
    i-=1;
    std::cout<<"Quantity to remove: ";std::cin>>quantity;
    list[i].sellQuantity(quantity);
    cabinetInventory.setListOfProducts(list);

}

void removeProduct(){
    int i;
    showProducts();
    auto list=cabinetInventory.getListOfProducts();
    std::cout<<"Select product to remove: ";std::cin>>i;
    i-=1;
    cabinetInventory.removeProductFromList(list[i]);
    std::cout<<"Product Removed\n";
}

std::string productSelector(){
    int i;
    auto listProducts = cabinetInventory.getListOfProducts();
    showProducts();
    std::cout << "Select products from list to add:";
    std::cin >> i;
    i-=1;
    return listProducts[i].getName();
}



void addBill() {
    Bill x;
    int i = 0, quantity, choice;
    std::string temp;
    showPatients();
    auto listPatient = listOfPatients.getListOfPatients();
    std::cout << "Select patient to assign the bill to: ";
    std::cin >> i;
    i -= 1;
    x.setPatient(listPatient[i]);
    std::cout << "Patient asigned\n\n";


    auto usedProducts = Inventory();


    while (choice != 99) {
        std::string productName=productSelector();
        std::cout << "Insert Quantity: ";
        std::cin>>quantity;
        x.addProductToBill(cabinetInventory,productName,quantity);
        std::cout << "Press 99 to stop adding products";
        std::cin >> choice;
    }

    x.calulateTotalPrice();
    listOfBills.addBillToList(x);
    std::cout<<"Bill Added\n";
}

void payBill(){

    int i;
    showBills();
    auto list=listOfBills.getListOfBills();
    std::cout<<"Select bill to pay: ";std::cin>>i;
    i-=1;
    list[i].pay();
    listOfBills.setListOfBills(list);
    std::cout<<"Bill Payed\n";
}
void seeBills(){
    showBills();
    std::cin.get();
    std::cout<<"Press any key to go back\n";
    std::cin.get();
}

void removeBill(){
    int i;
    showBills();
    auto list=listOfBills.getListOfBills();
    int ct=1;
    for(auto i:list)
    {
        std::cout<<ct<<".Bill"<<"\n";
        printBill(i);
        ct++;
    }
    std::cout<<"Select bill to remove: ";std::cin>>i;
    i-=1;
    listOfBills.removeBillFromList(list[i]);
    std::cout<<"Bill Removed\n";
}

int main() {

    if (!std::filesystem::is_empty("patients.json")) {
        std::ifstream fin("patients.json");
        std::string temp;
        fin >> temp;
        if (temp != "null") {
            listOfPatients.readFromFile("patients.json");
        }
    }
    if (!std::filesystem::is_empty("products.json")) {
        std::ifstream fin("products.json");
        std::string temp;
        fin >> temp;
        if (temp != "null") {
            cabinetInventory.readFromFile("products.json");
        }
    }
    if (!std::filesystem::is_empty("bills.json")) {
        std::ifstream fin("bills.json");
        std::string temp;
        fin >> temp;
        if (temp != "null") {
            listOfBills.readFromFile("bills.json");
        }
    }

    int i = 0;
    while (i < 99) {
        std::cout << "\nMedical Cabinet Administration System\n"
                     "Choose what you to do\n"
                     "1.Add Patient\n"
                     "2.Modify Patient\n"
                     "3.Remove Patient\n"
                     "4.See Patients\n"
                     "5.Add new product to inventory\n"
                     "6.See Products\n"
                     "7.Add quantity of product\n"
                     "8.Remove quantity of product\n"
                     "9.Remove product from inventory\n"
                     "10.Create new bill\n"
                     "11.See Bills\n"
                     "12.Pay bill\n"
                     "13.Remove bill\n"
                     "99. Exit\n";
        std::cin >> i;
        switch (i) {
            case 1: {
                addPatient();
                break;
            }
            case 2: {
                modifyPatient();
                break;
            }
            case 3: {
                removePatient();
                break;
            }
            case 4: {
                seePatients();
                break;
            }
            case 5: {
                addProduct();
                break;
            }
            case 6: {
                seeProducts();
                break;
            }
            case 7: {
                addQuantityToProduct();
                break;
            }
            case 8: {
                removeQuantityFromProduct();
                break;
            }
            case 9: {
                removeProduct();
                break;
            }
            case 10: {
                addBill();
                break;
            }
            case 11: {
                seeBills();
                break;
            }
            case 12: {
                payBill();
                break;
            }
            case 13: {
                removeBill();
                break;
            }
        }
    }
    listOfPatients.writeTofile("patients.json");
    cabinetInventory.writeTofile("products.json");
    listOfBills.writeTofile("bills.json");
    return 0;
}