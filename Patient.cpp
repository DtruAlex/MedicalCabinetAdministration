//
// Created by dumi on 10.06.2023.
//

#include "Patient.h"

Patient::Patient() {}
Patient::Patient(std::string name, std::string cnp) : name(std::move(name)), CNP(std::move(cnp)) {}

const std::string &Patient::getName() const {
    return name;
}
void Patient::setName(const std::string &newName) {
    name = newName;
}

const std::string &Patient::getCnp() const {
    return CNP;
}
void Patient::setCnp(const std::string &cnp) {
    CNP = cnp;
}

const std::vector<std::string> &Patient::getChronicDisease() const {
    return chronic_disease;
}
void Patient::setChronicDisease(const std::vector<std::string> &chronicDisease) {
    chronic_disease = chronicDisease;
}
void Patient::addChronicDisease(const std::string &chronicDisease){
    Patient::chronic_disease.push_back(chronicDisease);
}
void Patient::removeChronicDisease(const std::string &chronicDisease) {
    chronic_disease.erase(std::remove(chronic_disease.begin(), chronic_disease.end(), chronicDisease), chronic_disease.end());
}

const std::vector<std::string> &Patient::getDiagnosis() const {
    return diagnosis;
}
void Patient::setDiagnosis(std::vector<std::string> diagnostics) {
    Patient::diagnosis = diagnostics;
}
void Patient::addDiagnosis(const std::string &diagnostic){
    Patient::diagnosis.push_back(diagnostic);
}
void Patient::removeDiagnosis(const std::string &diagnostic) {
    diagnosis.erase(std::remove(diagnosis.begin(), diagnosis.end(), diagnostic), diagnosis.end());
}

const std::vector<std::string> &Patient::getPastInterventions() const {
    return past_interventions;
}
void Patient::setPastInterventions(const std::vector<std::string> &pastInterventions) {
    past_interventions = pastInterventions;
}
void Patient::addPastInterventions(const std::string &pastInterventions){
    Patient::past_interventions.push_back(pastInterventions);
}


nlohmann::json Patient::serialize() {
    nlohmann::json data;
    data["name"]= this->getName();
    data["CNP"]= this->getCnp();
    data["chronic_disease"]= this->getChronicDisease();
    data["diagnosis"]= this->getDiagnosis();
    data["past_interventions"] = this->getPastInterventions();
    return data;
}
Patient Patient::deserialize(nlohmann::json data) {
    Patient x = *new Patient;
    x.setName(data["name"].get<std::string>());
    x.setCnp(data["CNP"].get<std::string>());
    x.setChronicDisease(data["chronic_disease"].get<std::vector<std::string>>());
    x.setDiagnosis(data["diagnosis"].get<std::vector<std::string>>());
    x.setPastInterventions(data["past_interventions"].get<std::vector<std::string>>());
    return x;
}
std::ostream &operator<<(std::ostream &os, const Patient &data) {
    os<<"Name: "<<data.getName()<<"\n";
    os<<"CNP: "<<data.getCnp()<<"\n";
    os<<"Diagnosis: ";
    for(auto i: data.getDiagnosis())
        os<<i<<", ";
    os<<"\n";
    os<<"Chronic Diseases: ";
    for(auto i: data.getChronicDisease())
        os<<i<<", ";
    os<<"\n";
    os<<"Past Interventions: ";
    for(auto i: data.getPastInterventions())
        os<<i<<", ";
    os<<"\n";
    return os;
}
bool operator==(const Patient &p1, const Patient &p2) {
    return (p1.getName()==p2.getName() && p1.getCnp()==p2.getCnp());
}

Patient::~Patient() {

}