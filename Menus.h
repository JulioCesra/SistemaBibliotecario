#ifndef MENUS_H
#define MENUS_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "FuncionalidadesArquivos.h"
#include "FuncionalidadesMenu.h"

void MenuUsuarios(int idUsuarioLogado){
    setlocale(LC_ALL,"Portuguese");
    int opcao;
    int funcionamentoMenu = 1;
    while(funcionamentoMenu){
        LimparTela();
        printf("MENU DO USUÁRIO\n");
        printf("(1) - Alugar livro\n");
        printf("(2) - Livros alugados\n");
        printf("(3) - Sair\n");
        printf("Digite uma das opções acima: ");
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
    setlocale(LC_ALL,"Portuguese");
    int opcao;
    int funcionamentoMenu = 1;
    while(funcionamentoMenu){
        LimparTela();
        printf("TELA DO ADMINISTRADOR\n\n");
        printf("(1) - Registrar livros\n");
        printf("(2) - Consultar livro por ID\n");
        printf("(3) - Quantidade de livros em estoque\n");
        printf("(4) - Listar livros\n");
        printf("(5) - Visualizar usuários cadastrados\n");
        printf("(6) - Visualizar livros alugados\n");
        printf("(7) - Sair\n");
        printf("Digite uma das opçãos acima: ");
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
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    int funcionamentoMenu = 1;
    while(funcionamentoMenu){
        LimparTela();
        printf("MENU DE LOGIN\n");
        printf("(1) - Entrar\n");
        printf("(2) - Cadastrar usuário\n");
        printf("(3) - Voltar para o menu principal\n");
        printf("Digite uma das opções acima: ");
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
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    int funcionamentoMenu = 1;
    while(funcionamentoMenu){
        LimparTela();
        printf("SISTEMA BIBLIOTECÁRIO\n");
        printf("(1) - Tela de login\n");
        printf("(2) - Sair\n");
        printf("Digite um das opções: ");
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
