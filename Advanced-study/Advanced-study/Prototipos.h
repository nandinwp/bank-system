#pragma once
#include "Imports.h"

#define VAL_SIZE  6

void loadLocal();
void freekeyboardBuffer();
void getHomePage();
void drawLine(char br, int count);
void delay(int milliseconds);
void getOptions();

typedef struct optionsMenu
{
    int vals[VAL_SIZE];

    void (*initVals)(struct optionsMenu*);  
    bool (*existVal)(struct optionsMenu*, int);  
} optionsMenu;
void initVals(optionsMenu* menu);
bool existVal(optionsMenu* menu, int val);