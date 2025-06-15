#ifndef MENUS_H
#define MENUS_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "FuncionalidadesArquivos.h"
#include "FuncionalidadesMenu.h"

int funcionamentoMenu = 1;
int opcao = 0;

void MenuUsuarios(int idUsuarioLogado){
    while(funcionamentoMenu){
        LimparTela();
        printf("\n=====MENU DO USUÁRIO=====\n");
        printf("1 - Alugar livro\n");
        printf("2 - Meus livros alugados\n");
        printf("3 - Sair do menu do usuário\n");
        printf("Digite o número correspondente com à opção desejada:  ");
        scanf("%d",&opcao);
        switch(opcao){
        case 1:
            AlugarLivro(idUsuarioLogado);
            break;
        case 2:
            printf("Livros Alugados\n");
            SessaoListarLivrosAlugadosUsuarios(idUsuarioLogado);
            break;
        case 3:
            funcionamentoMenu = 0;
            break;
        }
    }
}
void MenuAdministrador(){
    while(funcionamentoMenu){
        LimparTela();
        printf("\n=====TELA DO ADMINISTRADOR=====\n");
        printf("1 - Registrar livros\n");
        printf("2 - Consultar livro por ID\n");
        printf("3 - Quantidade de livros em estoque\n");
        printf("4 - Visualizar livros registrados\n");
        printf("5 - Visualizar usuários cadastrados\n");
        printf("6 - Visualizar livros alugados\n");
        printf("7 - Sair\n");
        printf("Digite o número correspondente com à opção desejada: ");
        scanf("%d",&opcao);
        switch(opcao){
        case 1:
            LimparTela();
            CadastroLivros();
            break;
        case 2:
            LimparTela();
            ConsultarLivroPorID();
            break;
        case 4:
            LimparTela();
            ListarLivros();
            break;
        case 5:
            LimparTela();
            VisualizarUsuariosCadastrados();
            break;
        case 6:
            LimparTela();
            VisualizarLivrosAlugados();
            break;
        case 7:
            LimparTela();
            funcionamentoMenu = 0;
            break;
        default:
            printf("Digite uma opção válida!\n");
            break;
        }
    }
}

void MenuLogin(){
    while(funcionamentoMenu){
        LimparTela();
        printf("\n=====MENU DE LOGIN=====\n");
        printf("1 - Entrar no sistema\n");
        printf("2 - Cadastrar usuário\n");
        printf("3 - Sair do menu de login\n");
        printf("Digite o número correspondente com à opção desejada: ");
        scanf("%d",&opcao);
        switch(opcao){
        case 1:
            LimparTela();
            EntradaUsuario();
            break;
        case 2:
            LimparTela();
            CadastroUsuarios();
            break;
        case 3:
            LimparTela();
            funcionamentoMenu = 0;
            break;
        default:
            printf("Digite uma opção válida!\n");
            break;
        }
    }
}
void MenuPrincipal(){
    while(funcionamentoMenu){
        LimparTela();
        printf("\n=====SISTEMA BIBLIOTECÁRIO=====\n");
        printf("1 - Ir para a tela de login\n");
        printf("2 - Encerrar programa\n");
        printf("Digite o número correspondente com à opção desejada: ");
        scanf("%d",&opcao);
        switch(opcao){
        case 1:
            LimparTela();
            MenuLogin(funcionamentoMenu);
            break;
        case 2:
            funcionamentoMenu = 0;
            break;
        default:
            printf("Digite uma opção válida!\n");
            EsperarInputUsuario();
            break;
        }
    }
}

#endif
