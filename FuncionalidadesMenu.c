#include "FuncionalidadesMenu.h"
#include "FuncionalidadesArquivos.h"
#include "Menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas.h"

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
        RegistrarUsuarioEmArquivo(usuario.nome,usuario.senha);
        printf("Usu�rio cadastrado com sucesso!\n");
        EsperarInputUsuario();
    }
}
//Funcionalidades do menu do usu�rio
void AlugarLivro(int idUsuarioLogado) {
    int idSelecionado = 0;
    printf("\n===== LIVROS DISPONIVEIS PARA LOCACAO =====\n");
    VisualizarLivrosRegistrados();
    printf("\nDigite o ID do livro que deseja locar: ");

    if (scanf("%d", &idSelecionado) != 1) {
        printf("Entrada invalida!\n");
        LimparBuffer();
        EsperarInputUsuario();
        return;
    }
    LimparBuffer();

    if (ValidarIdLivro(idSelecionado) == 1) {
        int statusLocacao = VerificarLocacoes(idUsuarioLogado, idSelecionado);
        if (statusLocacao == 1) {
            printf("Voc� j� alugou este livro!\n");
        } else if (statusLocacao == 2) {
            printf("Limite m�ximo de 3 loca��es atingido!\n");
        } else {
            int resultadoPesquisa = DecrementaQuantidadeLivro(idSelecionado);
            if (resultadoPesquisa == 1) {
                RegistroLivrosLocadosPorUsuario(idSelecionado, idUsuarioLogado, LocalizarTitutoLivroPorID(idSelecionado));
                printf("Livro Alugado!\n");
            } else if (resultadoPesquisa == 0) {
                printf("Livro n�o encontrado!\n");
            } else if (resultadoPesquisa == -1) {
                printf("Livro sem estoque dispon�vel!\n");
            } else {
                printf("Erro ao abrir o arquivo de registro!\n");
            }
        }
    } else {
        printf("Livro n�o encontrado!\n");
    }

    EsperarInputUsuario();
}
void Devolver(int idUsuarioLogado)
{
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

    }while(livro.anoLancamento > 2025 || livro.anoLancamento <= 0);

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
    strcpy(livro.statusLivro,"DISPON�VEL");
    RegistrarLivrosEmArquivo(livro.titulo,livro.autor,livro.generoLiterario,livro.anoLancamento,livro.quantidadeEmEstoque,livro.statusLivro);
    printf("Livro registrado com sucesso!\n");
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
void AdicionarEstoque(){
    int idSelecionado;
    printf("Digite o ID do livro que deseja adicionar em estoque: ");
    if(scanf("%d",&idSelecionado) != 1){
        printf("Entrada inv�lida. Digite um valor n�merico!\n");
        LimparBuffer();
        EsperarInputUsuario();
        return;
    }else{
        if(ValidarIdLivro(idSelecionado) == 1){
            AdicionarQuantidade(idSelecionado);
            printf("Unidade adicionada com sucesso!\n");
        }else{
            printf("Livro n�o encontrado!\n");
        }
    }
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


