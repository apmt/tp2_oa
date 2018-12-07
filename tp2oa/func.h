#include<stdio.h>
#include <stdbool.h>


typedef struct reg{
	char chave[9];
	int referencia;
}reg;

int exclui();

bool adiciona();

int procura();

bool mostra();
