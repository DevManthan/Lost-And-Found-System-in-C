#include <stdio.h>
#include <string.h>
#include <time.h>
#include "headers/structure.h"
#include "headers/lostItem.h"

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

void reportLostItem()
{

    Item newItem;
    FILE *fp;

    printf("\n--- Report a Lost Item ---\n");

    newItem.id = (int)time(NULL);

    // 2. Details Input (Spaces ke liye underscore '_' use karna)
    printf("Enter Item Name (e.g., Black_HP_Laptop): ");
    scanf(" %[^\n]", newItem.itemName);
    
    printf("Enter Category (e.g., Electronics): ");
    scanf(" %[^\n]", newItem.category);
    
    printf("Where did you lose it? (Last seen location): ");
    scanf(" %[^\n]", newItem.location);
    
    printf("Date Lost (DD/MM/YYYY): ");
    scanf(" %[^\n]", newItem.date);

    // Status set kar rahe hain
    strcpy(newItem.status, "LOST");

    // 3. File Handling: lost_records.txt mein append mode ('a') mein save [cite: 54, 161]
    fp = fopen("lost_records.txt", "a");


    // CSV Format: ID,Name,Category,Location,Date,Status
    fprintf(fp, "%d,%s,%s,%s,%s,%s\n",
            newItem.id, newItem.itemName, newItem.category,
            newItem.location, newItem.date, newItem.status);

    fclose(fp);

    printf("\n[SUCCESS] Lost item reported! Save this Item ID: %d\n", newItem.id);
}

void getLostRecords()
{

    Item tempItem;
    FILE *fp = fopen("lost_records.txt", "r"); // Reading mode mein file kholi

    if (fp == NULL)
    {
        printf(RED "\n[!] No lost records found (OR File doesn't exist yet.)" RESET "\n");
        return;
    }

    printf("\n================================ ALL LOST RECORDS ================================\n");
    printf("%-12s | %-15s | %-12s | %-15s | %-10s\n", "ID", "Item Name", "Category", "Location", "Date");
    printf("----------------------------------------------------------------------------------\n");

    // File se data line by line read karna (CSV Format: ID,Name,Cat,Loc,Date,Status,Answer)
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &tempItem.id, tempItem.itemName, tempItem.category,
                  tempItem.location, tempItem.date, tempItem.status) != EOF)
    {
        // Table format mein print karna
        printf("%-12d | %-15s | %-12s | %-15s | %-10s\n",
               tempItem.id, tempItem.itemName, tempItem.category,
               tempItem.location, tempItem.date);
    }

    printf("==================================================================================\n");
    fclose(fp);
}