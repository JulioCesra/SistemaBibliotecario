#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

struct Usuario{
    int ID;
    char nome[60];
    char senha[60];
};

struct Livro{
    int ID;
    char titulo[60];
    char autor[60];
    char generoLiterario[60];
    int anoLancamento;
    int quantidadeEmEstoque;
};

struct LivroAlugado{
    int IDLivro;
    int IDLocador;
    char nomeLocador[60];
};

#endif
