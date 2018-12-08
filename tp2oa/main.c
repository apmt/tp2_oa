#include "func.h"

int main() {
	int ordem;
	btree *arvore = malloc(sizeof(btree));
	arvore->raiz = NULL;
	printf("Qual ordem desejas: ");
	scanf("%d", &ordem);
	cria(arvore, ordem);
	/* scanf ordem;
	// Constroi b tree(ordem m);
	// Cria arquivo de saida (indicelista.bt)
	// menu(); -CADA ALTERACAO DEVE ALTERAR O ARQUIVO DE SAIDA /OBS: OPT MOSTRA ARVORE
	// fecha arquivos;*/
	return 0;
}