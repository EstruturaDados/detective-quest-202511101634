#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char valor[50];
    char pista[100];
    struct No* esquerda;
    struct No* direita;
} No;

typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

#define TAMANHO_HASH 10

typedef struct {
    char pista[100];
    char suspeito[50];
} Hash;

Hash tabelaHash[TAMANHO_HASH];

No* novoNo(char* valor, char* pista) {
    No* novo = (No*) malloc(sizeof(No));
    strcpy(novo->valor, valor);
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

No* criar(No* raiz, char* valor, char* pista) { //cria um novo cômodo na mansão inserindo os valores posicionando-os de acordo com a ordem alfabética no lado correto das subárvores
    if (raiz == NULL) return novoNo(valor, pista);
    if (strcmp(valor, raiz->valor) < 0) { //se valor informado for menor que o valor do nó atual, então ele vai para a subárvore da esquerda
        raiz->esquerda = criar(raiz->esquerda, valor, pista);
    } else { //se valor informado for maior ou igual que o valor do nó atual, então ele vai para a subárvore da direita
        raiz->direita = criar(raiz->direita, valor, pista);
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

Pista* novaPista(char *texto) {
    Pista *nova = (Pista*) malloc(sizeof(Pista));
    strcpy(nova->texto, texto);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

Pista* inserirPista(Pista* raiz, char* texto) {
    if (raiz == NULL) return novaPista(texto);
    if (strcmp(texto, raiz->texto) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    } else {
        raiz->direita = inserirPista(raiz->direita, texto);
    }
    return raiz;
}

void mostrarPistas(Pista *raiz) {
    if(raiz != NULL){
        mostrarPistas(raiz->esquerda);
        printf("\n- %s", raiz->texto);
        mostrarPistas(raiz->direita);
    }
}

int hash(char *texto) {
    int soma = 0;
    while (*texto) {
        soma += *texto;
        texto++;
    }
    return soma % TAMANHO_HASH;
}

void inserirHash(char *pista, char *suspeito) {
    int i = hash(pista);
    while (strlen(tabelaHash[i].pista) > 0) {
        i = (i + 1) % TAMANHO_HASH;
    }
    strcpy(tabelaHash[i].pista, pista);
    strcpy(tabelaHash[i].suspeito, suspeito);
}

char* buscarSuspeito(char *pista) {
    int i = hash(pista);
    while (strlen(tabelaHash[i].pista) > 0) {
        if (strcmp(tabelaHash[i].pista, pista) == 0) return tabelaHash[i].suspeito;
        i = (i + 1) % TAMANHO_HASH;
    }
    return NULL;
}

int contarPistas(Pista *raiz, char *suspeito) {
    if (raiz == NULL) return 0;
    int total = 0;
    char *s = buscarSuspeito(raiz->texto);
    if (s != NULL && strcmp(s, suspeito) == 0) total++;
    total += contarPistas(raiz->esquerda, suspeito);
    total += contarPistas(raiz->direita, suspeito);
    return total;
}

int main() {

    No* raiz = NULL;
    No* atual = NULL;
    Pista* pistas = NULL;
    raiz = criar(raiz, "Hall de Entrada", "Inicio do Jogo");
    raiz = criar(raiz, "Sala de Estar", "Televisao e Radio");
    raiz = criar(raiz, "Biblioteca", "Muitos Livros");
    raiz = criar(raiz, "Copa", "Refeicoes em Familia");
    raiz = criar(raiz, "Cozinha", "Cheirinho bom");
    raiz = criar(raiz, "Quarto", "Descanso merecido");
    atual = raiz;

    inserirHash("Inicio do Jogo", "Ninguem");
    inserirHash("Televisao e Radio", "Mordomo");
    inserirHash("Muitos Livros", "Professor");
    inserirHash("Refeicoes em Familia", "Cozinheira");
    inserirHash("Cheirinho bom", "Cozinheira");
    inserirHash("Descanso merecido", "Mordomo");
    
    int opcao;
    do {
        printf("\n\n---------------------");
        printf("\n|  DETECTIVE QUEST  |");
        printf("\n---------------------");
        printf("\n\n-> Voce esta em: %s", atual->valor);
        if(strlen(atual->pista) > 0) { //exibir e coletar a pista do cômodo atual (sem repetir)
            printf("\n   Pista: %s", atual->pista);
            pistas = inserirPista(pistas, atual->pista);
            strcpy(atual->pista, "");
        }
        printf("\n\n1. Navegar para a esquerda");
        printf("\n2. Navegar para a direita");
        printf("\n3. Acusar um suspeito e sair");
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

    printf("\nPistas coletadas:");
    mostrarPistas(pistas);

    char acusado[50];
    printf("\n\nQuem voce acha que e o culpado? ");
    scanf("%s", acusado);
    int qtde = contarPistas(pistas, acusado);
    if (qtde >= 2) {
        printf("\nVoce solucionou o caso!");
        printf("\nExistem %d pistas contra %s.", qtde, acusado);
    } else {
        printf("\nAcusacao sem provas suficientes.");
        printf("\nForam encontradas apenas %d pistas contra %s.", qtde, acusado);
    }

    return 0;
}