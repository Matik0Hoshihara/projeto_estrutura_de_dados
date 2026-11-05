#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"


void iniciarPilha(Pilha *p) {
    p->topo = NULL;
}

// empilha uma acao concluida
void push(Pilha *p, AcaoHistorico acao) {
    NoPilha *novo = (NoPilha *) malloc(sizeof(NoPilha));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para a pilha.\n");
        return;
    }

    novo->dado = acao;
    novo->prox = p->topo;
    p->topo = novo;
}

// desempilha a acao do topo
int pop(Pilha *p, AcaoHistorico *saida) {
    if (p->topo == NULL) {
        return 0; 
    }

    NoPilha *temp = p->topo;
    *saida = temp->dado;
    p->topo = p->topo->prox;

    free(temp);
    return 1; 
}

// consulta a acao do topo sem remover 
int peek(Pilha *p, AcaoHistorico *saida) {
    if (p->topo == NULL) {
        return 0;
    }
    *saida = p->topo->dado;
    return 1;
}

// exibe ate as ultimas 5 acoes da pilha 
void exibirHistorico(Pilha *p) {
    if (p->topo == NULL) {
        printf("Historico de alteracoes vazio.\n");
        return;
    }

    printf("\n--- HISTORICO DE ALTERACOES (Ultimas 5) ---\n");
    NoPilha *atual = p->topo;
    int contador = 0;

    while (atual != NULL && contador < 5) {
        printf("%d. ", contador + 1);
        switch (atual->dado.tipo) {
            case CADASTRO:
                printf("[CADASTRO] Livro ID: %d\n", atual->dado.id1);
                break;
            case REMOCAO:
                printf("[REMOCAO] Livro ID: %d\n", atual->dado.id1);
                break;
            case ADD_CONEXAO:
                printf("[CONEXAO ADICIONADA] Entre ID %d e ID %d\n", atual->dado.id1, atual->dado.id2);
                break;
            case REM_CONEXAO:
                printf("[CONEXAO REMOVIDA] Entre ID %d e ID %d\n", atual->dado.id1, atual->dado.id2);
                break;
        }
        atual = atual->prox;
        contador++;
    }
    printf("-------------------------------------------\n");
}

// libera toda a pilha da memoria
void liberarPilha(Pilha *p) {
    AcaoHistorico temp;
    while (pop(p, &temp));
}