#include <string.h>
#include "../include/livro.h"

Livro criarLivro(int id, const char *titulo, const char *autor, int ano) {
    Livro l;
    l.id = id;
    strncpy(l.titulo, titulo, sizeof(l.titulo) - 1);
    l.titulo[sizeof(l.titulo) - 1] = '\0';
    strncpy(l.autor, autor, sizeof(l.autor) - 1);
    l.autor[sizeof(l.autor) - 1] = '\0';
    l.ano = ano;
    return l;
}