#ifndef FILA_H
#define FILA_H

typedef struct NoFila {
    int id;
    struct NoFila *prox;
} NoFila;

// Estrutura da Fila
typedef struct {
    NoFila *frente;
    NoFila *tras;
} Fila;

// Funcoes da fila
void iniciarFila(Fila *f);
void enfileirar(Fila *f, int id);
int desenfileirar(Fila *f, int *saida);
int filaVazia(Fila *f);
void liberarFila(Fila *f);

#endif