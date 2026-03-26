#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct {
    int id;
    char itemName[50];
    char category[30];
    char location[50];
    char date[15];
    char status[10];
} Item;

#endif