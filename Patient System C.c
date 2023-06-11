#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <conio.h>


//Variables:        name, CNP, chronic disease, diagnostic, past interventions
//Functionalities:  adding, editing, deleting data and searching patients by name
//                  saving and retrieving data from the file



//global variables:

// path to working file
char myFile[] = "C:\\Users\\andre\\CLionProjects6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666\\proiect_pacienti\\test_file.csv";

// definition of patient structure, size = 414 bytes
struct structPatient {
    char name[100];
    char CNP[14];
    char chronic_disease[100];
    char diagnosis[100];
    char past_interventions[100];
};

typedef struct structPatient patient;

// we have a global for pacient size
int patientSize = 414;

// number of registered patients
int nrPatients = 0;

// array of all registered patients currently 100
patient patients[100] = {};


int maxPatients = 100;


// function for adding data in the file as a line
char * add_patient(){
    // we create a patient
    struct structPatient patient = {}; // empty patients

    printf("Name:");
    scanf("%s", patient.name);

    printf("CNP:");
    scanf("%s", patient.CNP);

    printf("Chronic diseases:");
    scanf("%s", patient.chronic_disease);

    printf("Diagnosis:");
    scanf("%s", patient.diagnosis);

    printf("Past interventions:");
    scanf("%s", patient.past_interventions);

    //we create a line for the file
    char stringPatient[patientSize];
    strcat(stringPatient, patient.name);
    strcat(stringPatient, ", ");
    strcat(stringPatient, patient.CNP);
    strcat(stringPatient, ", ");
    strcat(stringPatient, patient.chronic_disease);
    strcat(stringPatient, ", ");
    strcat(stringPatient, patient.diagnosis);
    strcat(stringPatient, ", ");
    strcat(stringPatient, patient.past_interventions);
    strcat(stringPatient, "\n");

    FILE* file_p;  //made a file pointer
    file_p = fopen(myFile, "a"); //open the file in append mode
    if (file_p == NULL) {
        return("File failed to open.\n");
    }
    fwrite(stringPatient, sizeof(char), strlen(stringPatient), file_p);
    fclose(file_p);
    return("\nPatient added successfully\n");
}


char * get_patients(){      // this function erases current array and rebuilds it from the file
    //initialize patients array

    printf("\nGetting patients from the file:\n\n");
    memset(patients, 0, maxPatients * patientSize);

    FILE * file_p;
    int max_char = 1024;
    char row[max_char];
    char * token;

    int counter = 0;

    file_p = fopen(myFile, "r");
    fgets(row, max_char, file_p);
    while (fgets(row, max_char, file_p)){          //!feof(file_p)

        printf("Patient [%d]: %s",counter, row);

        token = strtok(row, ", ");
        strcpy(&patients[counter].name, token);
        token = strtok(NULL, ", ");
        strcpy(&patients[counter].CNP, token);
        token = strtok(NULL, ", ");
        strcpy(&patients[counter].chronic_disease, token);
        token = strtok(NULL, ", ");
        strcpy(&patients[counter].diagnosis, token);
        token = strtok(NULL, ", ");
        strcpy(&patients[counter].past_interventions, token);

        counter++;
    }
    nrPatients = counter;

    return "\nGet patients done\n";

}


void * update_file(){
    char header[] = "Name, CNP, Chronic disease, Diagnostic, Past interventions\n";
    char stringPatients [patientSize * maxPatients + sizeof (header)];
    strcpy(stringPatients, "");
    strcat(stringPatients, header);
    for(int i = 0; i < nrPatients; i++){
        if(strcmp(patients[i].name, "deleted") != 0){
            strcat(stringPatients, patients[i].name);
            strcat(stringPatients, ", ");
            strcat(stringPatients, patients[i].CNP);
            strcat(stringPatients, ", ");
            strcat(stringPatients, patients[i].chronic_disease);
            strcat(stringPatients, ", ");
            strcat(stringPatients, patients[i].diagnosis);
            strcat(stringPatients, ", ");
            strcat(stringPatients, patients[i].past_interventions);
            strcat(stringPatients, "");
        }
    }
    FILE * file_p = fopen(myFile, "w");
    fwrite(stringPatients, sizeof(char), strlen(stringPatients), file_p);
    fclose(file_p);
}


