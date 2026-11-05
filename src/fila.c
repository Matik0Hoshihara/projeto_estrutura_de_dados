#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


void iniciarFila(Fila *f) {
    f->frente = NULL;
    f->tras = NULL;
}

// verifica se a fila esta vazia
int filaVazia(Fila *f) {
    return (f->frente == NULL);
}

// enfileira um ID no final da fila 
void enfileirar(Fila *f, int id) {
    NoFila *novo = (NoFila *) malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para a fila.\n");
        return;
    }

    novo->id = id;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->frente = novo;
        f->tras = novo;
    } else {
        f->tras->prox = novo;
        f->tras = novo;
    }
}

// desenfileira o ID da frente 
int desenfileirar(Fila *f, int *saida) {
    if (filaVazia(f)) {
        return 0; 
    }

    NoFila *temp = f->frente;
    *saida = temp->id;
    
    f->frente = f->frente->prox;
    if (f->frente == NULL) {
        f->tras = NULL;
    }

    free(temp);
    return 1; 
}

// libera a memoria alocada para a fila
void liberarFila(Fila *f) {
    int temp;
    while (desenfileirar(f, &temp));
}