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
void CadastrarUsuario(){
    struct Usuario usuario;
    printf("\n=====CADASTRO DO USUÁRIO=====\n");
    printf("Digite o nome do usuario: ");
    scanf("%s",usuario.nome);
    printf("Digite a senha: ");
    scanf("%s",usuario.senha);
    if(VerificarUsuarioExistente(usuario.nome) == 1){
        printf("Usuário já existe!\n");
    }else{
        RegistrarUsuarioEmArquivo(usuario.nome,usuario.senha);
        printf("Usuário cadastrado com sucesso!\n");
        EsperarInputUsuario();
    }
}
//Funcionalidades do menu do usuário
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
            printf("Você já alugou este livro!\n");
        } else if (statusLocacao == 2) {
            printf("Limite máximo de 3 locações atingido!\n");
        } else {
            int resultadoPesquisa = DecrementaQuantidadeLivro(idSelecionado);
            if (resultadoPesquisa == 1) {
                RegistroLivrosLocadosPorUsuario(idSelecionado, idUsuarioLogado, LocalizarTitutoLivroPorID(idSelecionado));
                printf("Livro Alugado!\n");
            } else if (resultadoPesquisa == 0) {
                printf("Livro não encontrado!\n");
            } else if (resultadoPesquisa == -1) {
                printf("Livro sem estoque disponível!\n");
            } else {
                printf("Erro ao abrir o arquivo de registro!\n");
            }
        }
    } else {
        printf("Livro não encontrado!\n");
    }

    EsperarInputUsuario();
}
void DevolverLivroID(int idUsuarioLogado) {
    struct Livro livro;
    printf("\n===== DEVOLUCAO DE LIVRO =====\n");
    printf("Digite o ID do livro alugado: ");
    if (scanf("%d", &livro.ID) != 1) {
        printf("Entrada invalida. Digite corretamente o ID!\n");
        LimparBuffer();
        EsperarInputUsuario();
        return;
    }
    struct LivroAlugado registros[100];
    int totalRegistros = 0;
    FILE *fUsuario = fopen("Livros_Usuario.txt", "r");
    if (!fUsuario) {
        printf("Erro ao abrir Livros_Usuario.txt!\n");
        EsperarInputUsuario();
        return;
    }
    struct LivroAlugado registro;
    int encontrado = 0;
    while (fscanf(fUsuario, "%d|%d|%59[^\n]",
                  &registro.IDLocador,
                  &registro.IDLivro,
                  registro.nomeLocador) == 3) {
        if (registro.IDLocador == idUsuarioLogado && registro.IDLivro == livro.ID) {
            encontrado = 1;
        } else {
            registros[totalRegistros++] = registro;
        }
    }
    fclose(fUsuario);
    if (!encontrado) {
        printf("Você não tem este livro alugado!\n");
        EsperarInputUsuario();
        return;
    }
    // Reescreve o arquivo atual sem o registro do livro devolvido
    fUsuario = fopen("Livros_Usuario.txt", "w");
    if (!fUsuario) {
        printf("Erro ao abrir Livros_Usuario.txt para escrita!\n");
        EsperarInputUsuario();
        return;
    }
    for (int i = 0; i < totalRegistros; ++i) {
        fprintf(fUsuario, "%d|%d|%s\n",
                registros[i].IDLocador,
                registros[i].IDLivro,
                registros[i].nomeLocador);
    }
    fclose(fUsuario);
    // Devolve o livro para estoque
    LivrosDevolucao(livro.ID);
}



//Funcionalidades do menu dos administradores
void RegistrarLivro(){
    struct Livro livro;
    printf("\n=====REGISTAR LIVRO=====\n");
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

    }while(livro.anoLancamento > 2025 || livro.anoLancamento <= 0);

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
    strcpy(livro.statusLivro,"DISPONÍVEL");
    RegistrarLivrosEmArquivo(livro.titulo,livro.autor,livro.generoLiterario,livro.anoLancamento,livro.quantidadeEmEstoque,livro.statusLivro);
    printf("Livro registrado com sucesso!\n");
}
void ConsultarLivroPorID(){
    struct Livro livro;
    printf("\n=====BUSCA POR ID=====\n");
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
    printf("\n=====Usuários cadastrados=====\n");
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
        printf("Entrada inválida. Digite um valor númerico!\n");
        LimparBuffer();
        EsperarInputUsuario();
        return;
    }else{
        if(ValidarIdLivro(idSelecionado) == 1){
            AdicionarQuantidade(idSelecionado);
            printf("Unidade adicionada com sucesso!\n");
        }else{
            printf("Livro não encontrado!\n");
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


