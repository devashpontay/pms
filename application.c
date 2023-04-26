#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

typedef struct Account {
    char idNum[10];
    char fullname[31];
    char username[31];
    char password[20];
    int key;
    struct Account *next;
} Account;

Account *first_account = NULL; // Initialize a pointer to the first account in the linked list

int generate_account_number() {
    return (rand() % 9999) + 1;  // generate a random number between 1 and 9999
}
int retrieve(char *username, char *password);
void login()
{
    Account acc;

    printf("\n==================\n");
    printf("Enter username: \n");
    scanf("%49s", acc.username);
    printf("Enter password: \n");
    scanf("%49s", acc.password);

    int isValid = retrieve(acc.username, acc.password);

    if(isValid == 1){
        printf("Successful!\n");
        system("pause");
        operation_menu();
    }
    else{
        printf("Failed!");
        system("pause");
        return;
    }

}

//Function to call after retrieval
int operation_menu(){
    system("cls");
    int op;

    printf("\n===== OPERATION MENU =====\n");
    printf("1. Display accounts\n");
    printf("2. Add new account\n");
    printf("3. Update existing account\n");
    printf("4. Delete existing account\n");
    printf("5. Exit\n\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    return op;
}

void save_sampleRecords(){
    // This function saves all the account records to a file named "accountsDB.txt".
    // It appends new records to the end of the file if it already exists.

    FILE *fs;
    fs = fopen("accountsDB.txt", "a"); // open the file in "append" mode to add new records to the end of the file

    Account *p;
    p = first_account;

    fprintf(fs, "%s@%s@%s@%s@%d\n", p->idNum, p->fullname, p->username, p->password, p->key);

    fclose(fs);
    //printf("Successfully saved all accounts to file.\n");
}


void add_account() {
    Account *new_account = (Account *) malloc(sizeof(Account)); //create struct and populate its fields
    char confirm_password[20];
    char ch;
    int i = 0;
    srand(time(NULL));
    sprintf(new_account->idNum, "%d", generate_account_number());

    printf("Account number: %s\n", new_account->idNum);  // print the account number with leading zeros
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

int main_menu() {
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


void encryption() {
    Account *p;
    p = first_account;
    srand(time(NULL));


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

int retrieve(char *username, char *password){

    // This function retrieves account records from a file and checks if a given username and password match any record.

    Account obj;
    FILE *fs;

    fs = fopen("accountsDB.txt", "r");
     // Loop through the file until the end is reached or a record matching the given username and password is found.
    while(fscanf(fs, "%[^@]@%[^@]@%[^@]@%[^@]@%d\n", obj.idNum, obj.fullname, obj.username, obj.password, &obj.key)==5){
      obj =  decryption(obj);

        // If the record matches the given username and password, return 1 and pause the program.
        if(strcmp(username, obj.username )== 0 && strcmp(password, obj.password)==0){
            return 1;
            system("pause");
        }

        // If the record matches the given username but not the password, print an error message and pause the program.
        if(strcmp(username, obj.username)==0 && strcmp(password, obj.password) != 0){
            printf("Wrong password! Please try again...\n");
            system("pause");
            login();
        }
    }
    // If no matching record is found, return 0.
    return 0;
}

int main() {
    // WRITE CODE HERE
    // connected to you billona sarap mo
    // connected ~jerry


    while(1) {

        switch(main_menu()) {
            case 1:
                system("cls");
                //retrive();
                login();
                break;
            case 2:
                system("cls");
                //printf("Create Vault Account function goes here.\n");
                add_account();
                encryption();
                save_sampleRecords();
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




