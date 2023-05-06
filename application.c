#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
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
int row;

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
int addAccount();
int loginMenu();
Account decryption(Account p);
PAD decryptionForPAD(PAD p);
void retrievePreservedAcc();
void login();
void preserveNewAccData(PAD obj);
void displayAccounts();
void updateAccount();
void deleteNode();
void displayAndDelete();

//------------------------------------------------
//------------------------------------------------

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


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
                if(addAccount() == 1)break;
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

void login() {
    Account acc;
    char ch;
    int i = 0;
    int higa =196;

      gotoxy(40,4);printf("[< ------ L O G I N  P A G E ------- >]");

    for (int i = 20; i <= 99; i++) {
         gotoxy(i, 26);printf("%c", (char)higa);
         }
     gotoxy(45,9);printf("Enter username: ");
     scanf("%30s", acc.username);
     gotoxy(45,10);printf("Enter password: ");
    //scanf("%19s", acc.password);
    while ((ch = getch()) != '\r') {
        if (i < 19 && isprint(ch)) {
            acc.password[i++] = ch;
            printf("*");
        } else if (i > 0 && ch == '\b') {
            i--;
            printf("\b \b");
        }
    }
    acc.password[i] = '\0';



    int isValid = retrieve(acc.username, acc.password);

    if(isValid == 1){
    gotoxy(48, 25); printf("Successful login!");

        system("pause>0");
        retrievePreservedAcc();
        operationMenu();
    } else {
         gotoxy(43, 25);printf("Failed! Please try again...");
        system("pause>0");
        return;
    }
}

//Function to call after retrieval
int operationMenuUI(){
    system("cls");
    int op;

    gotoxy(35,6);printf("                  |\\__/,|   (`\\");
    gotoxy(35,7);printf("                _.|o o  |_   ) )");
    gotoxy(61,8);printf("(((");
    gotoxy(48,8);printf("(((");

    gotoxy(33,8);printf("---------------");
    gotoxy(51,8);printf("----------");
    gotoxy(64,8);printf("---------------");
    gotoxy(33,9);printf("|      O P E R A T I O N A L   M E N U       |");
    gotoxy(33,10);printf("----------------------------------------------");


    gotoxy(46,12);printf("1. Add new account");
    gotoxy(46,13);printf("2. Update existing account");
    gotoxy(46,14);printf("3. Display accounts");
    gotoxy(46,15);printf("4. Delete existing account");
    gotoxy(46,16);printf("5. Exit and Save");
    gotoxy(46,18);printf("Enter your choice(1-5): ");
    scanf("%d", &op);

    return op;
}

