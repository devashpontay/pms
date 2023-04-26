#include <stdio.h>
#include <stdlib.h>

int main_menu() {
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
                printf("Log in function goes here.\nJerryBoy");
                break;
            case 2:
                system("cls");
                printf("Create Vault Account function goes here.\n");
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
