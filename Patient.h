//
// Created by dumi on 10.06.2023.
//

#ifndef C__PROJECT_PATIENT_H
#define C__PROJECT_PATIENT_H

#include <string>
#include <vector>
#include "json.hpp"


class Patient{
private:
    std::string name;
    std::string CNP;
    std::vector<std::string> chronic_disease;
    std::vector<std::string> diagnosis;
    std::vector<std::string> past_interventions;
public:
    Patient();
    Patient(std::string name, std::string cnp);

    const std::string &getName() const;
    void setName(const std::string &newName);

    const std::string &getCnp() const;
    void setCnp(const std::string &cnp);

    const std::vector<std::string> &getChronicDisease() const;
    void setChronicDisease(const std::vector<std::string> &chronicDisease);
    void addChronicDisease(const std::string &chronicDisease);
    void removeChronicDisease(const std::string &chronicDisease);

    const std::vector<std::string> &getDiagnosis() const;
    void setDiagnosis(std::vector<std::string> diagnosis);
    void addDiagnosis(const std::string &diagnostic);
    void removeDiagnosis(const std::string &diagnostic);

    const std::vector<std::string> &getPastInterventions() const;
    void setPastInterventions(const std::vector<std::string> &pastInterventions);
    void addPastInterventions(const std::string &pastInterventions);

    nlohmann::json serialize();
    static Patient deserialize( nlohmann::json data);
    friend std::ostream& operator<<(std::ostream& os, const Patient& data);
    friend bool operator== (const Patient& p1, const Patient& p2);

    ~Patient();

};

#endif //C__PROJECT_PATIENT_H
