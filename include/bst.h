#ifndef BST_H
#define BST_H

#include "livro.h"

typedef struct NoBST {
    Livro dados;
    struct NoBST *esquerda;
    struct NoBST *direita;
} NoBST;

NoBST* criarNoBST(Livro livro);
NoBST* inserirLivro(NoBST *raiz, Livro livro);
NoBST* buscarLivro(NoBST *raiz, int id);
NoBST* removerLivro(NoBST *raiz, int id);
void exibirEmOrdem(NoBST *raiz);
void liberarBST(NoBST *raiz);

#endif