#pragma once
#include "Prototipos.h"
void loadLocal()
{
	setlocale(LC_ALL, "pt-BR");
}

void freekeyboardBuffer() 
{
	fflush(stdin);
}

void getHomePage() 
{
	optionsMenu menu;
	menu.initVals = initVals;
	menu.existVal = existVal;
	menu.initVals(&menu);

	system("CLS");
	loadLocal();
	freekeyboardBuffer();

	drawLine('n',1);

	printf("Seja bem vindo ao banco HELLO WORLD!");
	
	drawLine('n',1);
	drawLine('y',1);
	drawLine('n',2);

	printf("\nPor favor, selecione uma das opções abaixo:\n");
	getOptions();

	int c;

	while ((c = getchar()) != '\n' && c != EOF) 
	{
		int numero = c - '0';

		if (menu.existVal(&menu, numero))
		{
			system("CLS");
			printf("Processando...");
			delay(10000);
		}
		else
		{
			system("CLS");
			printf("opção não encontrada! Voltando...");
			delay(10000);
			getHomePage();
		}
	}

}

void drawLine(char br, int count) 
{
	for (int i = 0; i < count; i++)
	{
		if (br == 'n')
			printf("-------------------------------------");
		else
			printf("\n-------------------------------------");
	}
}

void delay(int milliseconds) {
	volatile unsigned long count = 0;
	for (unsigned long i = 0; i < milliseconds * 100000; i++) {
		count++;
	}
}

void getOptions() 
{
	printf("\n[ 0 ] - Consultar saldo.");
	printf("\n[ 1 ] - Movimentações");
	printf("\n[ 2 ] - Fazer transferência.");
	printf("\n:");
}

void initVals(optionsMenu* menu) 
{
	int default_vals[VAL_SIZE] = { 0, 1, 2, 3, 4, 5 };
	for (int i = 0; i < VAL_SIZE; i++) {
		menu->vals[i] = default_vals[i];
	}
}

bool existVal(optionsMenu* menu, int val) 
{
	for (int i = 0; i < VAL_SIZE; i++) {
		if (menu->vals[i] == val) {
			return true;
		}
	}
	return false;
}