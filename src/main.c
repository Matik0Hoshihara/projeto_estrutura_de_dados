#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/livro.h"
#include "../include/bst.h"
#include "../include/pilha.h"

// Limpa o buffer de entrada caso a linha exceda o tamanho maximo
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Leitura de inteiro isolada, imune a quebras de linha acumuladas no buffer
int lerInteiroValido(int *val) {
    char buffer[128];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    char *endptr;
    long v = strtol(buffer, &endptr, 10);

    // Ignora espacos no final
    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    // Valida se nao contem letras ou valor invalido
    if (endptr == buffer || *endptr != '\0' || v <= 0) {
        return 0;
    }

    *val = (int)v;
    return 1;
}

// Garante max 79 caracteres e proibe strings vazias
int lerStringValida(const char *rotulo, char *destino, int tamanhoMax) {
    char buffer[256];
    while (1) {
        printf("%s", rotulo);
        fflush(stdout);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            } else {
                limparBuffer();
            }

            // Remove espacos nas extremidades para validar
            char *inicio = buffer;
            while (isspace((unsigned char)*inicio)) inicio++;

            if (*inicio == '\0') {
                printf("[ERRO] Texto invalido! Nao pode ser vazio ou conter apenas espacos.\n");
                fflush(stdout);
                continue;
            }

            if (strlen(inicio) >= (size_t)tamanhoMax) {
                printf("[ERRO] Texto muito longo! Limite maximo de %d caracteres.\n", tamanhoMax - 1);
                fflush(stdout);
                continue;
            }

            strncpy(destino, inicio, tamanhoMax - 1);
            destino[tamanhoMax - 1] = '\0';
            return 1;
        }
    }
}

// Cadastrar registro na BST
void opcaoCadastrarBST(NoBST **raiz) {
    int id = 0, ano = 0;
    char titulo[80], autor[80];

    printf("\n--- CADASTRAR REGISTRO NA BST ---\n");
    fflush(stdout);

    // Validacao do ID
    while (1) {
        printf("Digite o ID (inteiro positivo unico): ");
        fflush(stdout);
        if (lerInteiroValido(&id)) {
            if (buscarLivro(*raiz, id) != NULL) {
                printf("[ERRO] ID %d ja cadastrado na BST. Digite um ID unico.\n", id);
                fflush(stdout);
            } else {
                break; // ID valido e unico!
            }
        } else {
            printf("[ERRO] ID invalido! Digite apenas numeros inteiros maiores que 0.\n");
            fflush(stdout);
        }
    }

    // Validacao do Titulo e Autor
    lerStringValida("Digite o Titulo (max 79 chars): ", titulo, sizeof(titulo));
    lerStringValida("Digite o Autor (max 79 chars): ", autor, sizeof(autor));

    // Validacao do Ano
    while (1) {
        printf("Digite o Ano de Publicacao (1 a 2026): ");
        fflush(stdout);
        if (lerInteiroValido(&ano) && ano >= 1 && ano <= 2026) {
            break; // Ano aceito!
        }
        printf("[ERRO] Ano invalido! Digite um numero inteiro entre 1 e 2026.\n");
        fflush(stdout);
    }

    // Insercao na BST
    Livro novo = criarLivro(id, titulo, autor, ano);
    *raiz = inserirLivro(*raiz, novo);

    printf("\n[SUCESSO] Livro '%s' (ID: %d, Ano: %d) cadastrado com sucesso na BST!\n", titulo, id, ano);
    fflush(stdout);
}

// Buscar registro por ID na BST
void opcaoBuscarBST(NoBST *raiz) {
    int id = 0;
    printf("\n--- BUSCAR REGISTRO POR ID NA BST ---\n");
    fflush(stdout);

    while (1) {
        printf("Digite o ID para busca: ");
        fflush(stdout);
        if (lerInteiroValido(&id)) break;
        printf("[ERRO] ID invalido! Digite um inteiro positivo.\n");
        fflush(stdout);
    }

    NoBST *res = buscarLivro(raiz, id);
    if (res != NULL) {
        printf("\n[REGISTRO ENCONTRADO]\n");
        printf("ID: %d | Titulo: %s | Autor: %s | Ano: %d\n",
               res->dados.id, res->dados.titulo, res->dados.autor, res->dados.ano);
    } else {
        printf("\n[AVISO] ID %d nao encontrado na BST.\n", id);
    }
    fflush(stdout);
}

