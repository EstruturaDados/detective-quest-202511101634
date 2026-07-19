#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char valor[50];
    struct No* esquerda;
    struct No* direita;
} No;

No* novoNo(char* valor) {
    No* novo = (No*) malloc(sizeof(No));
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

No* criar(No* raiz, char* valor) { //cria um novo cômodo na mansão inserindo os valores posicionando-os de acordo com a ordem alfabética no lado correto das subárvores
    if (raiz == NULL) return novoNo(valor);
    if (strcmp(valor, raiz->valor) < 0) { //se valor informado for menor que o valor do nó atual, então ele vai para a subárvore da esquerda
        raiz->esquerda = criar(raiz->esquerda, valor);
    } else { //se valor informado for maior ou igual que o valor do nó atual, então ele vai para a subárvore da direita
        raiz->direita = criar(raiz->direita, valor);
    }
    return raiz;
}

No* esquerda(No* atual) {
    if (atual->esquerda != NULL) return atual->esquerda;
    printf("\nNao existe um comodo a esquerda!");
    return atual;
}

No* direita(No* atual) {
    if (atual->direita != NULL) return atual->direita;
    printf("\nNao existe um comodo a direita!");
    return atual;
}

int main() {

    No* raiz = NULL;
    No* atual = NULL;
    raiz = criar(raiz, "Hall de Entrada");
    raiz = criar(raiz, "Sala de Estar");
    raiz = criar(raiz, "Biblioteca");
    raiz = criar(raiz, "Copa");
    raiz = criar(raiz, "Cozinha");
    raiz = criar(raiz, "Quarto");
    atual = raiz;
 
    int opcao;
    do {
        printf("\n\n---------------------");
        printf("\n|  DETECTIVE QUEST  |");
        printf("\n---------------------");
        printf("\n\n-> Voce esta em: %s", atual->valor);
        printf("\n\n1. Navegar para a esquerda");
        printf("\n2. Navegar para a direita");
        printf("\n3. Sair");
        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atual = esquerda(atual);
                break;
            case 2:
                atual = direita(atual);
                break;
        }

    } while (opcao < 3);

    return 0;
}