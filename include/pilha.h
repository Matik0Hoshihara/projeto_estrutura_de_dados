#ifndef PILHA_H
#define PILHA_H

//tipo da acao realizada
typedef enum {
    CADASTRO,
    REMOCAO,
    ADD_CONEXAO,
    REM_CONEXAO
} TipoAcao;


typedef struct {
    TipoAcao tipo; // tipo da acao feita
    int id1;       // ID do livro principal
    int id2;       // Segundo ID (se for conexao entre dois livros)
} AcaoHistorico;


typedef struct NoPilha {
    AcaoHistorico dado;
    struct NoPilha *prox;
} NoPilha;


typedef struct {
    NoPilha *topo;
} Pilha;

// Funcoes da pilha
void iniciarPilha(Pilha *p);
void push(Pilha *p, AcaoHistorico acao);
int pop(Pilha *p, AcaoHistorico *saida);
int peek(Pilha *p, AcaoHistorico *saida);
void exibirHistorico(Pilha *p);
void liberarPilha(Pilha *p);

#endif