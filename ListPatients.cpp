//
// Created by dumi on 10.06.2023.
//

#include "ListPatients.h"
#include <fstream>

const std::vector<Patient> &ListPatients::getListOfPatients() const {
    return listOfPatients;
}

void ListPatients::setListOfPatients(const std::vector<Patient> &listOfPatients) {
    ListPatients::listOfPatients = listOfPatients;
}

void ListPatients::writeTofile(const std::string& fileName) {
    nlohmann::json data;
    std::ofstream fout(fileName);
    for(int i=0;i<this->getListOfPatients().size();i++)
    {
        data["patients"].push_back(this->listOfPatients[i].serialize());
    }
    fout << std::setw(4) << data << std::endl;
}

void ListPatients::addPatientToList(const Patient& patientToAdd) {
    this->listOfPatients.push_back(patientToAdd);
}

void ListPatients::readFromFile(const std::string &fileName) {
    std::ifstream f(fileName);
    nlohmann::json data = nlohmann::json::parse(f);
    listOfPatients.clear();
    auto tempList = data["patients"].get<std::vector<nlohmann::json>>();
    for(int i=0;i<tempList.size();i++) {
        addPatientToList(Patient::deserialize(tempList[i]));
    }

}

ListPatients::~ListPatients() {
}

ListPatients::ListPatients() {}

//ListPatients::ListPatients(const std::vector<nlohmann::json> &newListOfPatients){
//    for(int i=0;i<newListOfPatients.size();i++)
//    {
//        std::cout<<newListOfPatients[i]<<std::endl;
//    }
//}

void ListPatients::removePatientFromList(const Patient &patientToRemove) {
    listOfPatients.erase(std::remove(listOfPatients.begin(), listOfPatients.end(), patientToRemove), listOfPatients.end());
}

nlohmann::json ListPatients::serialize() {
    nlohmann::json data;
    for(int i=0;i<this->getListOfPatients().size();i++)
    {
        data["patients"].push_back(this->listOfPatients[i].serialize());
    }
    return data;
}

void ListPatients::deserialize(const nlohmann::json &dataToUnpack) {
    listOfPatients.clear();
    auto tempList = dataToUnpack["patients"].get<std::vector<nlohmann::json>>();
    for(int i=0;i<tempList.size();i++) {
        addPatientToList(Patient::deserialize(tempList[i]));
    }
}