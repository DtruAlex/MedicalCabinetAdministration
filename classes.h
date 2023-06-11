//
// Created by dumi on 15.05.2023.
//

#ifndef C__PROJECT_CLASSES_H
#define C__PROJECT_CLASSES_H

#include <string>
#include <vector>
#include "json.hpp"


//
//
//
//class Patient{
//private:
//    std::string name;
//    std::string CNP;
//    std::vector<std::string> chronic_disease;
//    std::vector<std::string> diagnosis;
//    std::vector<std::string> past_interventions;
//public:
//    Patient();
//    Patient(std::string name, std::string cnp);
//
//    const std::string &getName() const;
//    void setName(const std::string &newName);
//
//    const std::string &getCnp() const;
//    void setCnp(const std::string &cnp);
//
//    const std::vector<std::string> &getChronicDisease() const;
//    void setChronicDisease(const std::vector<std::string> &chronicDisease);
//    void addChronicDisease(const std::string &chronicDisease);
//    void removeChronicDisease(const std::string &chronicDisease);
//
//    const std::vector<std::string> &getDiagnosis() const;
//    void setDiagnosis(const std::vector<std::string> &diagnosis);
//    void addDiagnosis(const std::string &diagnostic);
//    void removeDiagnosis(const std::string &diagnostic);
//
//    const std::vector<std::string> &getPastInterventions() const;
//    void setPastInterventions(const std::vector<std::string> &pastInterventions);
//    void addPastInterventions(const std::string &pastInterventions);
//
//    nlohmann::json serialize();
//    static Patient deserialize( nlohmann::json data);
//    friend std::ostream& operator<<(std::ostream& os, const Patient& data);
//    friend bool operator== (const Patient& p1, const Patient& p2);
//
//    ~Patient();
//
//};

//class ListPatients{
//private:
//    std::vector<Patient> listOfPatients;
//public:
//    ListPatients();
//    explicit ListPatients(const std::vector<nlohmann::json> &newListOfPatients);
//
//    void addPatientToList(const Patient& patientToAdd);
//    void removePatientFromList(const Patient& patientToRemove);
//
//
//    const std::vector<Patient> &getListOfPatients() const;
//    void setListOfPatients(const std::vector<Patient> &listOfPatients);
//
//
//    void writeTofile(const std::string& fileName);
//    void readFromFile(const std::string& fileName);
//    nlohmann::json serialize();
//    void deserialize(const nlohmann::json& dataToUnpack);
//    virtual ~ListPatients();
//};

//class Product{
//public:
//    Product();
//    Product(const std::string &name, std::string categories, int quantity, double price);
//
//private:
//    std::string name;
//    std::string categories;
//    int quantity;
//    double price;
//
//public:
//    const std::string &getName() const;
//    void setName(const std::string &name);
//
//    std::string getCategories() const;
//    void setCategories(std::string categories);
//
//    int getQuantity() const;
//    void setQuantity(int quantity);
//    void addQuantity(int quantity);
//    void sellQuantity(int quantity);
//
//    double getPrice() const;
//    void setPrice(double price);
//
//    nlohmann::json serialize();
//    static Product deserialize( nlohmann::json data);
//    friend std::ostream& operator<<(std::ostream& os, const Product& data);
//    friend bool operator== (const Product& p1, const Product& p2);
//
//};











#endif //C__PROJECT_CLASSES_H
