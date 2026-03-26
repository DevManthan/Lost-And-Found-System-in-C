#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "headers/foundItem.h"
#include "headers/structure.h"

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

void toLowerCase(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = tolower(src[i]); // Har character ko chhota kar raha hai
        i++;
    }
    dest[i] = '\0'; // String close karna zaroori hai
}

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

    strcpy(newItem.status, "FOUND");

    fp = fopen("found_records.txt", "a");

    // CSV Format: ID,Name,Category,Location,Date,Status,SecurityAnswer
    fprintf(fp, "%d,%s,%s,%s,%s,%s\n",
            newItem.id, newItem.itemName, newItem.category,
            newItem.location, newItem.date, newItem.status);

    fclose(fp);

    printf("\n[SUCCESS] found item reported! Save this Item ID: %d\n", newItem.id);
}

void getFoundRecords()
{
    Item tempItem;
    FILE *fp = fopen("found_records.txt", "r"); // Reading mode mein file kholi

    if (fp == NULL)
    {
        printf(RED "\n[!] No found records found (OR File doesn't exist yet.)" RESET "\n");
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

void searchAndClaim()
{
    char keyword[50], tempSearch[50], tempNameLower[50], tempCatLower[50];
    Item tempItem;
    int found = 0;
    FILE *fp;

    printf("\n--- GLOBAL SEARCH ---\n");
    printf("Enter Item Name or Category to search: ");
    scanf("%s", keyword);

    toLowerCase(tempSearch, keyword);

    printf("\n================================ SEARCH RESULTS ==================================\n");
    printf("%-12s | %-15s | %-12s | %-10s | %-10s\n", "ID", "Item Name", "Category", "Status", "Date");
    printf("----------------------------------------------------------------------------------\n");

    // --- STEP 1: LOST FILE MEIN DHUNDO ---
    fp = fopen("lost_records.txt", "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                      &tempItem.id, tempItem.itemName, tempItem.category,
                      tempItem.location, tempItem.date, tempItem.status) != EOF)
        {

            // File se jo Item Name aur Category mili, uski Lowercase copy banao
            toLowerCase(tempNameLower, tempItem.itemName);
            toLowerCase(tempCatLower, tempItem.category);

            if (strstr(tempNameLower, tempSearch) != NULL || strstr(tempCatLower, tempSearch) != NULL)
            {
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
    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                      &tempItem.id, tempItem.itemName, tempItem.category,
                      tempItem.location, tempItem.date, tempItem.status) != EOF)
        {
            toLowerCase(tempNameLower, tempItem.itemName);
            toLowerCase(tempCatLower, tempItem.category);

            if (strstr(tempNameLower, tempSearch) != NULL || strstr(tempCatLower, tempSearch) != NULL)
            {
                // Status (FOUND) column ke sath print karo
                printf("%-12d | %-15s | %-12s | %-10s | %-10s\n",
                       tempItem.id, tempItem.itemName, tempItem.category, tempItem.status, tempItem.date);
                found = 1;
            }
        }
        fclose(fp);
    }

    if (!found)
    {
        printf("\n             NO MATCHING ITEMS FOUND FOR: %s\n", keyword);
    }
    printf("==================================================================================\n");

    // TODO NEXT: Agar koi item FOUND dikh raha hai, toh user ko ID daal kar "Claim" karne ka option de sakte hain.
}
