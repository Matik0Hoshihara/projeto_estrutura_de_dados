#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

NoBST* inserirBST(NoBST *raiz, Livro livro, int *sucesso) {
    if (raiz == NULL) {
        NoBST *novo = (NoBST *) malloc(sizeof(NoBST));
        if (novo == NULL) {
            *sucesso = 0;
            return NULL;
        }
        novo->dado = livro;
        novo->esq = NULL;
        novo->dir = NULL;
        *sucesso = 1;
        return novo;
    }

    if (livro.id < raiz->dado.id) {
        raiz->esq = inserirBST(raiz->esq, livro, sucesso);
    } else if (livro.id > raiz->dado.id) {
        raiz->dir = inserirBST(raiz->dir, livro, sucesso);
    } else {
        // ID duplicado nao permitido
        *sucesso = 0;
    }

    return raiz;
}

// busca recursiva por ID 
NoBST* buscarBST(NoBST *raiz, int id) {
    if (raiz == NULL || raiz->dado.id == id) {
        return raiz;
    }
    if (id < raiz->dado.id) {
        return buscarBST(raiz->esq, id);
    }
    return buscarBST(raiz->dir, id);
}

// encontra menor ID
NoBST* buscarMenorID(NoBST *raiz) {
    NoBST *atual = raiz;
    while (atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

// encontra maior ID
NoBST* buscarMaiorID(NoBST *raiz) {
    NoBST *atual = raiz;
    while (atual && atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

// exibe livros em ordem crescente de ID
void emOrdemBST(NoBST *raiz) {
    if (raiz != NULL) {
        emOrdemBST(raiz->esq);
        printf("ID: %d | Titulo: %s | Autor: %s | Ano: %d\n", 
               raiz->dado.id, raiz->dado.titulo, raiz->dado.autor, raiz->dado.ano);
        emOrdemBST(raiz->dir);
    }
}

// 3 casos: 0, 1 ou 2 filhos 
NoBST* removerBST(NoBST *raiz, int id, int *sucesso) {
    if (raiz == NULL) {
        *sucesso = 0; // ID nao encontrado
        return NULL;
    }

    if (id < raiz->dado.id) {
        raiz->esq = removerBST(raiz->esq, id, sucesso);
    } else if (id > raiz->dado.id) {
        raiz->dir = removerBST(raiz->dir, id, sucesso);
    } else {
        // Encontrou o nó para remover
        *sucesso = 1;

        // caso 1: 0 filhos ou Caso 2: 1 filho a direita
        if (raiz->esq == NULL) {
            NoBST *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        // caso 2: 1 filho a esquerda
        else if (raiz->dir == NULL) {
            NoBST *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // caso 3: 2 filhos (substitui pelo menor elemento da subarvore a direita)
        NoBST *temp = buscarMenorID(raiz->dir);
        raiz->dado = temp->dado;
        raiz->dir = removerBST(raiz->dir, temp->dado.id, sucesso);
    }
    return raiz;
}

// libera toda a arvore da memoria 
void liberarBST(NoBST *raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->esq);
        liberarBST(raiz->dir);
        free(raiz);
    }
}