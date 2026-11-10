#ifndef LIVRO_H
#define LIVRO_H

typedef struct {
    int id;
    char titulo[80];
    char autor[80];
    int ano;
} Livro;

Livro criarLivro(int id, const char *titulo, const char *autor, int ano);

#endif