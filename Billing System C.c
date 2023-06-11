#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int maximumLenghtOfProductName = 50;

struct product{
    float price;
    char *name;
};

struct node{
    struct product val;
    struct node* next;
};

struct listOfProducts{
    struct node* head;
};

void addProductToList(struct listOfProducts *listOfRealProducts,struct product productToAddToList){
    struct node *newNode = (struct node *) malloc(sizeof(struct node)); //creates a new node to be added to the list
    newNode->val = productToAddToList;
    newNode->next = NULL; // Adds the values to the new node
    if (listOfRealProducts->head == NULL)     //if head is NULL, it is an empty list
    {
        listOfRealProducts->head = newNode;
        return;

    } else {
        struct node *current = listOfRealProducts->head;
        while (current->next != NULL) {
            current = current->next; //traverses the list to the last element
        }
        //add the newNode at the end of the linked list
        current->next = newNode;
    }
}


struct listOfProducts* readTheListOfProductsFromFile() {
    struct listOfProducts *listOfRealProducts = (struct listOfProducts *)malloc(sizeof(struct listOfProducts)); //creates a new list

    FILE *fp = fopen("products.csv", "r");//opens the file with products
    if (fp != NULL) {
        struct product tempProduct; //creates a temporary object in which to hold the product read
        char *line = (char *) malloc(sizeof(char) * 60), *tok;
        while (fgets(line, 60, fp)) { //While it reads the file and finds smth
            tok = strtok(line, ",");
            tempProduct.name = strdup(tok);  //Get the name of the product from list
            tok = strtok(NULL, "\n");
            tempProduct.price = atof(tok); //Get the price of the product from list
            addProductToList(listOfRealProducts,tempProduct);
        }
    }
    return listOfRealProducts;
}


void addProduct(struct listOfProducts *listOfRealProducts)
{
    struct product newProduct; //creates a temporary product to be added to the list

    printf("What is the name of the product? Input: \n");
    getchar();//to get rid of "evil" whitespace
    getline(&newProduct.name, (size_t *) &maximumLenghtOfProductName, stdin);
    newProduct.name[strcspn(newProduct.name, "\n")]=0; //removes the newline character in the product name

    printf("What is the price of your product? Input in format x.y: \n");
    scanf("%f",&newProduct.price);
    addProductToList(listOfRealProducts,newProduct);
}


void showProduct(struct product productToShow,int id){
    printf("%d. %s  Price: %.2lf \n",id,productToShow.name,productToShow.price);
}

void showProductsFromList(struct listOfProducts *listOfRealProducts)
{
    struct listOfProducts localList = *listOfRealProducts;
    int id=1;
    while(localList.head!=NULL){       //traverses the list and shows every product
        showProduct(localList.head->val,id++);
        localList.head=localList.head->next;
    }
}


void writeProductsToFile(struct listOfProducts *listOfRealProducts){
    FILE *fp = fopen("products.csv", "w");
    while(listOfRealProducts->head!=NULL) //traverses the list and writes every product from it in the products.csv file
    {
        fprintf(fp,"%s,%.3lf\n",listOfRealProducts->head->val.name,listOfRealProducts->head->val.price);
        listOfRealProducts->head=listOfRealProducts->head->next;
    }
}

void updateProduct(struct listOfProducts *listOfRealProducts){
    showProductsFromList(listOfRealProducts);

    int indexOfProduct,i=1;
    printf("Which product do you want to update? Input the id of the product:");
    scanf("%d",&indexOfProduct);

    struct node *current = listOfRealProducts->head; //copies the head to a new node and goes to the n-th node(product) in the list
    while (indexOfProduct!=i) {
        current = current->next;
        i++;
    }
    int option;
    printf("Do you wanna update the price or name?\n"
           "Pick 1 for name and 2 for price. Input:");
    scanf("%d",&option);
    switch (option) {
        case 1:{
            char name[50];
            printf("Input the new name:\n");
            getchar();
            fgets(name, sizeof(name), stdin);
            printf("%s\n",name);
            name[strcspn(name, "\n")]=0;
            current->val.name=NULL;
            current->val.name= strdup(name);
            return;
        }
        case 2:{
            float price;
            printf("Input the new price in format x.y:\n");
            scanf("%f",&price);
            current->val.price= price;
            return;
        }
        default:{
            printf("Not a valid choice. Try again.\n");
            updateProduct(listOfRealProducts);
            break;

        }
    }
}

