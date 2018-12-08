#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct reg;
struct node;

typedef struct reg{
	char chave[9];
	int referencia;
	struct reg* proximo;
	struct node *esquerda;
	struct node *direita;
	struct node *pai;
	bool folha;
}reg;

typedef struct node{
	reg* primeiro;
	int ordem;
	struct node *pai;
	bool folha;
}node;

typedef struct btree{
	node* raiz;
}btree;

bool cria(btree *arvore, int ordem);

bool adiciona(char string[9], btree *arvore, int referencia, int ordem);

int exclui();

int procura();

bool mostra(btree *arvore, int ordem);
