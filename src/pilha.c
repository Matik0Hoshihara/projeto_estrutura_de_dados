#include <stdio.h>
#include <stdlib.h>
#include "../include/pilha.h"

Pilha criarPilha(void) {
    Pilha p;
    p.topo = NULL;
    return p;
}

void empilhar(Pilha *p, int id) {
    NoPilha *novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (novo == NULL) {
        printf("[ERRO] Falha ao alocar memoria para a pilha.\n");
        return;
    }
    novo->id = id;
    novo->proximo = p->topo;
    p->topo = novo;
    printf("[SUCESSO] ID %d inserido na estrutura linear (Pilha).\n", id);
}

int desempilhar(Pilha *p, int *idRemovido) {
    if (p->topo == NULL) {
        return 0; // Pilha vazia
    }
    NoPilha *temp = p->topo;
    *idRemovido = temp->id;
    p->topo = temp->proximo;
    free(temp);
    return 1;
}

void exibirPilha(const Pilha *p) {
    if (p->topo == NULL) {
        printf("A estrutura linear (Pilha) esta vazia.\n");
        return;
    }
    printf("Topo -> ");
    NoPilha *atual = p->topo;
    while (atual != NULL) {
        printf("[ID: %d] ", atual->id);
        atual = atual->proximo;
    }
    printf("-> Base\n");
}

void liberarPilha(Pilha *p) {
    NoPilha *atual = p->topo;
    while (atual != NULL) {
        NoPilha *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    p->topo = NULL;
}