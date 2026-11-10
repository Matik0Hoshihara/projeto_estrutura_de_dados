#include <stdio.h>
#include <stdlib.h>
#include "../include/bst.h"

NoBST* criarNoBST(Livro livro) {
    NoBST *novo = (NoBST*) malloc(sizeof(NoBST));
    if (novo == NULL) {
        printf("[ERRO] Falha ao alocar memoria para o no da BST.\n");
        return NULL;
    }
    novo->dados = livro;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

NoBST* inserirLivro(NoBST *raiz, Livro livro) {
    if (raiz == NULL) {
        return criarNoBST(livro);
    }
    if (livro.id < raiz->dados.id) {
        raiz->esquerda = inserirLivro(raiz->esquerda, livro);
    } else if (livro.id > raiz->dados.id) {
        raiz->direita = inserirLivro(raiz->direita, livro);
    }
    return raiz;
}

NoBST* buscarLivro(NoBST *raiz, int id) {
    if (raiz == NULL || raiz->dados.id == id) {
        return raiz;
    }
    if (id < raiz->dados.id) {
        return buscarLivro(raiz->esquerda, id);
    }
    return buscarLivro(raiz->direita, id);
}

static NoBST* encontrarMinimo(NoBST *no) {
    NoBST *atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

NoBST* removerLivro(NoBST *raiz, int id) {
    if (raiz == NULL) return NULL;

    if (id < raiz->dados.id) {
        raiz->esquerda = removerLivro(raiz->esquerda, id);
    } else if (id > raiz->dados.id) {
        raiz->direita = removerLivro(raiz->direita, id);
    } else {
        // Caso 1 e 2: Folha ou Apenas 1 Filho
        if (raiz->esquerda == NULL) {
            NoBST *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoBST *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // No com 2 filhos
        NoBST *temp = encontrarMinimo(raiz->direita);
        raiz->dados = temp->dados;
        raiz->direita = removerLivro(raiz->direita, temp->dados.id);
    }
    return raiz;
}

void exibirEmOrdem(NoBST *raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->esquerda);
        printf("ID: %-5d | Titulo: %-30s | Autor: %-20s | Ano: %d\n",
               raiz->dados.id, raiz->dados.titulo, raiz->dados.autor, raiz->dados.ano);
        exibirEmOrdem(raiz->direita);
    }
}

void liberarBST(NoBST *raiz) {
    if (raiz != NULL) {
        liberarBST(raiz->esquerda);
        liberarBST(raiz->direita);
        free(raiz);
    }
}