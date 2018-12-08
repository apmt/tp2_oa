#include "func.h"


bool no_cheio(node *no, int ordem) {
	reg *aux = no->primeiro;
	int contador = 0;
	while(aux!=NULL){
		aux= aux->proximo;
		contador++;
	}
	if(contador >= ordem-1)
		return true;
	else
		return false;
}

void adiciona_ordenado(node *p_no, reg *p_reg){
	reg *p_reg_aux, *p_reg_anterior, *aux_r;
	p_reg_aux = p_no->primeiro;
	if(p_reg_aux==NULL){
		p_no->primeiro = p_reg;
	}
	else if(strcmp(p_reg->chave, p_reg_aux->chave)<0) {
		p_reg_aux = p_no->primeiro;
		p_no->primeiro = p_reg;
		p_reg->proximo = p_reg_aux;
	}
	else {
		while(strcmp(p_reg->chave, p_reg_aux->chave)>0 && p_reg_aux->proximo != NULL) {
			p_reg_anterior = p_reg_aux;								
			p_reg_aux = p_reg_aux->proximo;
		}
		if(p_reg_aux->proximo == NULL && strcmp(p_reg->chave, p_reg_aux->chave)>0) {
			p_reg_aux->proximo = p_reg;
			p_reg->proximo = NULL;
		}
		else {
			aux_r = p_reg_aux;
			p_reg_anterior->proximo = p_reg;
			p_reg->proximo = aux_r;
		}
	}
}

void eleva(btree *arvore, reg *p_reg, node *p_no, int ordem) {
	node *no_new = malloc(sizeof(node));
	no_new->primeiro = p_reg->proximo;
	no_new->folha = p_no->folha;
	no_new->pai = p_no->pai;
	p_reg->direita = no_new;
	p_reg->proximo = NULL;
	p_reg->esquerda = p_no;
	p_reg->folha = false;
	if(p_no->pai == NULL){
		node *no = malloc(sizeof(node));
		no->primeiro = p_reg;
		no->pai=NULL;
		no->folha = false;
		arvore->raiz = no;
		p_no->pai = no;
		no_new->pai = p_no->pai;
	}
	else if(!no_cheio(p_no->pai, ordem)){
		reg *p_reg_aux, *p_reg_anterior, *aux_r;
		p_reg_aux = p_no->pai->primeiro;
		if(strcmp(p_reg->chave, p_reg_aux->chave)<0) {
			p_no->pai->primeiro = p_reg;
			p_reg->proximo = p_reg_aux;
		}
		else {
			while(strcmp(p_reg->chave, p_reg_aux->chave)>0 && p_reg_aux->proximo != NULL) {
				p_reg_anterior = p_reg_aux;								
				p_reg_aux = p_reg_aux->proximo;
			}
			if(p_reg_aux->proximo == NULL && strcmp(p_reg->chave, p_reg_aux->chave)>0) {
				p_reg_aux->proximo = p_reg;
			}
			else {
				aux_r = p_reg_aux;
				p_reg_anterior->proximo = p_reg;
				p_reg->proximo = aux_r;
			}
		}

	}
	else {
		reg *p_reg_aux, *p_reg_anterior, *aux_r;
		int i;
		i = (ordem-1)/2;
		p_reg_aux = p_no->pai->primeiro;
		while(i--) {
			p_reg_anterior = p_reg_aux;
			p_reg_aux = p_reg_aux->proximo;
		}
		eleva(arvore, p_reg_aux, p_no->pai, ordem);
		if(strcmp(p_reg->chave, p_reg_aux->chave)<0){
			p_reg_anterior -> proximo = NULL;
			adiciona_ordenado(p_reg_aux->esquerda, p_reg);
		}
		else {
			p_reg_anterior -> proximo = NULL;
			adiciona_ordenado(p_reg_aux->direita, p_reg);
		}
		if(p_reg_aux->proximo!=NULL)
			p_reg_aux->proximo->esquerda = p_reg_aux->direita;
	}
}

