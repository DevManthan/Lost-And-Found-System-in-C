#include<stdio.h>
#include<stdlib.h>

int main(){

    int ch;

    while(1){
        
        printf("\n=====================================\n");
        printf("    DIGITAL LOST & FOUND SYSTEM\n");
        printf("=====================================\n");
        printf("Enter your Choice : \n");
        printf("1. Report Lost item \n");
        printf("2. Check for lost item \n");
        printf("3. Check found Records\n");
        printf("4. Check lost Records\n");
        printf("5. Exit\n");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Reporting\n");
            break;
        case 2:
            printf("checking\n");
            break;
        case 3:
            printf("records\n");
            break;
        case 4:
            printf("records\n");
            break;
        case 5:
            printf("exit\n");
            exit(0);
            break;
        default:
            printf("******INVALID CHOICE*******\n");
            break;
        }
    }
}