#include<stdio.h>
#include<stdlib.h>
#include "headers/lostItem.h"
#include "headers/foundItem.h"

int main(){

    int ch;

    while(1){
        // 1. Loop start hote hi poori screen saaf
        system("cls"); 
        
        printf("\n=====================================\n");
        printf("    DIGITAL LOST & FOUND SYSTEM\n");
        printf("=====================================\n");
        printf("Enter your Choice : \n");
        printf("1. Report Lost item \n");
        printf("2. report found item \n");
        printf("3. Search Item Globally \n");
        printf("4. Check found Records\n");
        printf("5. Check lost Records\n");
        printf("6. Exit\n");
        printf("------------------------------------\n");
        printf("Choice : ");
        scanf("%d", &ch);
        printf("------------------------------------\n");

        switch (ch)
        {
        case 1:
            printf("Reporting\n");
            reportLostItem();
            break;
        case 2:
            printf("saving\n");
            reportFoundItem();
            break;
        case 3:
            printf(" searching and matching\n");
            searchAndClaim();
            break;
        case 4:
            printf("records\n");
            getFoundRecords();
            break;
        case 5:
            printf("records\n");
            getLostRecords();
            break;
        case 6:
            printf("exit\n");
            exit(0);
        default:
            printf("******INVALID CHOICE*******\n");
            break;
        }
        
        // 2. Task khatam hone pe screen roko taaki user read kar sake
        printf("\n");
        system("pause"); 
    }
}