bool adiciona(char string[9], btree *arvore, int referencia, int ordem){
	node *p_no_aux, *p_no = arvore->raiz;
	int i;
	reg *p_reg, *p_reg_aux, *p_reg_anterior;
	reg *reg_add = malloc(sizeof(reg));
	reg_add->proximo = NULL;
	reg_add->esquerda = NULL;
	reg_add->direita = NULL;
	reg_add->referencia = referencia;
	reg_add->folha = true;
	reg_add->pai = NULL;
	strcpy(reg_add->chave, string);

	if(arvore->raiz == NULL) {
		node *no = malloc(sizeof(node));
		no->primeiro = reg_add;
		no->pai=NULL;
		no->folha = true;
		arvore->raiz = no;
	}
	else {
		p_no_aux = p_no;
		while(p_no_aux->folha == false) {
			p_reg = p_no_aux->primeiro;
			while(p_reg->proximo!=NULL && strcmp(reg_add->chave, p_reg->chave)>0) {
				p_reg = p_reg->proximo;
			}
			if(p_reg->proximo==NULL) {
				if(strcmp(reg_add->chave, p_reg->chave)>0)
					p_no_aux = p_reg->direita;
				else
					p_no_aux = p_reg->esquerda;
			}
			else {
				p_no_aux = p_reg->esquerda;
			}
		}
		p_no = p_no_aux;
		if(no_cheio(p_no, ordem)) {
			i = (ordem-1)/2;
			p_reg = p_no->primeiro;
			while(i--) {
				p_reg_anterior = p_reg;
				p_reg = p_reg->proximo;
			}
			eleva(arvore, p_reg, p_no, ordem);
			if(strcmp(p_reg->chave, reg_add->chave)>0){
				p_reg_anterior->proximo = NULL;
				adiciona_ordenado(p_reg->esquerda, reg_add);
			}
			else {
				p_reg_anterior->proximo = NULL;
				adiciona_ordenado(p_reg->direita, reg_add);
			}
			if(p_reg->proximo!=NULL)
				p_reg->proximo->esquerda = p_reg->direita;

		}
		else {
			p_reg = p_no->primeiro;
			if(p_no->primeiro==NULL) {
				p_no->primeiro = reg_add;
			}
			else {

				while(strcmp(reg_add->chave, p_reg->chave)>0 && p_reg->proximo!=NULL) {
					p_reg_anterior = p_reg;
					p_reg = p_reg->proximo;
				}
				if(p_reg->proximo==NULL && strcmp(reg_add->chave, p_reg->chave)>0) {
					p_reg->proximo = reg_add;

				}
				else {
					if(p_reg==p_no->primeiro) {
						p_reg_aux = p_reg;
						p_no->primeiro = reg_add;
						p_no->primeiro->proximo = p_reg_aux; 
					}
					else {
						p_reg_aux = p_reg;
						p_reg_anterior->proximo = reg_add;
						p_reg_anterior->proximo->proximo = p_reg_aux; 
					}

				}
			}
		}
	}
	mostra(arvore, ordem);
	return true;
}

bool cria(btree *arvore, int ordem){
	FILE* arq=fopen("lista.txt", "r");
	char registo[150];
	char string[9];
	int i;
	int linha = 1;
	string[8]='\0';
	while(1) {
		if(fscanf(arq, "%[^\n]", registo)==EOF)
			break;
		/* 3 primeiros char do nome uppercase */
		for(i=0; i<3; i++) {
			string[i]=toupper(registo[i]);
		}
		for(i=41; i<46; i++) {
			string[i-38]=toupper(registo[i]);
		}
		fgetc(arq);
		adiciona(string, arvore, linha, ordem);
		linha++;
	}
	fclose(arq);
	return true;
}

int exclui();

int procura();

void imprime(node *p_no, int nivel) {	
	int i = nivel;
	if(p_no != NULL && p_no->primeiro != NULL) {
		reg *p_reg = p_no->primeiro;
		imprime(p_reg->esquerda, nivel+1);
		while(i--){
			printf("    ");
		}
		printf("%s\n", p_reg->chave);
		/*imprime(p_reg->esquerda, nivel+1); POS_ORDEM*/
		imprime(p_reg->direita, nivel+1);
		while(p_reg->proximo!=NULL) {
			i = nivel;
			while(i--){
				printf("    ");
			}
			printf("%s\n", p_reg->proximo->chave);
			imprime(p_reg->proximo->direita, nivel+1);
			p_reg = p_reg->proximo;

		}
	}
}

bool mostra(btree *arvore, int ordem) {
	imprime(arvore->raiz, 0);
	printf("\n");
	return true;
}

void menu();