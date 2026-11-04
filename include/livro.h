#ifndef LIVRO_H
#define LIVRO_H


typedef struct {
    int id;             // ID unico positivo
    char titulo[80];    // Titulo do livro (ate 79 caracteres)
    char autor[80];     // Autor do livro
    int ano;            // Ano de publicacao (1 a 2026)
} Livro;

#endif