#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct Account {
    int number;
    char name[50];
    char password[20];
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
    scanf("%49s", login_credentials->name);
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
    new_account->number = generate_account_number();

    printf("Account number: %04d\n", new_account->number);  // print the account number with leading zeros
    printf("Enter full name: ");
    scanf(" %[^\n]", new_account->name);

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


