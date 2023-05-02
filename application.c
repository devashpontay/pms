#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
//Making some function reusable
typedef struct Account {
    char idNum[10];
    char fullname[31];
    char username[31];
    char password[20];
    int key;
    struct Account *next;
} Account;

Account *first_account = NULL; // Initialize a pointer to the first account in the linked list


typedef struct PreserveAccountData {
    char idNum[10];
    char link[50];
    char username[31];
    char pw[20];
    int key;
    struct PreserveAccountData *next;
} PAD;

PAD *insideFirstAccount = NULL;

int genIdNum() {
    return (rand() % 9999) + 1;  // generate a random number between 1 and 9999
}

short int userStatCode = 200, singleEncrypt = 100;
short int listStatCode = 201, multipleEncrypt = 101;
short int key;
char activeUserId[10];
int attempt = 0;

//FUNCTION FORWARD DECLARATION

int retrieve(char *username, char *password);
void retrievePreservedAcc();
void preserveNewAccData(PAD obj);
int operationMenuUI();
void encryption(short int statCode);
void saveAccount(int statCode);
void operationMenu();
void saveAccount(int statCode);
void addAccount();
int loginMenu();
Account decryption(Account p);
PAD decryptionForPAD(PAD p);
void retrievePreservedAcc();
void login();
void preserveNewAccData(PAD obj);

//------------------------------------------------
//------------------------------------------------


