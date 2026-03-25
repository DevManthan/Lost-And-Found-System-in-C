#include <stdio.h>
#include <string.h>
#include <time.h>
#include "headers/foundItem.h"
#include "headers/structure.h"

void reportFoundItem()
{

    Item newItem;
    FILE *fp;

    printf("\n--- Report a Found Item ---\n");

    newItem.id = (int)time(NULL); // auto id generate

    printf("Enter Item Name (e.g., Black_HP_Laptop): ");
    scanf(" %[^\n]", newItem.itemName);

    printf("Enter Category (e.g., Electronics): ");
    scanf(" %[^\n]", newItem.category);

    printf("Where did you lose it? (Last seen location): ");
    scanf(" %[^\n]", newItem.location);

    printf("Date Lost (DD/MM/YYYY): ");
    scanf(" %[^\n]", newItem.date);

    // Security Question for Verification later [cite: 60, 170]
    strcpy(newItem.claimAnswer, "NA");

    // Status set kar rahe hain
    strcpy(newItem.status, "FOUND");

    // 3. File Handling: found_records.txt mein save hoga
    fp = fopen("found_records.txt", "a");

    if (fp == NULL)
    {
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

void getFoundRecords()
{
    Item tempItem;
    FILE *fp = fopen("found_records.txt", "r"); // Reading mode mein file kholi

    if (fp == NULL)
    {
        printf("\n[!] No lost records found (File doesn't exist yet).\n");
        return;
    }

    printf("\n================================ ALL LOST RECORDS ================================\n");
    printf("%-12s | %-15s | %-12s | %-15s | %-10s\n", "ID", "Item Name", "Category", "Location", "Date");
    printf("----------------------------------------------------------------------------------\n");

    // File se data line by line read karna (CSV Format: ID,Name,Cat,Loc,Date,Status,Answer)
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &tempItem.id, tempItem.itemName, tempItem.category,
                  tempItem.location, tempItem.date, tempItem.status, tempItem.claimAnswer) != EOF)
    {
        // Table format mein print karna
        printf("%-12d | %-15s | %-12s | %-15s | %-10s\n",
               tempItem.id, tempItem.itemName, tempItem.category,
               tempItem.location, tempItem.date);
    }

    printf("==================================================================================\n");
    fclose(fp);
}

void searchAndClaim()
{
    char keyword[50];
    Item tempItem;
    int found = 0;
    FILE *fp;

    printf("\n--- GLOBAL SEARCH ---\n");
    printf("Enter Item Name or Category to search: ");
    scanf("%s", keyword);

    printf("\n================================ SEARCH RESULTS ==================================\n");
    printf("%-12s | %-15s | %-12s | %-10s | %-10s\n", "ID", "Item Name", "Category", "Status", "Date");
    printf("----------------------------------------------------------------------------------\n");

    // --- STEP 1: LOST FILE MEIN DHUNDO ---
    fp = fopen("lost_records.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", 
               &tempItem.id, tempItem.itemName, tempItem.category, 
               tempItem.location, tempItem.date, tempItem.status, tempItem.claimAnswer) != EOF) {
            
            if (strstr(tempItem.itemName, keyword) != NULL || strstr(tempItem.category, keyword) != NULL) {
                // Status (LOST) column ke sath print karo
                printf("%-12d | %-15s | %-12s | %-10s | %-10s\n", 
                       tempItem.id, tempItem.itemName, tempItem.category, tempItem.status, tempItem.date);
                found = 1;
            }
        }
        fclose(fp);
    }

    // --- STEP 2: FOUND FILE MEIN DHUNDO ---
    fp = fopen("found_records.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", 
               &tempItem.id, tempItem.itemName, tempItem.category, 
               tempItem.location, tempItem.date, tempItem.status, tempItem.claimAnswer) != EOF) {
            
            if (strstr(tempItem.itemName, keyword) != NULL || strstr(tempItem.category, keyword) != NULL) {
                // Status (FOUND) column ke sath print karo
                printf("%-12d | %-15s | %-12s | %-10s | %-10s\n", 
                       tempItem.id, tempItem.itemName, tempItem.category, tempItem.status, tempItem.date);
                found = 1;
            }
        }
        fclose(fp);
    }

    if (!found) {
        printf("\n             NO MATCHING ITEMS FOUND FOR: %s\n", keyword);
    }
    printf("==================================================================================\n");

    // TODO NEXT: Agar koi item FOUND dikh raha hai, toh user ko ID daal kar "Claim" karne ka option de sakte hain.
}