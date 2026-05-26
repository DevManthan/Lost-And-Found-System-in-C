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
    char ch;
    int id;
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
    printf("Want to search an item ? [y/n]");
    scanf("%c", &ch);

    if(ch == 'y' || ch == 'Y')
        search();

    fclose(fp);
    printf("Want to Claim? [y/n]");
    scanf("%c", &ch);

    if(ch == 'y' || ch == 'Y')
       printf("Enter Lost Record ID : ");
       scanf("%d", &id);

}

void search()
{
    char keyword[50], tempSearch[50], tempNameLower[50], tempCatLower[50];
    Item tempItem;
    int found = 0;
    FILE *fp;
    int id;
    char ch;

    printf("\n--- GLOBAL SEARCH ---\n");
    printf("Enter Item Name or Category to search: ");
    scanf("%s", keyword);

    toLowerCase(tempSearch, keyword);

    printf("\n================================ SEARCH RESULTS ==================================\n");
    printf("%-12s | %-15s | %-12s | %-10s | %-10s\n", "ID", "Item Name", "Category", "Status", "Date");
    printf("----------------------------------------------------------------------------------\n");

    // ---  FOUND FILE MEIN DHUNDO ---
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
    printf("Want to Claim? [y/n]");
    scanf("%c", &ch);

    if(ch == 'y' || ch == 'Y')
       printf("Enter Lost Record ID : ");
       scanf("%d", &id);

    
}




void claimby_id(int id)
{
Item lostItem,foundItem, bestMatch;
int lostFound=0, matchFound=0;
int bestFound =-1;
int best
FILE *fp;

fp = fopen("lost_records.txt","r");
//id dhoodh rha agr  fie khali hui 
if (fp == NULL) {
    printf("File nahi mili!\n");
    return;
}

while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
              &lostItem.id,
              lostItem.itemName,
              lostItem.category,
              lostItem.location,
              lostItem.date,
              lostItem.status) != EOF) {

    // Sirf ID check kar rha 
    if (lostItem.id == id) {
        lostFound = 1;
        break;  // Mil gayi! Sari info already lostItem mein save hai
    }
}

fclose(fp);
//agrr nahi mili id toh 
if (lostFound==0) {
        printf(RED "\n[!] Invalid ID! no item is there .\n" RESET);
        return;
}
 // ── STEP 3: Lost item details dikhao ──

    printf("\n========== LOST ITEM ==========\n");

    printf("ID       : %d\n", lostItem.id);
    printf("Name     : %s\n", lostItem.itemName);
    printf("Category : %s\n", lostItem.category);
    printf("Location : %s\n", lostItem.location);
    printf("Date     : %s\n", lostItem.date);

    printf("================================\n");

    printf("\n[INFO] Found database mein matching item search ho raha hai...\n");

    // ── STEP 4: Matching ke liye lowercase conversion krdiya ──

    char lNameL[50], lCatL[30], lLocL[50];
    char fNameL[50], fCatL[30], fLocL[50];

    toLowerCase(lNameL, lostItem.itemName);
    toLowerCase(lCatL,  lostItem.category);
    toLowerCase(lLocL,  lostItem.location);

    // ── STEP 5: Found records mein match search karha ──

    fp = fopen("found_records.txt", "r");

    if (fp == NULL) {
        printf(RED "\n[!] Found records file nahi mili.\n" RESET);
        return;
    }

    while (fscanf(fp,
                  "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &foundItem.id,
                  foundItem.itemName,
                  foundItem.category,
                  foundItem.location,
                  foundItem.date,
                  foundItem.status) != EOF) {

        toLowerCase(fNameL, foundItem.itemName);
        toLowerCase(fCatL,  foundItem.category);
        toLowerCase(fLocL,  foundItem.location);

        // Name + Category + Location match karha 

        if (strcmp(lNameL, fNameL) == 0 &&    
            strcmp(lCatL,  fCatL)  == 0 &&
            strcmp(lLocL,  fLocL)  == 0) {

            matchFound = 1;

            bestMatch = foundItem;  // best match variable mai founditem ko store kara diya 

            bestFoundID = foundItem.id; // found item ki id ko best found item mai store kar diya 

            break;
        }
    }

    fclose(fp);

    // ── STEP 6: Match nahi mila ──

    if (matchFound==0) {

        printf(RED "\n[!] Item abhi tak found records mein nahi mila.\n" RESET);

        printf("    Baad mein dobara check karo.\n");

        return;
    }

    // ── STEP 7: Match mil gaya ──

    printf(GREEN "\n========== MATCH FOUND ==========\n" RESET);

    printf("Found Record ID : %d\n", bestMatch.id);
    printf("Name            : %s\n", bestMatch.itemName);
    printf("Category        : %s\n", bestMatch.category);
    printf("Location        : %s\n", bestMatch.location);
    printf("Date            : %s\n", bestMatch.date);

    printf("=================================\n");

    // ── STEP 8: User confirmation karha 

    char confirm;

    printf("\nKya yeh tumhara item hai? (y/n): ");

    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y') {

        printf("\nTheek hai. Record unchanged rahega.\n");


        return;
    }

    // ── STEP 9: Lost records se item delete karha ──

    FILE *lt = fopen("lost_records.txt", "r");
    FILE *ltemp = fopen("lost_temp.txt", "w");

// scan kar rha read kara original file ko store kardiya temporary file
    while (fscanf(lt,
                  "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &temp.id,
                  temp.itemName,
                  temp.category,
                  temp.location,
                  temp.date,
                  temp.status) != EOF) {
// agr temp.id is equal to lost item id toh vo skip ho jayega baki write ho jayega  
        if (temp.id != lostItem.id) {

            fprintf(ltmp,
                    "%d,%s,%s,%s,%s,%s\n",
                    temp.id,
                    temp.itemName,
                    temp.category,
                    temp.location,
                    temp.date,
                    temp.status);
        }
    }

    fclose(lt);
    fclose(ltmp);

    remove("lost_records.txt");

    rename("lost_temp.txt", "lost_records.txt");

    // ── STEP 10: Found records se matched item delete karo ──

    FILE *ft = fopen("found_records.txt", "r");
    FILE *ftmp = fopen("found_temp.txt", "w");

    while (fscanf(ft,
                  "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  &tmp.id,
                  tmp.itemName,
                  tmp.category,
                  tmp.location,
                  tmp.date,
                  tmp.status) != EOF) {

        if (tmp.id != bestFoundID) {

            fprintf(ftmp,
                    "%d,%s,%s,%s,%s,%s\n",
                    tmp.id,
                    tmp.itemName,
                    tmp.category,
                    tmp.location,
                    tmp.date,
                    tmp.status);
        }
    }

    fclose(ft);
    fclose(ftmp);

    remove("found_records.txt");

    rename("found_temp.txt", "found_records.txt");

    // ── STEP 11: Success message ──

    printf(GREEN "\n[SUCCESS] Item successfully claimed!\n" RESET);

    printf("Lost aur Found records is updated.\n");
}