#ifndef LISTA_H
#define LISTA_H

typedef struct NoLista {
    int id;
    struct NoLista *prox;
} NoLista;

typedef struct {
    NoLista *inicio;
    NoLista *fim;
} Lista;

// Funcoes da lista
void iniciarLista(Lista *l);
void inserirFim(Lista *l, int id);
void exibirLista(Lista *l);
void liberarLista(Lista *l);

#endif