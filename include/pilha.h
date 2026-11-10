#ifndef PILHA_H
#define PILHA_H

typedef struct NoPilha {
    int id;
    struct NoPilha *proximo;
} NoPilha;

typedef struct {
    NoPilha *topo;
} Pilha;

Pilha criarPilha(void);
void empilhar(Pilha *p, int id);
int desempilhar(Pilha *p, int *idRemovido);
void exibirPilha(const Pilha *p);
void liberarPilha(Pilha *p);

#endif