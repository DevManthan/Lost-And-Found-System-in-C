#include <stdio.h>
#include <stdlib.h>
#include "headers/lostItem.h"
#include "headers/foundItem.h"

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

int main()
{

    int ch;

    while (1)
    {
        system("cls");

        printf("\n=====================================\n");
        printf("    DIGITAL LOST & FOUND SYSTEM\n");
        printf("=====================================\n");
        printf("Enter your Choice : \n");
        printf("1. Report Lost item \n");
        printf("2. report found item \n");
        printf("3. Search Item Globally \n");
        printf("4. View Lost items\n");
        printf("5. View Found items\n");
        printf("6. Exit\n");
        printf("------------------------------------\n");
        printf("Choice : ");
        // Agar number ki jagah alphabet daala
        if (scanf("%d", &ch) != 1)
        {
            while (getchar() != '\n')
                ;    // Kachra saaf karo
            ch = -1; // Invalid value de do taaki seedha 'default' case mein chala jaye
        }
        printf("------------------------------------\n");

        switch (ch)
        {
        case 1:
            reportLostItem();
            break;
        case 2:
            reportFoundItem();
            break;
        case 3:
            searchAndClaim();
            break;
        case 4:
            getLostRecords();
            break;
        case 5:
            getFoundRecords();
            break;
        case 6:
            printf(RED "----------EXIT----------" RESET "\n");
            exit(0);
        default:
            printf(RED "**********INVALID CHOICE**********" RESET "\n");
            break;
        }

        printf("\n");
        system("pause");
    }
}