void deleteProductFromList(struct listOfProducts *listOfRealProducts,int id){
    struct node* temp = listOfRealProducts->head; // Creating a temporary node
    id=id-1; //The linked list "acts" like an array so we decrease the id by 1
    int i;
    if (id == 0) {
        listOfRealProducts->head = listOfRealProducts->head->next; // Advancing the head pointer
        temp->next = NULL;
        free(temp); // Node is deleted
    }
    else {
        for (i = 0; i < id-1; i++) {
            temp = temp->next;  // Advancing the head pointer to the point we need
        }
        struct node* del= temp->next; //Node to delete
        temp->next = temp->next->next;
        del->next = NULL;
        free(del); // Node is deleted
    }
    return;
}

void deleteProduct(struct listOfProducts *listOfRealProducts){
    showProductsFromList(listOfRealProducts);
    int indexOfProduct;
    printf("Which product do you want to delete? Input the id of the product:");
    scanf("%d",&indexOfProduct);
    deleteProductFromList(listOfRealProducts,indexOfProduct);
    printf("Delete Successful. Press any key to go back\n");
    getchar();getchar();
}


void addProductMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Add Product       *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input: ");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            addProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
        }
        default: {
            printf("Not a valid choice. Try again.\n");
            addProductMenu(listOfRealProducts);
            break;
        }
    }
}

void updateProductMenu(struct listOfProducts *listOfRealProducts){
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Update Product    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            updateProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            updateProductMenu(listOfRealProducts);
            break;
        }
    }
}

void deleteProductMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Delete Product    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            deleteProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
            break;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            deleteProductMenu(listOfRealProducts);
            break;
        }
    }
}

void showProductsMenu(struct listOfProducts *listOfRealProducts) {
    printf("The list of available products:\n");
    showProductsFromList(listOfRealProducts);
    printf("Press any key to go back to the menu\n");
    getchar();//used to catch the newline character
    getchar();

}

void createInvoice(struct listOfProducts *listOfRealProducts){
    FILE *fp = fopen("invoice.txt","w");
    int id,option=1;
    putc('*',fp);
    for (int i = 1; i <100; i ++)
        putc('-',fp);  //creates the top border
    putc('*',fp);
    putc('\n',fp);

    while(option==1) {
        printf("Press 1 to add product to invoice or press any key to quit\n");getchar();
        scanf("%d",&option);


        if(option!=1)
        {  putc('*',fp);
            for (int i = 1; i <100; i ++) // creates the bottom border when the user exists
                putc('-',fp);
            putc('*',fp);
            putc('\n',fp);
            return;}

        showProductsFromList(listOfRealProducts);

        printf("\nWhat Product do you want to add to the invoice? Input the id of the product:");
        scanf("%d", &id);
        printf("\nHow many times do you want to add the product on the invoice? Input:");
        int timesOfProductUsed;
        scanf("%d",&timesOfProductUsed);
        struct node *current = listOfRealProducts->head;
        int i=1;                                                                                            //calculates and adds to the invoice.txt file the product
        while (id!=i) {
            current = current->next;//finds the product in the list
            i++;
        }
        fprintf(fp,"|%-50s *%-30d =%-15f|\n",current->val.name,timesOfProductUsed,current->val.price*(float)timesOfProductUsed);
    }

}


void createInvoiceMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;
    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Create Invoice    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);

    system("clear");
    switch (option) {
        case 1: {
            createInvoice(listOfRealProducts);
            break;
        }
        case 2: {
            return;
            break;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            createInvoiceMenu(listOfRealProducts);
            break;
        }
    }
}


void welcomeMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;
    while (option!=99) {
        printf("*----------------------*\n");
        printf("*       Welcome        *\n");
        printf("*                      *\n");
        printf("*   Choose operation   *\n");
        printf("*  1)Add product       *\n");
        printf("*  2)Update product    *\n");
        printf("*  3)Show products     *\n");
        printf("*  4)Delete product    *\n");
        printf("*  5)Create Invoice    *\n");
        printf("*  6)Exit app          *\n");
        printf("*                      *\n");
        printf("*----------------------*\n");
        printf("input:");
        scanf("%d", &option);

        system("clear");
        switch (option) {
            case 1: {
                addProductMenu(listOfRealProducts);
                break;
            }
            case 2: {
                updateProductMenu(listOfRealProducts);
                break;
            }
            case 3:{
                showProductsMenu(listOfRealProducts);
                break;
            }
            case 4: {
                deleteProductMenu(listOfRealProducts);
                break;
            }
            case 5: {
                createInvoiceMenu(listOfRealProducts);
                break;
            }
            case 6: {
                return;
            }
            default: {
                printf("Not a valid choice. Try again.\n");
                break;
            }
        }
    }
}

int main() {
    struct listOfProducts *listOfRealProducts = readTheListOfProductsFromFile();
    welcomeMenu(listOfRealProducts);
    writeProductsToFile(listOfRealProducts);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int maximumLenghtOfProductName = 50;

struct product{
    float price;
    char *name;
};

struct node{
    struct product val;
    struct node* next;
};

struct listOfProducts{
    struct node* head;
};

void addProductToList(struct listOfProducts *listOfRealProducts,struct product productToAddToList){
    struct node *newNode = (struct node *) malloc(sizeof(struct node)); //creates a new node to be added to the list
    newNode->val = productToAddToList;
    newNode->next = NULL; // Adds the values to the new node
    if (listOfRealProducts->head == NULL)     //if head is NULL, it is an empty list
    {
        listOfRealProducts->head = newNode;
        return;

    } else {
        struct node *current = listOfRealProducts->head;
        while (current->next != NULL) {
            current = current->next; //traverses the list to the last element
        }
        //add the newNode at the end of the linked list
        current->next = newNode;
    }
}


struct listOfProducts* readTheListOfProductsFromFile() {
    struct listOfProducts *listOfRealProducts = (struct listOfProducts *)malloc(sizeof(struct listOfProducts)); //creates a new list

    FILE *fp = fopen("products.csv", "r");//opens the file with products
    if (fp != NULL) {
        struct product tempProduct; //creates a temporary object in which to hold the product read
        char *line = (char *) malloc(sizeof(char) * 60), *tok;
        while (fgets(line, 60, fp)) { //While it reads the file and finds smth
            tok = strtok(line, ",");
            tempProduct.name = strdup(tok);  //Get the name of the product from list
            tok = strtok(NULL, "\n");
            tempProduct.price = atof(tok); //Get the price of the product from list
            addProductToList(listOfRealProducts,tempProduct);
        }
    }
    return listOfRealProducts;
}


void addProduct(struct listOfProducts *listOfRealProducts)
{
    struct product newProduct; //creates a temporary product to be added to the list

    printf("What is the name of the product? Input: \n");
    getchar();//to get rid of "evil" whitespace
    getline(&newProduct.name, (size_t *) &maximumLenghtOfProductName, stdin);
    newProduct.name[strcspn(newProduct.name, "\n")]=0; //removes the newline character in the product name

    printf("What is the price of your product? Input in format x.y: \n");
    scanf("%f",&newProduct.price);
    addProductToList(listOfRealProducts,newProduct);
}


void showProduct(struct product productToShow,int id){
    printf("%d. %s  Price: %.2lf \n",id,productToShow.name,productToShow.price);
}

void showProductsFromList(struct listOfProducts *listOfRealProducts)
{
    struct listOfProducts localList = *listOfRealProducts;
    int id=1;
    while(localList.head!=NULL){       //traverses the list and shows every product
        showProduct(localList.head->val,id++);
        localList.head=localList.head->next;
    }
}


void writeProductsToFile(struct listOfProducts *listOfRealProducts){
    FILE *fp = fopen("products.csv", "w");
    while(listOfRealProducts->head!=NULL) //traverses the list and writes every product from it in the products.csv file
    {
        fprintf(fp,"%s,%.3lf\n",listOfRealProducts->head->val.name,listOfRealProducts->head->val.price);
        listOfRealProducts->head=listOfRealProducts->head->next;
    }
}

void updateProduct(struct listOfProducts *listOfRealProducts){
    showProductsFromList(listOfRealProducts);

    int indexOfProduct,i=1;
    printf("Which product do you want to update? Input the id of the product:");
    scanf("%d",&indexOfProduct);

    struct node *current = listOfRealProducts->head; //copies the head to a new node and goes to the n-th node(product) in the list
    while (indexOfProduct!=i) {
        current = current->next;
        i++;
    }
    int option;
    printf("Do you wanna update the price or name?\n"
           "Pick 1 for name and 2 for price. Input:");
    scanf("%d",&option);
    switch (option) {
        case 1:{
            char name[50];
            printf("Input the new name:\n");
            getchar();
            fgets(name, sizeof(name), stdin);
            printf("%s\n",name);
            name[strcspn(name, "\n")]=0;
            current->val.name=NULL;
            current->val.name= strdup(name);
            return;
        }
        case 2:{
            float price;
            printf("Input the new price in format x.y:\n");
            scanf("%f",&price);
            current->val.price= price;
            return;
        }
        default:{
            printf("Not a valid choice. Try again.\n");
            updateProduct(listOfRealProducts);
            break;

        }
    }
}

void deleteProductFromList(struct listOfProducts *listOfRealProducts,int id){
    struct node* temp = listOfRealProducts->head; // Creating a temporary node
    id=id-1; //The linked list "acts" like an array so we decrease the id by 1
    int i;
    if (id == 0) {
        listOfRealProducts->head = listOfRealProducts->head->next; // Advancing the head pointer
        temp->next = NULL;
        free(temp); // Node is deleted
    }
    else {
        for (i = 0; i < id-1; i++) {
            temp = temp->next;  // Advancing the head pointer to the point we need
        }
        struct node* del= temp->next; //Node to delete
        temp->next = temp->next->next;
        del->next = NULL;
        free(del); // Node is deleted
    }
    return;
}

void deleteProduct(struct listOfProducts *listOfRealProducts){
    showProductsFromList(listOfRealProducts);
    int indexOfProduct;
    printf("Which product do you want to delete? Input the id of the product:");
    scanf("%d",&indexOfProduct);
    deleteProductFromList(listOfRealProducts,indexOfProduct);
    printf("Delete Successful. Press any key to go back\n");
    getchar();getchar();
}


void addProductMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Add Product       *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input: ");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            addProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
        }
        default: {
            printf("Not a valid choice. Try again.\n");
            addProductMenu(listOfRealProducts);
            break;
        }
    }
}

