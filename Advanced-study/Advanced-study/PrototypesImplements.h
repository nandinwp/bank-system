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

void getHomePage() {
	optionsMenu menu;
	IniFile* ini = FileManager::load_ini("config.ini");

	if (!ini) {
		ini = (IniFile*)malloc(sizeof(IniFile));
		ini->sections = NULL;
		ini->section_count = 0;

		FileManager::initialize_default_values(ini);
	}

	string datetime = getCurrentTime();
	printf(datetime.c_str());


	menu.initVals = initVals;
	menu.existVal = existVal;
	
	menu.initVals(&menu);

	system("CLS");
	
	loadLocal();
	
	freekeyboardBuffer();

	drawLine('n', 1);
	printf("Seja bem-vindo ao banco HELLO WORLD!");
	drawLine('n', 1);
	drawLine('y', 1);
	drawLine('n', 2);

	printf("\nPor favor, selecione uma das opções abaixo:\n");
	getOptions();

	int numero;
	if (scanf_s("%d", &numero) != 1) {
		printf("Erro de entrada, por favor insira um número.\n");
		FileManager::free_ini(ini);
		getHomePage();
		return;
	}

	if (menu.existVal(&menu, numero)) {
		system("CLS");
		printf("Processando...");
		delay(10000);
		if (processarOperacao(numero, &menu) == EXIT_FAILURE) 
		{
			printf("Operação não disponível");
			delay(10000);
			getHomePage();
			return;
		}
		else
		{
			printf("\nOperação finalizada com sucesso!");
			delay(10000);
			getHomePage();
			return;
		}
	}
	else
	{
		system("CLS");
		printf("Opção não encontrada! Voltando...");
		delay(10000);
		
		FileManager::free_ini(ini);

		getHomePage();
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
	printf("\n[ 3 ] - Limite de crédito.");
	printf("\nDigite a operação:");
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

std::string getCurrentTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	char buffer[30];
	snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d %02d:%02d:%02d.%03d",
		st.wDay,         // Dia
		st.wMonth,       // Mês
		st.wYear,        // Ano
		st.wHour,        // Hora
		st.wMinute,      // Minuto
		st.wSecond,      // Segundo
		st.wMilliseconds // Milissegundos
	);

	return std::string(buffer);
}

int processarOperacao(int operacao, optionsMenu* menu)
{
	if (menu->existVal(menu, operacao)) 
	{
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}