#ifndef FUNCIONALIDADES_MENU_H
#define FUNCIONALIDADES_MENU_H
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "Menus.h"
#include "FuncionalidadesArquivos.h"
//Funcionalidades do menu dos usuários
void EntradaUsuario(){
    struct Usuario usuario;
    setlocale(LC_ALL, "Portuguese");
    printf("Digite o usuário: ");
    scanf(" %[^\n]",usuario.nome);
    printf("Digite a senha: ");
    scanf(" %[^\n]",usuario.senha);
    if(strcmp(usuario.nome,"admin") == 0 && strcmp(usuario.senha,"admin") == 0){
        LimparTela();
        MenuAdministrador();
    }else if (VerificarUsuarioExistente(usuario.nome) == 0){
        LimparTela();
        printf("Usuário não encontrado!\n");
        EsperarInputUsuario();
    }else{
        if(ValidarEntradaUsuario(usuario.nome,usuario.senha) == 1){
            LimparTela();
            int idUsuario = IdUsuarioAtual(usuario.nome);
            MenuUsuarios(idUsuario);
        }else{
            LimparTela();
            printf("Usuário ou senha incorreto!\n");
            EsperarInputUsuario();
        }
    }
}
void CadastroUsuarios(){
    struct Usuario usuario;
    setlocale(LC_ALL, "Portuguese");
    printf("MENU DE CADASTRO DOS USUÁRIOS\n");
    printf("Digite o nome do usuario: ");
    scanf("%s",usuario.nome);
    printf("Digite a senha: ");
    scanf("%s",usuario.senha);
    if(VerificarUsuarioExistente(usuario.nome) == 1){
        printf("Usuário já existe!\n");
    }else{
        printf("Usuário cadastrado com sucesso!");
        RegistrarUsuarioEmArquivo(usuario.nome,usuario.senha);
    }
}
void AlugarLivro(int idUsuarioLogado){
    int idSelecionado = 0;
    setlocale(LC_ALL,"Portuguese");
    printf("Livros disponíveis para locação: \n");
    ListarLivros();
    printf("Digite o ID do livro que deseja locar: ");
    if(scanf("%d",&idSelecionado) != 1){
        printf("Entrada inválida!\n");
        return;
    }

    if(ValidarIdLivro(idSelecionado) == 1){
        int usuarioID = idUsuarioLogado;
        int tituloID = idSelecionado;
        int statusLocacao = VerificarLocacoes(usuarioID,tituloID);
        if(statusLocacao == 1){
            printf("Livro já alugado!\n");
        }else if (statusLocacao == 2){
            printf("Locação máxima de 3 livros já atingida!\n");
        }else{
            RegistroLivrosLocadosPorUsuario(tituloID,usuarioID,LocalizarTitutoLivroPorID(tituloID));
            printf("Livro locado com sucesso!\n");
        }
    }else{
        printf("ID não encontrado!\n");
    }
    EsperarInputUsuario();
}

//Funcionalidades do menu dos administradores
void CadastroLivros(){
    setlocale(LC_ALL, "Portuguese");
    struct Livro livro;
    printf("MENU DE CADASTRO DOS LIVROS\n");
    printf("Digite o título do livro: ");
    scanf(" %[^\n]",livro.titulo);
    printf("Digite o nome do autor: ");
    scanf(" %[^\n]",livro.autor);
    printf("Digite o gênero literário: ");
    scanf(" %[^\n]",livro.generoLiterario);
    do{
        printf("Digite o ano de lançamento: ");
        if(scanf("%d",&livro.anoLancamento) != 1){
            while(getchar() != '\n');
            printf("Entrada inválida. Digite novamente!\n");
            continue;
        }

        if(livro.anoLancamento > 2025){
            printf("Ano de lançamento do livro deve ser menor ou igual ao ano atual!\n");
        }

    }while(livro.anoLancamento > 2025);

    do{
        printf("Digite a quantidade: ");
        if(scanf("%d",&livro.quantidadeEmEstoque) != 1){
            while(getchar() != '\n');
            printf("Entrada inválida. Digite novamente!\n");
            continue;

        }

        if(livro.quantidadeEmEstoque <= 0){
            printf("A quantidade não pode ser menor ou igual a zero!\n");
        }
    }while(livro.quantidadeEmEstoque <= 0);
    RegistrarLivrosEmArquivo(livro.titulo,livro.autor,livro.generoLiterario,livro.anoLancamento,livro.quantidadeEmEstoque);
}
void ConsultarLivroPorID(){
    struct Livro livro;
    printf("MENU BUSCAR POR ID\n");
    printf("Digite o id do livro para buscar: ");
    if(scanf("%d",&livro.ID) != 1){
        printf("Entrada inválida. Digite corretamente o ID!\n");
        LimparBuffer();
    }else{
        BuscarLivroPorID(livro.ID);
    }
    EsperarInputUsuario();
}
void VisualizarUsuariosCadastrados(){
    printf("Usuários cadastrados: \n");
    ListarUsuariosRegistrados();
    EsperarInputUsuario();
}
void VisualizarLivrosAlugados(){
    printf("Livros alugados: \n");
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