int main() {
    // WRITE CODE HERE
    // connected to you billona sarap mo
    // connected ~jerry

    srand(time(NULL));
    while(1) {

        switch(loginMenu()) {
            case 1:
                system("cls");
                //retrive();
                login();
                break;
            case 2:
                system("cls");
                //printf("Create Vault Account function goes here.\n");
                addAccount();
                encryption(singleEncrypt);
                saveAccount(userStatCode);
                free(first_account);
                break;

            case 3:
                printf("Exiting the program...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;

}






void login()
{
    Account acc;

    printf("\n==================\n");
    printf("\nEnter username: ");
    scanf("%30s", acc.username);
    printf("\nEnter password: ");
    scanf("%19s", acc.password);

    int isValid = retrieve(acc.username, acc.password);

    if(isValid == 1){
        printf("Successful!\n");
        system("pause");
        retrievePreservedAcc();
        operationMenu();
    }
    else{
        printf("Failed!");
        system("pause");
        return;
    }

}

//Function to call after retrieval
int operationMenuUI(){
    system("cls");
    int op;

    printf("\n===== OPERATION MENU =====\n");
    printf("1. Add new account\n");
    printf("2. Update existing account\n");
    printf("3. Display accounts\n");
    printf("4. Delete existing account\n");
    printf("5. Exit and Save\n\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    return op;
}

void operationMenu(){
    PAD obj;
    while(1){
            switch(operationMenuUI()) {
                case 1:
                    system("cls");
                    printf("WELCOME TO YOURS TRULY! \n\n");
                    strcpy(obj.idNum, activeUserId);
                    printf("LINK: ");scanf("%s", obj.link);
                    printf("username: ");scanf("%s", obj.username);
                    printf("password: ");scanf("%s", obj.pw);
                    obj.key = key;
                    system("pause");
                    preserveNewAccData(obj);
                    break;

                case 2:
                    system("cls");
                    printf("Update function goes here!");
                    break;
                case 3:
                    system("cls");
                    //display function here
                    break;
                case 4:
                    system("cls");
                    printf("Delete function goes here!");
                    break;
                case 5:
                    printf("Saving then exiting the program...\n");
                    system("pause");
                    encryption(multipleEncrypt);
                    saveAccount(listStatCode);
                    exit(0);
                    break;
                default:
                    printf("Invalid choice! Please try again.\n");
                    break;
                }
        }
}

void saveAccount(int statCode){
    // This function saves all the account records to a file named "accountsDB.txt".
    // It appends new records to the end of the file if it already exists.

    FILE *fs;

    if(statCode == 200) {
        fs = fopen("accountsDB.txt", "a"); // open the file in "append" mode to add new records to the end of the file
        Account *p;
        p = first_account;
        fprintf(fs, "%s@%s@%s@%s@%d\n", p->idNum, p->fullname, p->username, p->password, p->key);
    }else {
        fs = fopen("preserveAccDataDB.txt", "w");
        PAD *p;
        p = insideFirstAccount;
        while(p != NULL) {
            fprintf(fs, "%s@%s@%s@%s@%d\n", p->idNum, p->link, p->username, p->pw, p->key);
            p = p->next;
        }
    }

    fclose(fs);
    //printf("Successfully saved all accounts to file.\n");
}


void addAccount() {
    Account *new_account = (Account *) malloc(sizeof(Account)); //create struct and populate its fields
    char confirm_password[20];
    char ch;
    int i = 0;
    sprintf(new_account->idNum, "%d", genIdNum());

    printf("Enter full name: ");
    scanf(" %[^\n]", new_account->fullname);

    printf("Enter username: ");
    scanf("%s", new_account->username);

    printf("Enter password: ");
    while ((ch = getch()) != '\r') {
        if (i < 20 && ch != '\b') {
            new_account->password[i++] = ch;
            printf("*");
        } else if (i > 0 && ch == '\b') {
            i--;
            printf("\b \b");
        }
    }
    new_account->password[i] = '\0';

    printf("\nConfirm password: ");
    i = 0;
    while ((ch = getch()) != '\r') {
        if (i < 20 && ch != '\b') {
            confirm_password[i++] = ch;
            printf("*");
        } else if (i > 0 && ch == '\b') {
            i--;
            printf("\b \b");
        }
    }
    confirm_password[i] = '\0';

    if (strcmp(new_account->password, confirm_password) != 0) {
        printf("\nPasswords do not match. Account not created.\n");
        system("pause");
        free(new_account);
        return;
    }

    new_account->key = rand() % 56 + 1;

    new_account->next = first_account; // next pointer of the new account to the current first account

    first_account = new_account; // first account pointer to the new account

    printf("\n\nAccount added successfully!\n");
    system("pause");
}

int loginMenu() {
    system("cls");
    int op;

    printf("\n===== MENU =====\n");
    printf("1. Log in\n");
    printf("2. Create Vault Account\n");
    printf("3. Exit\n\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    return op;
}


void encryption(short int statCode) {


    if(statCode == 100) {
        Account *p;
        p = first_account;
        for (int i = 0; i < 4; i++) {
            char *field = NULL;
            int is_string = 0;

            // Determine which field to encrypt
            switch (i) {
                case 0:
                    field = p->idNum;
                    is_string = 1;
                    break;
                case 1:
                    field = p->fullname;
                    is_string = 1;
                    break;
                case 2:
                    field = p->username;
                    is_string = 1;
                    break;
                case 3:
                    field = p->password;
                    is_string = 1;
                    break;
                default:
                    break;
            }

            if (is_string) {
            // encrypt the field
                for (int j = 0; field[j] != '\0'; j++) {
                    int ascii_code = (int) field[j];
                    field[j] = (char) ascii_code + p->key;
                }
            }
        }

    }else {
        PAD *p;
        p = insideFirstAccount;
        while(p != NULL) {
            for (int i = 0; i < 4; i++) {
                char *field = NULL;
                int is_string = 0;

                // Determine which field to encrypt
                switch (i) {
                    case 0:
                        field = p->idNum;
                        is_string = 1;
                        break;
                    case 1:
                        field = p->link;
                        is_string = 1;
                        break;
                    case 2:
                        field = p->username;
                        is_string = 1;
                        break;
                    case 3:
                        field = p->pw;
                        is_string = 1;
                        break;
                    default:
                        break;
                }

                if (is_string) {
                // encrypt the field
                    for (int j = 0; field[j] != '\0'; j++) {
                        int ascii_code = (int) field[j];
                        field[j] = (char) ascii_code + p->key;
                    }
                }
            }
            p = p->next;
        }
    }
}

Account decryption(Account p) {

    for (int i = 0; i < 4; i++) {
        char *field = NULL;
        int is_string = 0;

        // Determine which field to decrypt
        switch (i) {
            case 0:
                field = p.idNum;
                is_string = 1;
                break;
            case 1:
                field = p.fullname;
                is_string = 1;
                break;
            case 2:
                field = p.username;
                is_string = 1;
                break;
            case 3:
                field = p.password;
                is_string = 1;
                break;
            default:
                break;
        }

        if (is_string) {
            //decrypt the field
            for (int j = 0; field[j] != '\0'; j++) {
                int ascii_code = (int) field[j];
                field[j] = (char) ascii_code - p.key;
            }
        }
    }
    return p;
}

PAD decryptionForPAD(PAD p) {

    for (int i = 0; i < 4; i++) {
        char *field = NULL;
        int is_string = 0;

        // Determine which field to decrypt
        switch (i) {
            case 0:
                field = p.idNum;
                is_string = 1;
                break;
            case 1:
                field = p.link;
                is_string = 1;
                break;
            case 2:
                field = p.username;
                is_string = 1;
                break;
            case 3:
                field = p.pw;
                is_string = 1;
                break;
            default:
                break;
        }

        if (is_string) {
            //decrypt the field
            for (int j = 0; field[j] != '\0'; j++) {
                int ascii_code = (int) field[j];
                field[j] = (char) ascii_code - p.key;
            }
        }
    }
    return p;
}

int retrieve(char *username, char *password){

    // This function retrieves account records from a file and checks if a given username and password match any record.

    Account obj;
    FILE *fs;

    fs = fopen("accountsDB.txt", "r");

    if(attempt != 2) {
        // Loop through the file until the end is reached or a record matching the given username and password is found.
        while(fscanf(fs, "%[^@]@%[^@]@%[^@]@%[^@]@%d\n", obj.idNum, obj.fullname, obj.username, obj.password, &obj.key )== 5){
            obj =  decryption(obj);

            // If the record matches the given username and password, return 1 and pause the program.
            if(strcmp(username, obj.username ) == 0 && strcmp(password, obj.password) == 0){
                strcpy(activeUserId, obj.idNum);
                key = obj.key;
                return 1;
            }

        // If the record matches the given username but not the password, print an error message and pause the program.
            if(strcmp(username, obj.username)==0 && strcmp(password, obj.password) != 0){
                printf("Wrong password! Please try again...\n");
                system("pause");
                system("cls");
                attempt++;
                login();
            }
        }

    }else {
        system("cls");
        printf("Limit for attempt was reached. Try again next time!");
        system("pause");
        exit(0);
    }

    // If no matching record is found, return 0.
    return 0;
}

void retrievePreservedAcc() {
    FILE *fs;
    PAD obj;
    fs = fopen("preserveAccDataDB.txt", "r");

    while(fscanf(fs, "%[^@]@%[^@]@%[^@]@%[^@]@%d\n", obj.idNum, obj.link, obj.username, obj.pw, &obj.key) == 5) {
        obj = decryptionForPAD(obj);
        if(strcmp(obj.idNum, activeUserId) == 0) {
            preserveNewAccData(obj);
        }
    }

}

void preserveNewAccData(PAD obj){

    PAD *p,*q,*n;
    p = q = insideFirstAccount;

    n = (PAD*) ((malloc(sizeof(PAD))));
    strcpy(n->idNum, obj.idNum);
    strcpy(n->link, obj.link);
    strcpy(n->username, obj.username);
    strcpy(n->pw, obj.pw);
    n->key = obj.key;

    while(p != NULL){
        q = p;
        p = p->next;
    }
    if(p == insideFirstAccount)
        insideFirstAccount = n;
    else
        q->next = n;
    n->next = p;
}







