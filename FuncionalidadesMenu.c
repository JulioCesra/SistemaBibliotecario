#include "FuncionalidadesMenu.h"
#include "FuncionalidadesArquivos.h"
#include "Menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas.h"

//Funcionalidades do menu de login
void EntradaSistema(){
    struct Usuario usuario;
    printf("\n=====LOGIN=====\n");
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
    printf("Deseja prosseguir com o cadastro? (1)-Sim | (2)-Não: ");
    int prosseguir = 0;
    if(scanf("%d",&prosseguir) != 1){
        printf("Entrada inválida. Digite somente valores númericos!\n");
        EsperarInputUsuario();
        LimparBuffer();
        return;
    }
    LimparBuffer();
    switch(prosseguir){
    case 1:
        do{
            printf("Digite o nome do usuario: ");
            scanf(" %[^\n]",usuario.nome);
            if(strlen(usuario.nome) == 0 || strlen(usuario.nome) < 6){
                printf("O nome do usuário não pode ser nulo ou ter menos que 6 caracteres!\n");
            }
        }while(strlen(usuario.nome) == 0 || strlen(usuario.nome) < 6);
        do{
            printf("Digite a senha: ");
            scanf(" %[^\n]",usuario.senha);
            if(strlen(usuario.senha) == 0 || strlen(usuario.senha) < 6){
                printf("A senha não pode ser vázia ou ter menos que 6 digitos ou caracteres!\n");
            }
        }while(strlen(usuario.senha) == 0 || strlen(usuario.senha) < 6);

        if(VerificarUsuarioExistente(usuario.nome) == 1){
            printf("Usuário já existe!\n");
        }else{
            RegistrarUsuarioEmArquivo(usuario.nome,usuario.senha);
            printf("Usuário cadastrado com sucesso!\n");
        }
        break;
    case 2:
        return;
        break;
    default:
        printf("Número digitado não encontrado nas opções!\n");
        break;
    }
    EsperarInputUsuario();
}
//Funcionalidades do menu do usuário
void AlugarLivro(int idUsuarioLogado) {
    int idSelecionado = 0;
    printf("\n=====LIVROS DISPONÍVEIS PARA LOCAÇÃO=====\n");
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
void DevolverLivroID(int idUsuarioLogado){
    printf("\n=====DEVOLVER LIVRO=====\n");
    printf("Digite o id que deseja devolver: ");
    int idSelecionado = 0;
    scanf("%d", &idSelecionado);

    FILE *arquivo = fopen("Livros_Alugados.txt", "r");
    FILE *devolvidos = fopen("Livros_Devolvidos.txt", "a");
    FILE *temp = fopen("Livros_Alugados_Temp.txt","w");

    if (arquivo == NULL || devolvidos == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha1[256];
    char linha2[256];
    char linha3[256];
    int campoIDUsuario = 0;
    int campoIDLivro = 0;
    int encontrado = 0;

    while (fgets(linha1, sizeof(linha1), arquivo)) {
        if (sscanf(linha1, "ID do locatario: %d", &campoIDUsuario) == 1) {
            if (fgets(linha2, sizeof(linha2), arquivo) &&
                sscanf(linha2, "ID do livro locado: %d", &campoIDLivro) == 1) {

                fgets(linha3, sizeof(linha3), arquivo);

                if (campoIDUsuario == idUsuarioLogado && campoIDLivro == idSelecionado) {
                    fprintf(devolvidos, "\nID do locador: %d\n", campoIDUsuario);
                    fprintf(devolvidos, "ID do livro devolvido: %d\n", campoIDLivro);
                    fprintf(devolvidos, "Nome do livro devolvido: %s\n", LocalizarTitutoLivroPorID(idSelecionado));
                    printf("Livro devolvido com sucesso!\n");
                    AdicionarQuantidade(campoIDLivro);
                    encontrado = 1;
                } else {
                    fputs(linha1, temp);
                    fputs(linha2, temp);
                    fputs(linha3, temp);
                }
            }
        }
    }

    fclose(arquivo);
    fclose(devolvidos);
    fclose(temp);

    if (!encontrado) {
        printf("Livro não encontrado!\n");
        remove("Livros_Alugados_Temp.txt");
    } else {
        remove("Livros_Alugados.txt");
        rename("Livros_Alugados_Temp.txt", "Livros_Alugados.txt");
    }

    EsperarInputUsuario();
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
    printf("\n=====USUÁRIOS CADASTRADOS=====\n");
    ListarUsuariosRegistrados();
    EsperarInputUsuario();
}
void VisualizarLivrosAlugados(){
    printf("\n=====LIVROS ALUGADOS=====\n");
    SessaoListarLivrosAlugadosAdministrador();
    EsperarInputUsuario();
}
void AdicionarEstoque(){
    printf("\n=====ADICIONAR ESTOQUE=====\n");
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


