#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "livro.h"
#include "bst.h"
#include "pilha.h"

//caso a linha exceda o tamanho
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//valida se nao eh vazia ou apenas espacos 
int lerStringValida(char *destino, int tamanhoMax) {
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    //emove o \n do final
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len >= sizeof(buffer) - 1) {
        limparBuffer();
    }

    //valida se nao eh apenas espacos em branco ou vazia
    int possuiCaractereValido = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            possuiCaractereValido = 1;
            break;
        }
    }

    if (!possuiCaractereValido || strlen(buffer) > (size_t)(tamanhoMax - 1)) {
        return 0;
    }

    strcpy(destino, buffer);
    return 1;
}

//validacao de inteiro positivo
int lerIntPositivo(int *valor) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;

    char *endptr;
    long num = strtol(buffer, &endptr, 10);

    //ignora espacos e \n no fim do numero
    while (isspace((unsigned char)*endptr)) endptr++;

    if (*endptr != '\0' || num <= 0 || num > 2147483647) {
        return 0; //valor invalido
    }

    *valor = (int)num;
    return 1;
}

int main() {
    NoBST *raizBST = NULL;
    Pilha pilhaLinear;
    iniciarPilha(&pilhaLinear);

    int opcao = -1;

    do {
        printf("\n========================================\n");
        printf("     SISTEMA DE ESTRUTURA DE DADOS\n");
        printf("========================================\n");
        printf("1 - Cadastrar registro na BST\n");
        printf("2 - Buscar registro por ID na BST\n");
        printf("3 - Remover registro da BST\n");
        printf("4 - Listar registros em-ordem\n");
        printf("5 - Inserir ID na estrutura linear (Pilha)\n");
        printf("6 - Remover da estrutura linear (Pilha)\n");
        printf("7 - Exibir estrutura linear (Pilha)\n");
        printf("0 - Encerrar\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");

        if (!lerIntPositivo(&opcao)) {
            printf("Opcao invalida! Digite um numero inteiro do menu.\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: {
                Livro novo;
                printf("\n--- Cadastrar Livro na BST ---\n");
                printf("Digite o ID (inteiro positivo unico): ");
                if (!lerIntPositivo(&novo.id)) {
                    printf("ID invalido! Deve ser um numero inteiro positivo.\n");
                    break;
                }

                if (buscarBST(raizBST, novo.id) != NULL) {
                    printf("Erro: Ja existe um livro cadastrado com o ID %d!\n", novo.id);
                    break;
                }

                printf("Digite o Titulo (max 79 chars): ");
                if (!lerStringValida(novo.titulo, 80)) {
                    printf("Titulo invalido! Nao pode ser vazio ou exceder 79 caracteres.\n");
                    break;
                }

                printf("Digite o Autor (max 79 chars): ");
                if (!lerStringValida(novo.autor, 80)) {
                    printf("Autor invalido! Nao pode ser vazio ou exceder 79 caracteres.\n");
                    break;
                }

                printf("Digite o Ano de Publicacao (1 a 2026): ");
                if (!lerIntPositivo(&novo.ano) || novo.ano > 2026) {
                    printf("Ano invalido! Deve ser um ano de 1 a 2026.\n");
                    break;
                }

                int sucesso = 0;
                raizBST = inserirBST(raizBST, novo, &sucesso);
                if (sucesso) {
                    printf("Livro cadastrado com sucesso na BST!\n");
                }
                break;
            }

            case 2: {
                int idBusca;
                printf("\n--- Buscar Livro por ID ---\n");
                printf("Digite o ID para busca: ");
                if (!lerIntPositivo(&idBusca)) {
                    printf("ID invalido!\n");
                    break;
                }

                NoBST *resultado = buscarBST(raizBST, idBusca);
                if (resultado != NULL) {
                    printf("\n[ENCONTRADO] ID: %d | Titulo: %s | Autor: %s | Ano: %d\n",
                           resultado->dado.id, resultado->dado.titulo, resultado->dado.autor, resultado->dado.ano);
                } else {
                    printf("Livro com ID %d nao encontrado na BST.\n", idBusca);
                }
                break;
            }

            case 3: {
                int idRemover;
                printf("\n--- Remover Livro da BST ---\n");
                printf("Digite o ID para remover: ");
                if (!lerIntPositivo(&idRemover)) {
                    printf("ID invalido!\n");
                    break;
                }

                int sucesso = 0;
                raizBST = removerBST(raizBST, idRemover, &sucesso);
                if (sucesso) {
                    printf("Livro ID %d removido com sucesso da BST!\n", idRemover);
                } else {
                    printf("Erro: Livro ID %d nao existe na BST.\n", idRemover);
                }
                break;
            }

            case 4: {
                printf("\n--- Listagem Em-Ordem (BST) ---\n");
                if (raizBST == NULL) {
                    printf("BST vazia.\n");
                } else {
                    emOrdemBST(raizBST);
                }
                break;
            }

            case 5: {
                int idLinear;
                printf("\n--- Inserir ID na Estrutura Linear (Pilha) ---\n");
                printf("Digite o ID (inteiro positivo): ");
                if (!lerIntPositivo(&idLinear)) {
                    printf("ID invalido!\n");
                    break;
                }

                AcaoHistorico acao;
                acao.tipo = CADASTRO;
                acao.id1 = idLinear;
                acao.id2 = 0;

                push(&pilhaLinear, acao);
                printf("ID %d inserido na Pilha com sucesso!\n", idLinear);
                break;
            }

            case 6: {
                printf("\n--- Remover da Estrutura Linear (Pilha) ---\n");
                AcaoHistorico rem;
                if (pop(&pilhaLinear, &rem)) {
                    printf("ID %d removido do topo da Pilha com sucesso!\n", rem.id1);
                } else {
                    printf("Estrutura linear vazia! Nenhum elemento para remover.\n");
                }
                break;
            }

            case 7: {
                printf("\n--- Exibir Estrutura Linear (Pilha) ---\n");
                exibirHistorico(&pilhaLinear);
                break;
            }

            case 0:
                printf("\nEncerrando o programa e liberando memoria...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    //libera toda a memoria alocada ao encerrar 
    liberarBST(raizBST);
    liberarPilha(&pilhaLinear);

    printf("Memoria liberada. Programa finalizado!\n");
    return 0;
}