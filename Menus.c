#include "FuncionalidadesMenu.h"
#include "FuncionalidadesArquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas.h"
#include <locale.h>

int opcao = 0;
void MenuUsuarios(int idUsuarioLogado){
    int funcionamentoMenu = 1;
    while(funcionamentoMenu){
        LimparTela();
        printf("\n=====MENU DO USU�RIO=====\n");
        printf("1 - Alugar livro\n");
        printf("2 - Meus livros alugados\n");
        printf("3 - Devolver livro\n");
        printf("4 - Sair do menu do usu�rio\n");
        printf("Digite o n�mero correspondente com � op��o desejada:  ");
        if(scanf("%d",&opcao) != 1){
            printf("Op��o inv�lida. Digite apenas n�meros!\n");
            EsperarInputUsuario();
            LimparBuffer();
            continue;
        }
        switch(opcao){
        case 1:
            LimparTela();
            AlugarLivro(idUsuarioLogado);
            break;
        case 2:
            LimparTela();
            SessaoListarLivrosAlugadosUsuarios(idUsuarioLogado);
            break;
        case 3:
            LimparTela();
            DevolverLivroID(idUsuarioLogado);
            break;
        case 4:
            LimparTela();
            funcionamentoMenu = 0;
            break;
        default:
            printf("N�mero digitado n�o encontrado nas op��es!\n");
            EsperarInputUsuario();
            break;
        }
    }
}
void MenuAdministrador(){
    int funcionamentoMenu = 1;
    while(funcionamentoMenu){
        LimparTela();
        printf("\n=====MENU DO ADMINISTRADOR=====\n");
        printf("1 - Registrar livros\n");
        printf("2 - Consultar livro por ID\n");
        printf("3 - Visualizar livros registrados\n");
        printf("4 - Visualizar usu�rios cadastrados\n");
        printf("5 - Visualizar livros alugados\n");
        printf("6 - Adicionar estoque\n");
        printf("7 - Visualizar livros devolvidos\n");
        printf("8 - Sair do menu do administrador\n");
        printf("Digite o n�mero correspondente com � op��o desejada: ");
        if(scanf("%d",&opcao) != 1){
            printf("Op��o inv�lida. Digite apenas n�meros!\n");
            EsperarInputUsuario();
            LimparBuffer();
            continue;
        }
        switch(opcao){
        case 1:
            LimparTela();
            RegistrarLivro();
            EsperarInputUsuario();
            break;
        case 2:
            LimparTela();
            ConsultarLivroPorID();
            break;
        case 3:
            LimparTela();
            VisualizarLivrosRegistrados();
            EsperarInputUsuario();
            break;
        case 4:
            LimparTela();
            VisualizarUsuariosCadastrados();
            break;
        case 5:
            LimparTela();
            VisualizarLivrosAlugados();
            break;
        case 6:
            LimparTela();
            AdicionarEstoque();
            break;
        case 7:
            LimparTela();
            VisualizarLivrosDevolvidos();
            break;
        case 8:
            LimparTela();
            funcionamentoMenu = 0;
            break;
        default:
            printf("N�mero digitado n�o encontrado nas op��es!\n");
            EsperarInputUsuario();
            break;
        }
    }
}
void MenuLogin(){
    int funcionamentoMenu = 1;
    while(funcionamentoMenu){
        LimparTela();
        printf("\n=====MENU DE LOGIN=====\n");
        printf("1 - Entrar no sistema\n");
        printf("2 - Cadastrar usu�rio\n");
        printf("3 - Sair do menu de login\n");
        printf("Digite o n�mero correspondente com � op��o desejada: ");
        if(scanf("%d",&opcao) != 1){
            printf("Op��o inv�lida. Digite apenas n�meros!\n");
            EsperarInputUsuario();
            LimparBuffer();
            continue;
        }
        switch(opcao){
        case 1:
            LimparTela();
            EntradaSistema();
            break;
        case 2:
            LimparTela();
            CadastrarUsuario();
            break;
        case 3:
            LimparTela();
            funcionamentoMenu = 0;
            break;
        default:
            printf("N�mero digitado n�o encontrado nas op��es!\n");
            EsperarInputUsuario();
            break;
        }
    }
}
void MenuPrincipal(){
    int funcionamentoMenu = 1;
    while(funcionamentoMenu){
        LimparTela();
        printf("\n=====SISTEMA BIBLIOTEC�RIO=====\n");
        printf("1 - Ir para a tela de login\n");
        printf("2 - Encerrar programa\n");
        printf("Digite o n�mero correspondente com � op��o desejada: ");
        if(scanf("%d",&opcao) != 1){
            printf("Op��o inv�lida. Digite apenas n�meros!\n");
            EsperarInputUsuario();
            LimparBuffer();
            continue;
        }
        switch(opcao){
        case 1:
            LimparTela();
            MenuLogin(funcionamentoMenu);
            break;
        case 2:
            funcionamentoMenu = 0;
            break;
        default:
            printf("N�mero digitado n�o encontrado nas op��es!\n");
            EsperarInputUsuario();
            break;
        }
    }
}