int search_data(){
    int field;
    int ind;
    char name[100], CNP[14];
    get_patients(); // get the patients
    do{
        ind = -1;
        name[0] = '/0';
        CNP[0] = '/0';
        printf("\n====Choose search criteria====\n");
        printf("1. Name\n");
        printf("2. CNP\n");
        printf("3. Back to main menu\n");
        printf("Enter chosen action (1 - 3): ");
        scanf("%d", &field);
        printf("\n");
        switch(field){
            case 1:
                printf("Introduce patient name: ");
                scanf("%s", name);
                break;
            case 2:
                printf("Introduce patient CNP: ");
                scanf("%s", CNP);
                break;
            case 3:
                break;
            default:
                printf("Invalid action. Please try again.\n");
                break;
        }
        if(field != 3){
            printf("\nSearching... \n");
            for (int i = 0; i < nrPatients; ++i) {
                if(field == 1 && strcmp(patients[i].name, name) == 0){
                    ind = i;
                    break;
                }
                if(field == 2 && strcmp(patients[i].CNP, CNP) == 0){
                    ind = i;
                    break;
                }
            }
            if(ind > -1){
                printf("\nPatient found: \nPatient [%d]: %s, %s, %s, %s, %s\n",ind, patients[ind].name, patients[ind].CNP, patients[ind].chronic_disease, patients[ind].diagnosis, patients[ind].past_interventions);
                return ind;
            } else printf("\nPatient not found\n");
        }
    }while(field != 3);
    return ind;
}


char * edit_data(){
    printf("\nSearch patient you want to edit:\n");
    int field, index = search_data();
    char new_atr[100];
    if (index > -1) {

        do{
            printf("\n====Choose a field to edit====\n");
            printf("1. Name\n");
            printf("2. CNP\n");
            printf("3. Chronic disease\n");
            printf("4. Diagnosis\n");
            printf("5. Past interventions\n");
            printf("6. Back to main menu\n");
            printf("Enter chosen action (1 - 6): ");
            scanf("%d", &field);
            printf("\n");
            // in switch case I will use file functions to access and edit the data
            switch(field){

                case 1:
                    printf("\nNew name:\n");
                    scanf("%s", new_atr);
                    strcpy(patients[index].name, new_atr);
                    break;

                case 2:
                    printf("\nNew CNP:\n");
                    scanf("%s", new_atr);
                    strcpy(patients[index].CNP, new_atr);
                    break;

                case 3:
                    printf("\nNew chronic disease:\n");
                    scanf("%s", new_atr);
                    strcpy(patients[index].chronic_disease, new_atr);
                    break;

                case 4:
                    printf("\nNew diagnosis:\n");
                    scanf("%s", new_atr);
                    strcpy(patients[index].diagnosis, new_atr);
                    break;

                case 5:
                    printf("\nNew intervention:\n");
                    scanf("%s", new_atr);
                    strcpy(patients[index].past_interventions, new_atr);
                    break;

                case 6:
                    break;

                default:
                    printf("\nInvalid action. Please try again.\n");
                    break;
            }
            if(field != 6){
                printf("\n**%s, %s, %s, %s, %s\n",patients[index].name, patients[index].CNP, patients[index].chronic_disease, patients[index].diagnosis, patients[index].past_interventions);
                printf("Patient edited\n");
            }

        }while(field != 6);
        update_file();
        return("\nEdit successful\n");
    } else return("\nPatient not found\n");
}


char * delete_data(){
    printf("\nSearch patient you want to delete:\n");
    int index = search_data();
    printf("\nDeleting...\n");
    if(index > -1){
        strcpy(patients[index].name, "deleted");
        update_file();
        return("\nPatient deleted successfully\n");
    }
    return("\nDelete error\n");

}



int main() {

    // check if file exists, if not, we create it
    FILE * file_p = fopen(myFile, "r");
    if(file_p == NULL){
        file_p = fopen(myFile, "w");
        fputs("Name, CNP, Chronic disease, Diagnostic, Past interventions\n", file_p);
        fclose(file_p);
    }
    else{
        fclose(file_p);
    }

    int chosen_action;


    do{
        printf("\n====Choose an action====\n");
        printf("1. Add new patient\n");
        printf("2. Edit data patient\n");
        printf("3. Searching a patient\n");
        printf("4. Delete a patient\n");
        printf("5. Get all patients\n");
        printf("6. Exit\n");
        printf("Enter chosen action (1 - 5): ");
        scanf("%d", &chosen_action);
        printf("\n");
        switch(chosen_action){
            case 1:
                printf(add_patient());
                //printf("\n");
                break;
            case 2:
                printf(edit_data());
                break;
            case 3:
                search_data();
                break;
            case 4:
                printf(delete_data());
                break;
            case 5:
                printf(get_patients());
                break;
            case 6:
                break;
            default:
                printf("Invalid action. Please try again.\n");
                break;
        }

    }while(chosen_action != 6);

    return 0;
}