void updateProductMenu(struct listOfProducts *listOfRealProducts){
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Update Product    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            updateProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            updateProductMenu(listOfRealProducts);
            break;
        }
    }
}

void deleteProductMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Delete Product    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            deleteProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
            break;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            deleteProductMenu(listOfRealProducts);
            break;
        }
    }
}

void showProductsMenu(struct listOfProducts *listOfRealProducts) {
    printf("The list of available products:\n");
    showProductsFromList(listOfRealProducts);
    printf("Press any key to go back to the menu\n");
    getchar();//used to catch the newline character
    getchar();

}

void createInvoice(struct listOfProducts *listOfRealProducts){
    FILE *fp = fopen("invoice.txt","w");
    int id,option=1;
    putc('*',fp);
    for (int i = 1; i <100; i ++)
        putc('-',fp);  //creates the top border
    putc('*',fp);
    putc('\n',fp);

    while(option==1) {
        printf("Press 1 to add product to invoice or press any key to quit\n");getchar();
        scanf("%d",&option);


        if(option!=1)
        {  putc('*',fp);
            for (int i = 1; i <100; i ++) // creates the bottom border when the user exists
                putc('-',fp);
            putc('*',fp);
            putc('\n',fp);
            return;}

        showProductsFromList(listOfRealProducts);

        printf("\nWhat Product do you want to add to the invoice? Input the id of the product:");
        scanf("%d", &id);
        printf("\nHow many times do you want to add the product on the invoice? Input:");
        int timesOfProductUsed;
        scanf("%d",&timesOfProductUsed);
        struct node *current = listOfRealProducts->head;
        int i=1;                                                                                            //calculates and adds to the invoice.txt file the product
        while (id!=i) {
            current = current->next;//finds the product in the list
            i++;
        }
        fprintf(fp,"|%-50s *%-30d =%-15f|\n",current->val.name,timesOfProductUsed,current->val.price*(float)timesOfProductUsed);
    }

}


void createInvoiceMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;
    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Create Invoice    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);

    system("clear");
    switch (option) {
        case 1: {
            createInvoice(listOfRealProducts);
            break;
        }
        case 2: {
            return;
            break;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            createInvoiceMenu(listOfRealProducts);
            break;
        }
    }
}


void welcomeMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;
    while (option!=99) {
        printf("*----------------------*\n");
        printf("*       Welcome        *\n");
        printf("*                      *\n");
        printf("*   Choose operation   *\n");
        printf("*  1)Add product       *\n");
        printf("*  2)Update product    *\n");
        printf("*  3)Show products     *\n");
        printf("*  4)Delete product    *\n");
        printf("*  5)Create Invoice    *\n");
        printf("*  6)Exit app          *\n");
        printf("*                      *\n");
        printf("*----------------------*\n");
        printf("input:");
        scanf("%d", &option);

        system("clear");
        switch (option) {
            case 1: {
                addProductMenu(listOfRealProducts);
                break;
            }
            case 2: {
                updateProductMenu(listOfRealProducts);
                break;
            }
            case 3:{
                showProductsMenu(listOfRealProducts);
                break;
            }
            case 4: {
                deleteProductMenu(listOfRealProducts);
                break;
            }
            case 5: {
                createInvoiceMenu(listOfRealProducts);
                break;
            }
            case 6: {
                return;
            }
            default: {
                printf("Not a valid choice. Try again.\n");
                break;
            }
        }
    }
}

