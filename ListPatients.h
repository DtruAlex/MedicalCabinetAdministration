//
// Created by dumi on 10.06.2023.
//

#ifndef C__PROJECT_LISTPATIENTS_H
#define C__PROJECT_LISTPATIENTS_H

#include "Patient.h"
#include <string>
#include <vector>
#include "json.hpp"

class ListPatients{
private:
    std::vector<Patient> listOfPatients;
public:
    ListPatients();
    explicit ListPatients(const std::vector<nlohmann::json> &newListOfPatients);

    void addPatientToList(const Patient& patientToAdd);
    void removePatientFromList(const Patient& patientToRemove);


    const std::vector<Patient> &getListOfPatients() const;
    void setListOfPatients(const std::vector<Patient> &listOfPatients);


    void writeTofile(const std::string& fileName);
    void readFromFile(const std::string& fileName);
    nlohmann::json serialize();
    void deserialize(const nlohmann::json& dataToUnpack);
    virtual ~ListPatients();
};
#endif //C__PROJECT_LISTPATIENTS_H
