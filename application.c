#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

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
void login()
{
    Account *login_credentials = (Account *) malloc(sizeof(Account));

    printf("\n==================\n");
    printf("Enter username: \n");
    scanf("%49s", login_credentials->fullname);
    printf("Enter password: \n");
    scanf("%49s", login_credentials->password);

    //FUNCTION!
    printf("Function for username and password validation goes here.!!");
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

void decryption(Account *p) {
    for (int i = 0; i < 4; i++) {
        char *field = NULL;
        int is_string = 0;

        // Determine which field to decrypt
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
            //decrypt the field
            for (int j = 0; field[j] != '\0'; j++) {
                int ascii_code = (int) field[j];
                field[j] = (char) ascii_code - p->key;
            }
        }
    }
}


int main() {
    // WRITE CODE HERE
    // connected to you billona sarap mo
    // connected ~jerry

    while(1) {
        switch(main_menu()) {
            case 1:
                system("cls");
                login();
                break;
            case 2:
                system("cls");
                //printf("Create Vault Account function goes here.\n");
                add_account();
                encryption();
                //save()
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