int main() {
    struct listOfProducts *listOfRealProducts = readTheListOfProductsFromFile();
    welcomeMenu(listOfRealProducts);
    writeProductsToFile(listOfRealProducts);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int maximumLenghtOfProductName = 50;

struct product{
    float price;
    char *name;
};

struct node{
    struct product val;
    struct node* next;
};

struct listOfProducts{
    struct node* head;
};

void addProductToList(struct listOfProducts *listOfRealProducts,struct product productToAddToList){
    struct node *newNode = (struct node *) malloc(sizeof(struct node)); //creates a new node to be added to the list
    newNode->val = productToAddToList;
    newNode->next = NULL; // Adds the values to the new node
    if (listOfRealProducts->head == NULL)     //if head is NULL, it is an empty list
    {
        listOfRealProducts->head = newNode;
        return;

    } else {
        struct node *current = listOfRealProducts->head;
        while (current->next != NULL) {
            current = current->next; //traverses the list to the last element
        }
        //add the newNode at the end of the linked list
        current->next = newNode;
    }
}


struct listOfProducts* readTheListOfProductsFromFile() {
    struct listOfProducts *listOfRealProducts = (struct listOfProducts *)malloc(sizeof(struct listOfProducts)); //creates a new list

    FILE *fp = fopen("products.csv", "r");//opens the file with products
    if (fp != NULL) {
        struct product tempProduct; //creates a temporary object in which to hold the product read
        char *line = (char *) malloc(sizeof(char) * 60), *tok;
        while (fgets(line, 60, fp)) { //While it reads the file and finds smth
            tok = strtok(line, ",");
            tempProduct.name = strdup(tok);  //Get the name of the product from list
            tok = strtok(NULL, "\n");
            tempProduct.price = atof(tok); //Get the price of the product from list
            addProductToList(listOfRealProducts,tempProduct);
        }
    }
    return listOfRealProducts;
}


void addProduct(struct listOfProducts *listOfRealProducts)
{
    struct product newProduct; //creates a temporary product to be added to the list

    printf("What is the name of the product? Input: \n");
    getchar();//to get rid of "evil" whitespace
    getline(&newProduct.name, (size_t *) &maximumLenghtOfProductName, stdin);
    newProduct.name[strcspn(newProduct.name, "\n")]=0; //removes the newline character in the product name

    printf("What is the price of your product? Input in format x.y: \n");
    scanf("%f",&newProduct.price);
    addProductToList(listOfRealProducts,newProduct);
}


void showProduct(struct product productToShow,int id){
    printf("%d. %s  Price: %.2lf \n",id,productToShow.name,productToShow.price);
}

void showProductsFromList(struct listOfProducts *listOfRealProducts)
{
    struct listOfProducts localList = *listOfRealProducts;
    int id=1;
    while(localList.head!=NULL){       //traverses the list and shows every product
        showProduct(localList.head->val,id++);
        localList.head=localList.head->next;
    }
}


void writeProductsToFile(struct listOfProducts *listOfRealProducts){
    FILE *fp = fopen("products.csv", "w");
    while(listOfRealProducts->head!=NULL) //traverses the list and writes every product from it in the products.csv file
    {
        fprintf(fp,"%s,%.3lf\n",listOfRealProducts->head->val.name,listOfRealProducts->head->val.price);
        listOfRealProducts->head=listOfRealProducts->head->next;
    }
}

void updateProduct(struct listOfProducts *listOfRealProducts){
    showProductsFromList(listOfRealProducts);

    int indexOfProduct,i=1;
    printf("Which product do you want to update? Input the id of the product:");
    scanf("%d",&indexOfProduct);

    struct node *current = listOfRealProducts->head; //copies the head to a new node and goes to the n-th node(product) in the list
    while (indexOfProduct!=i) {
        current = current->next;
        i++;
    }
    int option;
    printf("Do you wanna update the price or name?\n"
           "Pick 1 for name and 2 for price. Input:");
    scanf("%d",&option);
    switch (option) {
        case 1:{
            char name[50];
            printf("Input the new name:\n");
            getchar();
            fgets(name, sizeof(name), stdin);
            printf("%s\n",name);
            name[strcspn(name, "\n")]=0;
            current->val.name=NULL;
            current->val.name= strdup(name);
            return;
        }
        case 2:{
            float price;
            printf("Input the new price in format x.y:\n");
            scanf("%f",&price);
            current->val.price= price;
            return;
        }
        default:{
            printf("Not a valid choice. Try again.\n");
            updateProduct(listOfRealProducts);
            break;

        }
    }
}

void deleteProductFromList(struct listOfProducts *listOfRealProducts,int id){
    struct node* temp = listOfRealProducts->head; // Creating a temporary node
    id=id-1; //The linked list "acts" like an array so we decrease the id by 1
    int i;
    if (id == 0) {
        listOfRealProducts->head = listOfRealProducts->head->next; // Advancing the head pointer
        temp->next = NULL;
        free(temp); // Node is deleted
    }
    else {
        for (i = 0; i < id-1; i++) {
            temp = temp->next;  // Advancing the head pointer to the point we need
        }
        struct node* del= temp->next; //Node to delete
        temp->next = temp->next->next;
        del->next = NULL;
        free(del); // Node is deleted
    }
    return;
}

void deleteProduct(struct listOfProducts *listOfRealProducts){
    showProductsFromList(listOfRealProducts);
    int indexOfProduct;
    printf("Which product do you want to delete? Input the id of the product:");
    scanf("%d",&indexOfProduct);
    deleteProductFromList(listOfRealProducts,indexOfProduct);
    printf("Delete Successful. Press any key to go back\n");
    getchar();getchar();
}


void addProductMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Add Product       *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input: ");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            addProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
        }
        default: {
            printf("Not a valid choice. Try again.\n");
            addProductMenu(listOfRealProducts);
            break;
        }
    }44
}

void updateProductMenu(struct listOfProducts *listOfRealProducts){
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Update Product    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            updateProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            updateProductMenu(listOfRealProducts);
            break;
        }
    }
}

void deleteProductMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;

    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Delete Product    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);
    system("clear");
    switch (option) {
        case 1: {
            deleteProduct(listOfRealProducts);
            break;
        }
        case 2: {
            return;
            break;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            deleteProductMenu(listOfRealProducts);
            break;
        }
    }
}

void showProductsMenu(struct listOfProducts *listOfRealProducts) {
    printf("The list of available products:\n");
    showProductsFromList(listOfRealProducts);
    printf("Press any key to go back to the menu\n");
    getchar();//used to catch the newline character
    getchar();

}

void createInvoice(struct listOfProducts *listOfRealProducts){
    FILE *fp = fopen("invoice.txt","w");
    int id,option=1;
    putc('*',fp);
    for (int i = 1; i <100; i ++)
        putc('-',fp);  //creates the top border
    putc('*',fp);
    putc('\n',fp);

    while(option==1) {
        printf("Press 1 to add product to invoice or press any key to quit\n");getchar();
        scanf("%d",&option);


        if(option!=1)
        {  putc('*',fp);
            for (int i = 1; i <100; i ++) // creates the bottom border when the user exists
                putc('-',fp);
            putc('*',fp);
            putc('\n',fp);
            return;}

        showProductsFromList(listOfRealProducts);

        printf("\nWhat Product do you want to add to the invoice? Input the id of the product:");
        scanf("%d", &id);
        printf("\nHow many times do you want to add the product on the invoice? Input:");
        int timesOfProductUsed;
        scanf("%d",&timesOfProductUsed);
        struct node *current = listOfRealProducts->head;
        int i=1;                                                                                            //calculates and adds to the invoice.txt file the product
        while (id!=i) {
            current = current->next;//finds the product in the list
            i++;
        }
        fprintf(fp,"|%-50s *%-30d =%-15f|\n",current->val.name,timesOfProductUsed,current->val.price*(float)timesOfProductUsed);
    }

}


void createInvoiceMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;
    printf("*----------------------*\n");
    printf("*                      *\n");
    printf("*   Choose operation   *\n");
    printf("*  1)Create Invoice    *\n");
    printf("*  2)Back              *\n");
    printf("*                      *\n");
    printf("*----------------------*\n");
    printf("input:");
    scanf("%d",&option);

    system("clear");
    switch (option) {
        case 1: {
            createInvoice(listOfRealProducts);
            break;
        }
        case 2: {
            return;
            break;
        }
        default: {

            printf("Not a valid choice. Try again.\n");
            createInvoiceMenu(listOfRealProducts);
            break;
        }
    }
}


void welcomeMenu(struct listOfProducts *listOfRealProducts) {
    int option = 0;
    while (option!=99) {
        printf("*----------------------*\n");
        printf("*       Welcome        *\n");
        printf("*                      *\n");
        printf("*   Choose operation   *\n");
        printf("*  1)Add product       *\n");
        printf("*  2)Update product    *\n");
        printf("*  3)Show products     *\n");
        printf("*  4)Delete product    *\n");
        printf("*  5)Create Invoice    *\n");
        printf("*  6)Exit app          *\n");
        printf("*                      *\n");
        printf("*----------------------*\n");
        printf("input:");
        scanf("%d", &option);

        system("clear");
        switch (option) {
            case 1: {
                addProductMenu(listOfRealProducts);
                break;
            }
            case 2: {
                updateProductMenu(listOfRealProducts);
                break;
            }
            case 3:{
                showProductsMenu(listOfRealProducts);
                break;
            }
            case 4: {
                deleteProductMenu(listOfRealProducts);
                break;
            }
            case 5: {
                createInvoiceMenu(listOfRealProducts);
                break;
            }
            case 6: {
                return;
            }
            default: {
                printf("Not a valid choice. Try again.\n");
                break;
            }
        }
    }
}

int main() {
    struct listOfProducts *listOfRealProducts = readTheListOfProductsFromFile();
    welcomeMenu(listOfRealProducts);
    writeProductsToFile(listOfRealProducts);
    return 0;
}