void operationMenu(){
    PAD obj;
    while(1){
            switch(operationMenuUI()) {
                case 1:
                    system("cls");
                    gotoxy(42,5);printf("[<------- W E L C O M E ------->]");
                    strcpy(obj.idNum, activeUserId);
                    gotoxy(44,8);printf("Link: ");scanf("%s", obj.link);
                    gotoxy(44,9);printf("Username: ");scanf("%s", obj.username);
                    gotoxy(44,10);printf("password: ");scanf("%s", obj.pw);
                    obj.key = key;
                    gotoxy(44,12);system("pause");
                    preserveNewAccData(obj);
                    break;

                case 2:
                    system("cls");
                    updateAccount();
                    break;
                case 3:
                    system("cls");
                    displayAccounts();
                    break;
                case 4:
                    system("cls");
                    displayAndDelete();
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

void displayAccounts() {    //Display the current user's accounts
    PAD *p = insideFirstAccount;
    int num = 0;
    row = 7;

    gotoxy(45, 2); printf("===== YOUR ACCOUNTS =====");
    gotoxy(7, 5); printf("#");
    gotoxy(35, 5); printf("LINK");
    gotoxy(65, 5); printf("USERNAME");
    gotoxy(100, 5); printf("PASSWORD");

    while (p != NULL) {
        if (strcmp(p->idNum, activeUserId) == 0) {
            num++;
            gotoxy(7, row); printf("%d", num);
            gotoxy(10, row); printf("|");
            gotoxy(30, row); printf("%s", p->link);
            gotoxy(63, row); printf("%s", p->username);
            gotoxy(98, row); printf("%s", p->pw);
            row++;
        }
        p = p->next;
    }
    getch();
}

void deleteNode() {
    int position;
    row = 14;
    gotoxy(32, 28);printf("Enter the row number of the account you want to delete: ");
    scanf("%d", &position);

    if (position == 1) {
        PAD *temp = insideFirstAccount;
        insideFirstAccount = insideFirstAccount->next;
        free(temp);
        system("cls");
        gotoxy(30, 8);printf("Account deleted successfully");
        gotoxy(30, 10);system("pause");
        return;
    }

    PAD *prev = insideFirstAccount;
    for (int i = 1; i < position - 1; i++) {
        if(prev->next == NULL){
            system("cls");
            gotoxy(30, 8);printf("Invalid request! Row %d is not in the list.", position);
            gotoxy(30, 10);system("pause");
            return;
        }
        prev = prev->next;
    }

    if (prev->next == NULL) {
        system("cls");
        gotoxy(30, 8);printf("Invalid request! Row %d is not in the list.", position);
        gotoxy(30, 10);system("pause");
        return;
    };

    PAD *temp = prev->next;
    prev->next = temp->next;
    free(temp);
    system("cls");
    gotoxy(50, 11);printf("Account deleted successfully");
    gotoxy(35, 10);system("pause");
    return;
}

void displayAndDelete() {
    if (insideFirstAccount == NULL) {
        system("cls");
        gotoxy(30, 8);printf("The list is empty!");
        gotoxy(30, 10);system("pause");
        return;
    }

    PAD *p = insideFirstAccount;
    int num = 0;
    row = 7;

    gotoxy(45, 2); printf("===== YOUR ACCOUNTS =====");
    gotoxy(7, 5); printf("#");
    gotoxy(35, 5); printf("LINK");
    gotoxy(65, 5); printf("USERNAME");
    gotoxy(100, 5); printf("PASSWORD");

    while (p != NULL) {
        if (strcmp(p->idNum, activeUserId) == 0) {
            num++;
            gotoxy(7, row); printf("%d", num);
            gotoxy(10, row); printf("|");
            gotoxy(30, row); printf("%s", p->link);
            gotoxy(63, row); printf("%s", p->username);
            gotoxy(98, row); printf("%s", p->pw);
            row++;
        }
        p = p->next;
    }
    printf("\n");
    deleteNode();
}

void updateAccount() {
    PAD *p = insideFirstAccount;
    char link[256];
    char newUsername[256];
    char newPassword[256];
    int choice, found = 0, num = 0, row = 7, row_matchingAcc = 8;
    // find all accounts with the same link
    PAD *matchingAccounts[256];
    int numMatchingAccounts = 0;

    gotoxy(45, 2); printf("===== UPDATE AN ACCOUNT =====");
    gotoxy(7, 5); printf("#");
    gotoxy(35, 5); printf("LINK");
    gotoxy(65, 5); printf("USERNAME");
    gotoxy(100, 5); printf("PASSWORD");

    while (p != NULL) {
        num++;
        gotoxy(7, row); printf("%d", num);
        gotoxy(10, row); printf("|");
        gotoxy(30, row); printf("%s", p->link);
        gotoxy(63, row); printf("%s", p->username);
        gotoxy(98, row); printf("%s", p->pw);
        row++;
        p = p->next;
    }

    p = insideFirstAccount; // reset p to the beginning of the list

    gotoxy(25, 27); printf("Enter the link of the account you want to update: ");
    scanf("%s", link);

    while (p != NULL) {
        if (strcmp(p->idNum, activeUserId) == 0 && strcmp(p->link, link) == 0) {
            matchingAccounts[numMatchingAccounts++] = p;
        }
        p = p->next;
    }

    if (numMatchingAccounts == 0) {
        gotoxy(52, 16); printf("Link not found.\n");
        gotoxy(45, 17); system("pause");
        return;
    }

    if (numMatchingAccounts == 1) {
        p = matchingAccounts[0];
    } else {
        // prompt the user to choose which account to update
        system("cls");
        gotoxy(38, 6); printf("Multiple accounts found with the same link.");
        for (int i = 0; i < numMatchingAccounts; i++) {
            gotoxy(50, row_matchingAcc + i + 1); printf("%d. %s\n", i + 1, matchingAccounts[i]->username);
        }
        gotoxy(30, row_matchingAcc + numMatchingAccounts + 2); printf("Enter the username of the account you want to update: ");
        scanf("%s", newUsername);

        // find the account with the entered username
        for (int i = 0; i < numMatchingAccounts; i++) {
            if (strcmp(matchingAccounts[i]->username, newUsername) == 0) {
                p = matchingAccounts[i];
                found = 1;
                break;
            }
        }

        if (!found) {
            gotoxy(52, 16); printf("Account not found.\n");
            gotoxy(45, 17); system("pause");
            return;
        }
    }

    system("cls");
    gotoxy(5, 3); printf("Updating account:\n");
    gotoxy(10, 5); printf("Link: %s\n", p->link);
    gotoxy(10, 6); printf("Username: %s\n", p->username);
    gotoxy(10, 7); printf("Password: %s\n", p->pw);

    gotoxy(45, 9); printf("What do you want to update?");
    gotoxy(50, 11); printf("1. Username");
    gotoxy(50, 12); printf("2. Password");
    gotoxy(45, 14); printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            gotoxy(42, 18); printf("Enter new username: ");
            scanf("%s", newUsername);
            strcpy(p->username, newUsername);
            break;
        case 2:
            gotoxy(43, 18); printf("Enter new password: ");
            scanf("%s", newPassword);
            strcpy(p->pw, newPassword);
            break;
        default:
            gotoxy(52, 18); printf("Invalid choice.\n");
            return;
    }

    gotoxy(45, 25); printf("Account updated successfully.\n");
    gotoxy(46, 26); system("pause");
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

int addAccount() {
    Account *new_account = (Account *) malloc(sizeof(Account)); //create struct and populate its fields
    char confirm_password[20];
    char ch;
    int i = 0;
    sprintf(new_account->idNum, "%d", genIdNum());

     gotoxy(35,5);printf("[< ----- C R E A T E  A C C O U N T ----- >]");

    gotoxy(44,8);printf("Enter fullname: ");
    scanf(" %[^\n]", new_account->fullname);

    gotoxy(44,9);printf("Enter username: ");
    scanf("%s", new_account->username);

    gotoxy(44,10);printf("Enter password: ");
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
    int higa =196;
    for (int i = 20; i <= 99; i++) {
         gotoxy(i, 26);printf("%c", (char)higa);
    }

    gotoxy(44,12);printf("Confirm password: ");
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
        gotoxy(37,25);printf("Passwords do not match. Account not created.");
        gotoxy(38,27);system("pause");
        free(new_account);
        return 1;
    }

    new_account->key = rand() % 56 + 1;

    new_account->next = first_account; // next pointer of the new account to the current first account

    first_account = new_account; // first account pointer to the new account

    gotoxy(44,25);printf("Account added successfully!");
    gotoxy(44,27);system("pause");
}

int loginMenu() {
    system("cls");
    int op;

    gotoxy(43,5); printf(" __  __  ____  _  _  __  __ /\\ ");
    gotoxy(43,6); printf("(  \\/  )( ___)( \\( )(  )(  ))( ");
    gotoxy(43,7); printf(" )    (  )__)  )  (  )(__)( \\/ ");
    gotoxy(43,8); printf("(_/\\/\\_)(____)(_)\\_)(______)() ");
    gotoxy(46,10);printf("1. Log in\n");
    gotoxy(46,11);printf("2. Create vault \n");
    gotoxy(46,12);printf("3. Exit\n\n");
    gotoxy(46,14);printf("Enter your choice(1-3): ");
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

    } else {
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
    int higa = 196;

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
                gotoxy(48, 25);printf("Wrong password!");
                system("pause>0");
                system("cls");
                attempt++;
                login();
            }
        }

    }else {
        //system("cls");
         gotoxy(33, 25);printf("Limit for attempt was reached. Try again next time!");
        system("pause>0");
        system("cls");
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
