#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


void iniciarLista(Lista *l) {
    l->inicio = NULL;
    l->fim = NULL;
}

// insere um novo ID no fim da lista encadeada 
void inserirFim(Lista *l, int id) {
    NoLista *novo = (NoLista *) malloc(sizeof(NoLista));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para a lista.\n");
        return;
    }
    
    novo->id = id;
    novo->prox = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
        l->fim = novo;
    } else {
        l->fim->prox = novo;
        l->fim = novo;
    }
}

// imprime a lista do inicio ao fim
void exibirLista(Lista *l) {
    NoLista *atual = l->inicio;
    if (atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("Ordem descoberta (BFS): ");
    while (atual != NULL) {
        printf("[%d] ", atual->id);
        atual = atual->prox;
    }
    printf("\n");
}

// libera toda a memoria alocada para a lista
void liberarLista(Lista *l) {
    NoLista *atual = l->inicio;
    while (atual != NULL) {
        NoLista *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    l->inicio = NULL;
    l->fim = NULL;
}