// Remover registro da BST
void opcaoRemoverBST(NoBST **raiz) {
    int id = 0;
    printf("\n--- REMOVER REGISTRO DA BST ---\n");
    fflush(stdout);

    while (1) {
        printf("Digite o ID para remover: ");
        fflush(stdout);
        if (lerInteiroValido(&id)) break;
        printf("[ERRO] ID invalido! Digite um inteiro positivo.\n");
        fflush(stdout);
    }

    if (buscarLivro(*raiz, id) == NULL) {
        printf("\n[ERRO] Nao foi possivel remover: ID %d nao existe na BST.\n", id);
        fflush(stdout);
        return;
    }

    *raiz = removerLivro(*raiz, id);
    printf("\n[SUCESSO] Registro ID %d removido da BST com sucesso!\n", id);
    fflush(stdout);
}

// Inserir ID na estrutura linear (Pilha)
void opcaoInserirPilha(Pilha *p) {
    int id = 0;
    printf("\n--- INSERIR ID NA ESTRUTURA LINEAR (PILHA) ---\n");
    fflush(stdout);

    while (1) {
        printf("Digite o ID para inserir na pilha (inteiro positivo): ");
        fflush(stdout);
        if (lerInteiroValido(&id)) break;
        printf("[ERRO] ID invalido! Digite apenas numeros inteiros positivos maiores que 0.\n");
        fflush(stdout);
    }
    empilhar(p, id);
    fflush(stdout);
}

// Remover da estrutura linear (Pilha)
void opcaoRemoverPilha(Pilha *p) {
    int idRemovido;
    printf("\n--- REMOVER DA ESTRUTURA LINEAR (PILHA) ---\n");
    fflush(stdout);

    if (desempilhar(p, &idRemovido)) {
        printf("[SUCESSO] ID %d removido do topo da pilha!\n", idRemovido);
    } else {
        printf("[AVISO] A estrutura linear esta vazia. Nao ha o que remover.\n");
    }
    fflush(stdout);
}

int main() {
    NoBST *raiz = NULL;
    Pilha pilha = criarPilha();
    int opcao = -1;

    do {
        printf("\n=========================================\n");
        printf("     SISTEMA DE GESTAO DE BIBLIOTECA     \n");
        printf("=========================================\n");
        printf("1 - Cadastrar registro na BST\n");
        printf("2 - Buscar registro por ID na BST\n");
        printf("3 - Remover registro da BST\n");
        printf("4 - Listar registros em-ordem\n");
        printf("5 - Inserir ID na estrutura linear\n");
        printf("6 - Remover da estrutura linear\n");
        printf("7 - Exibir estrutura linear\n");
        printf("0 - Encerrar\n");
        printf("=========================================\n");
        printf("Escolha uma opcao: ");
        fflush(stdout);

        if (!lerInteiroValido(&opcao) && opcao != 0) {
            char buf[64];
            if (fgets(buf, sizeof(buf), stdin) != NULL) {
                opcao = atoi(buf);
            }
        }

        switch (opcao) {
            case 1:
                opcaoCadastrarBST(&raiz);
                break;
            case 2:
                opcaoBuscarBST(raiz);
                break;
            case 3:
                opcaoRemoverBST(&raiz);
                break;
            case 4:
                printf("\n--- LISTAGEM EM-ORDEM (BST) ---\n");
                if (raiz == NULL) {
                    printf("A BST esta vazia.\n");
                } else {
                    exibirEmOrdem(raiz);
                }
                fflush(stdout);
                break;
            case 5:
                opcaoInserirPilha(&pilha);
                break;
            case 6:
                opcaoRemoverPilha(&pilha);
                break;
            case 7:
                printf("\n--- ESTRUTURA LINEAR (PILHA) ---\n");
                exibirPilha(&pilha);
                fflush(stdout);
                break;
            case 0:
                printf("\nEncerrando o programa e liberando memoria...\n");
                liberarBST(raiz);
                liberarPilha(&pilha);
                printf("Memoria liberada com sucesso. Programa encerrado!\n");
                fflush(stdout);
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Escolha um numero de 0 a 7.\n");
                fflush(stdout);
        }
    } while (opcao != 0);

    return 0;
}