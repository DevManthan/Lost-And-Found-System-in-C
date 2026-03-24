#include<stdio.h>
#include <string.h>
#include <time.h>
#include "headers/foundItem.h"
#include "headers/structure.h"

void reportFoundItem(){

    Item newItem;
    FILE *fp;

    printf("\n--- Report a Found Item ---\n");

    newItem.id = (int)time(NULL); // auto id generate 

    // 2. Details Input (Spaces ke liye underscore '_' use karna)
    printf("Enter Item Name (e.g., Black_HP_Laptop): ");
    scanf(" %[^\n]", newItem.itemName);
    
    printf("Enter Category (e.g., Electronics): ");
    scanf(" %[^\n]", newItem.category);
    
    printf("Where did you lose it? (Last seen location): ");
    scanf(" %[^\n]", newItem.location);
    
    printf("Date Lost (DD/MM/YYYY): ");
    scanf(" %[^\n]", newItem.date);
    
    // Security Question for Verification later [cite: 60, 170]
    strcpy(newItem.claimAnswer,"NA");

    // Status set kar rahe hain
    strcpy(newItem.status, "FOUND");

    // 3. File Handling: found_records.txt mein save hoga
    fp = fopen("found_records.txt", "a");
    
    if (fp == NULL) {
        printf("Error: found database file nahi khul rahi!\n");
        return;
    }

    // CSV Format: ID,Name,Category,Location,Date,Status,SecurityAnswer 
    fprintf(fp, "%d,%s,%s,%s,%s,%s,%s\n", 
            newItem.id, newItem.itemName, newItem.category, 
            newItem.location, newItem.date, newItem.status, newItem.claimAnswer);

    fclose(fp);

    printf("\n[SUCCESS] found item reported! Save this Item ID: %d\n", newItem.id);
}

void getFoundRecords(){
    printf("Shwoing all found item records , soon");
}
void searchAndClaim(){
    printf("karta hu thodi der mai hi karunga \n");
}