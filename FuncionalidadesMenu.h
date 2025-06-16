#ifndef FUNCIONALIDADES_MENU_H
#define FUNCIONALIDADES_MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menus.h"
#include "FuncionalidadesArquivos.h"
//Funcionalidades do menu de login
void EntradaSistema(){
    struct Usuario usuario;
    printf("\n=====ENTRADA DO SISTEMA=====\n");
    printf("Digite o usu�rio: ");
    scanf(" %[^\n]",usuario.nome);
    printf("Digite a senha: ");
    scanf(" %[^\n]",usuario.senha);
    if(strcmp(usuario.nome,"admin") == 0 && strcmp(usuario.senha,"admin") == 0){
        LimparTela();
        MenuAdministrador();
    }else if (VerificarUsuarioExistente(usuario.nome) == 0){
        LimparTela();
        printf("Usu�rio n�o encontrado!\n");
        EsperarInputUsuario();
    }else{
        if(ValidarEntradaUsuario(usuario.nome,usuario.senha) == 1){
            LimparTela();
            int idUsuario = IdUsuarioAtual(usuario.nome);
            MenuUsuarios(idUsuario);
        }else{
            LimparTela();
            printf("Usu�rio ou senha incorreto!\n");
            EsperarInputUsuario();
        }
    }
}
void CadastrarUsuario(){
    struct Usuario usuario;
    printf("\n=====CADASTRO DO USU�RIO=====\n");
    printf("Digite o nome do usuario: ");
    scanf("%s",usuario.nome);
    printf("Digite a senha: ");
    scanf("%s",usuario.senha);
    if(VerificarUsuarioExistente(usuario.nome) == 1){
        printf("Usu�rio j� existe!\n");
    }else{
        printf("Usu�rio cadastrado com sucesso!");
        RegistrarUsuarioEmArquivo(usuario.nome,usuario.senha);
        EsperarInputUsuario();
    }
}

//Funcionalidades do menu do usu�rio
void AlugarLivro(int idUsuarioLogado){
    struct LivroAlugado livroAlugado;
    int idSelecionado = 0;
    printf("\n=====LIVROS DISPON�VEIS PARA LOCA��O=====\n");
    VisualizarLivrosRegistrados();
    printf("Digite o ID do livro que deseja locar: ");
    if(scanf("%d",&idSelecionado) != 1){
        printf("Entrada inv�lida!\n");
        return;
    }

    if(ValidarIdLivro(idSelecionado) == 1){
        livroAlugado.IDLocador = idUsuarioLogado;
        livroAlugado.IDLivro = idSelecionado;
        int statusLocacao = VerificarLocacoes(livroAlugado.IDLocador,livroAlugado.IDLivro);
        if(statusLocacao == 1){
            printf("Livro j� alugado!\n");
        }else if (statusLocacao == 2){
            printf("Loca��o m�xima de 3 livros atingida!\n");
        }else{
            RegistroLivrosLocadosPorUsuario(livroAlugado.IDLivro,livroAlugado.IDLocador,LocalizarTitutoLivroPorID(livroAlugado.IDLivro));
            printf("Livro locado com sucesso!\n");
        }
    }else{
        printf("ID digitado n�o encontrado!\n");
    }
    EsperarInputUsuario();
}

//Funcionalidades do menu dos administradores
void RegistrarLivro(){
    struct Livro livro;
    printf("\n=====REGISTAR LIVRO=====\n");
    printf("Digite o t�tulo do livro: ");
    scanf(" %[^\n]",livro.titulo);
    printf("Digite o nome do autor: ");
    scanf(" %[^\n]",livro.autor);
    printf("Digite o g�nero liter�rio: ");
    scanf(" %[^\n]",livro.generoLiterario);
    do{
        printf("Digite o ano de lan�amento: ");
        if(scanf("%d",&livro.anoLancamento) != 1){
            while(getchar() != '\n');
            printf("Entrada inv�lida. Digite novamente!\n");
            continue;
        }

        if(livro.anoLancamento > 2025){
            printf("Ano de lan�amento do livro deve ser menor ou igual ao ano atual!\n");
        }

    }while(livro.anoLancamento > 2025);

    do{
        printf("Digite a quantidade: ");
        if(scanf("%d",&livro.quantidadeEmEstoque) != 1){
            while(getchar() != '\n');
            printf("Entrada inv�lida. Digite novamente!\n");
            continue;

        }

        if(livro.quantidadeEmEstoque <= 0){
            printf("A quantidade n�o pode ser menor ou igual a zero!\n");
        }
    }while(livro.quantidadeEmEstoque <= 0);
    RegistrarLivrosEmArquivo(livro.titulo,livro.autor,livro.generoLiterario,livro.anoLancamento,livro.quantidadeEmEstoque);
}
void ConsultarLivroPorID(){
    struct Livro livro;
    printf("\n=====BUSCA POR ID=====\n");
    printf("Digite o id do livro para buscar: ");
    if(scanf("%d",&livro.ID) != 1){
        printf("Entrada inv�lida. Digite corretamente o ID!\n");
        LimparBuffer();
    }else{
        BuscarLivroPorID(livro.ID);
    }
    EsperarInputUsuario();
}
void VisualizarUsuariosCadastrados(){
    printf("\n=====Usu�rios cadastrados=====\n");
    ListarUsuariosRegistrados();
    EsperarInputUsuario();
}
void VisualizarLivrosAlugados(){
    printf("\n=====Livros alugados=====\n");
    SessaoListarLivrosAlugadosAdministrador();
    EsperarInputUsuario();
}

//Funcionalidades para todos os menus
void LimparTela(){
    system("cls");
}
void EsperarInputUsuario(){
    system("Pause");
}
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
#endif
