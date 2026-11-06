#ifndef BST_H
#define BST_H

#include "livro.h"

// BST
typedef struct NoBST {
    Livro dado;
    struct NoBST *esq;
    struct NoBST *dir;
} NoBST;

// funcoes BST
NoBST* inserirBST(NoBST *raiz, Livro livro, int *sucesso);
NoBST* buscarBST(NoBST *raiz, int id);
NoBST* removerBST(NoBST *raiz, int id, int *sucesso);
void emOrdemBST(NoBST *raiz);
NoBST* buscarMenorID(NoBST *raiz);
NoBST* buscarMaiorID(NoBST *raiz);
void liberarBST(NoBST *raiz);

#endif