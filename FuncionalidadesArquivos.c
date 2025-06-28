#include "FuncionalidadesMenu.h"
#include "FuncionalidadesArquivos.h"
#include "Menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas.h"
#include <time.h>


//Funcionalidades gerais
char* DataAtual(){
    time_t tempo_atual;
    struct tm *info_tempo;
    char *data = malloc(80);

    if(data == NULL){
        return NULL;
    }

    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);

    strftime(data,80,"%d/%m/%Y %H:%M:%S",info_tempo);
    return data;
}
int VerificarArquivoVazio(const char* nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo,"r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return 1;
    }
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fclose(arquivo);

    return (tamanho == 0);

}

//Funcionalidades relacionadas ao usuário
int ValidarEntradaUsuario(const char *nomeUsuario, const char *senhaUsuario){
    FILE *arquivo;
    arquivo = fopen("Usuarios_Cadastrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!");
        return 0;
    }
    char linhas[256];
    char campoUsuario[60] = "";
    char campoSenha[60] = "";
    while(fgets(linhas,sizeof(linhas),arquivo)){
        linhas[strcspn(linhas,"\r\n")] = '\0';
        if (sscanf(linhas,"Nome do usuário: %[^\n]",campoUsuario) == 1){
            continue;
        }
        if(sscanf(linhas,"Senha do usuário: %[^\n]",campoSenha) == 1){
            if(strcmp(nomeUsuario,campoUsuario) == 0 && strcmp(senhaUsuario,campoSenha) == 0){
                fclose(arquivo);
                return 1;
            }
        }

        campoUsuario[0] = '\0';
        campoSenha[0] = '\0';
    }
    fclose(arquivo);
    return 0;

}
int VerificarUsuarioExistente(const char *nomeUsuario){
    FILE *arquivo;
    arquivo = fopen("Usuarios_Cadastrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo.\n");
        return 0;
    }
    char linhas[256];
    char campoUsuario[60] = "";
    int usuarioEncontrado = 0;
    while(fgets(linhas, sizeof(linhas),arquivo)){
        linhas[strcspn(linhas,"\r\n")] = '\0';
        if(sscanf(linhas,"Nome do usuário: %[^\n]",campoUsuario) == 1){
            if(strcmp(campoUsuario,nomeUsuario) == 0){
                return usuarioEncontrado = 1;
                break;
            }
        }
    }
    fclose(arquivo);
    return 0;

}
int GeradorIdUsuario(){
    char linhas[256];
    int id = 0;
    int idMaximo = 0;
    FILE *arquivo = fopen("Usuarios_Cadastrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao acessar o arquivo!");
        return 1;
    }

    while(fgets(linhas, sizeof(linhas), arquivo)){
        if(sscanf(linhas,"ID do usuário: %d",&id) == 1){
            if(id > idMaximo){
                idMaximo = id;
            }
        }
    }
    fclose(arquivo);
    return idMaximo + 1;
}
void RegistrarUsuarioEmArquivo(const char *nomeUsuario, const char *senhaUsuario){
    FILE *arquivo;
    arquivo = fopen("Usuarios_Cadastrados.txt","a+");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo\n");
        return;
    }

    struct Usuario usuario;
    usuario.ID = GeradorIdUsuario();
    fprintf(arquivo,"\nID do usuário: %d\n",usuario.ID);
    fprintf(arquivo,"Nome do usuário: %s\n",nomeUsuario);
    fprintf(arquivo,"Senha do usuário: %s\n",senhaUsuario);
    fprintf(arquivo,"Data e horario do registro: %s\n",DataAtual());
    fclose(arquivo);
}
void ListarUsuariosRegistrados(){
    char *nomeArquivo = "Usuarios_Cadastrados.txt";
    if(VerificarArquivoVazio(nomeArquivo)){
        printf("Nenhum usuário cadastrado!\n");
    }else{
        FILE *arquivo = fopen(nomeArquivo,"r");
        int idLido;
        char nomeLido[60];
        char linhas[256];
        while(fgets(linhas,sizeof(linhas),arquivo)){
            if(sscanf(linhas,"ID do usuário: %d",&idLido) == 1){
                printf("%s",linhas);
            }
            if(sscanf(linhas,"Nome do usuário: %s",nomeLido) == 1){
                printf("%s",linhas);
            }
        }
    }
}
int IdUsuarioAtual(const char *nomeUsuario){
    FILE *arquivo = fopen("Usuarios_Cadastrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return 0;
    }
    char linhasAtual[256];
    char linhasAnterior[256] = "";
    int idUsuario = 0;
    char campoNome[60] = "";
    while(fgets(linhasAtual,sizeof(linhasAtual),arquivo)){
        linhasAtual[strcspn(linhasAtual, "\r\n")] = '\0';
        if(sscanf(linhasAtual,"Nome do usuário: %[^\n]",campoNome) == 1){
            if(strcmp(campoNome,nomeUsuario) == 0){
                if(sscanf(linhasAnterior,"ID do usuário: %d",&idUsuario) == 1){
                    fclose(arquivo);
                    return idUsuario;
                }
            }
        }
        strcpy(linhasAnterior,linhasAtual);
    }
    fclose(arquivo);
    return 0;

}

//Funcionalidades relacionadas ao livro
void RegistrarLivrosEmArquivo(const char *titulo, const char *autor, const char *generoLiterario, const int anoLancamento, const int quantidadeEmEstoque, const char *statusLivro){
    FILE *arquivo = fopen("Livros_Registrados.txt","a");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!");
        return;
    }
    struct Livro livro;
    livro.ID = GeradorIDLivro();
    fprintf(arquivo,"\nID do livro: %d\n",livro.ID);
    fprintf(arquivo,"Titulo: %s\n",titulo);
    fprintf(arquivo,"Autor: %s\n",autor);
    fprintf(arquivo,"Gênero literário: %s\n",generoLiterario);
    fprintf(arquivo,"Ano de lançamento: %d\n",anoLancamento);
    fprintf(arquivo,"Quantidade em estoque: %d\n",quantidadeEmEstoque);
    fprintf(arquivo,"Status: %s\n", statusLivro);
    fprintf(arquivo,"Data e horrio do registro: %s\n",DataAtual());
    fclose(arquivo);

}
int GeradorIDLivro(){
    char linhas[256];
    int id = 0;
    int idMaximo = 0;
    FILE *arquivo = fopen("Livros_Registrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao acessar o arquivo!");
        return 1;
    }
    while(fgets(linhas,sizeof(linhas),arquivo)){
        if(sscanf(linhas,"ID do livro: %d",&id) == 1){
            if(id > idMaximo){
                idMaximo = id;
            }
        }
    }
    fclose(arquivo);
    return idMaximo + 1;
}
void VisualizarLivrosRegistrados(){
    char *nomeArquivo = "Livros_Registrados.txt";
    if(VerificarArquivoVazio(nomeArquivo)){
        printf("Nenhum livro registrado!\n");
    }else{
        FILE *arquivo = fopen(nomeArquivo,"r");
        if(arquivo == NULL){
            printf("Error ao abrir o arquivo!");
            return;
        }
        char linhas[256];
        while(fgets(linhas,sizeof(linhas),arquivo)){
            printf("%s",linhas);
        }
        fclose(arquivo);
    }
}
void BuscarLivroPorID(const int IDProcurar){
    FILE *arquivo = fopen("Livros_Registrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!");
        return;
    }
    char linhas[256];
    int idLido;
    int livroEncontrado = 0;
    while(fgets(linhas,sizeof(linhas),arquivo)){
        if(sscanf(linhas,"ID do livro: %d",&idLido) == 1){
            if(idLido == IDProcurar){
                printf("%s",linhas);
                for(int i = 0; i < 6; i ++){
                    if (fgets(linhas,sizeof(linhas),arquivo)){
                        printf("%s",linhas);
                    }
                }
                livroEncontrado = 1;
                break;
            }
        }
    }
    if(livroEncontrado == 0){
        printf("Livro de ID %d não encontrado.\n",IDProcurar);
    }
    fclose(arquivo);
}
int ValidarIdLivro(const int idLivro){
    FILE *arquivo = fopen("Livros_Registrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return 0;
    }

    int campoID = 0;
    char linhaAtual[256];
    while(fgets(linhaAtual,sizeof(linhaAtual),arquivo)){
        if(sscanf(linhaAtual,"ID do livro: %d",&campoID) == 1){
            if(campoID == idLivro){
                fclose(arquivo);
                return 1;
            }
        }
    }
    fclose(arquivo);
    return 0;
}
char* LocalizarTitutoLivroPorID(const int idLivro){
    FILE *arquivo = fopen("Livros_Registrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return NULL;
    }
    int campoID = 0;
    char linhaAtual[256];
    static char campoTitulo[60];
    while(fgets(linhaAtual,sizeof(linhaAtual),arquivo)){
        if(sscanf(linhaAtual,"ID do livro: %d",&campoID) == 1){
            if(campoID == idLivro){
                if(fgets(linhaAtual,sizeof(linhaAtual),arquivo)){
                    if(sscanf(linhaAtual,"Titulo: %[^\n]",campoTitulo) == 1){
                        fclose(arquivo);
                        return campoTitulo;
                    }
                }
            }
        }
    }
    fclose(arquivo);
    return NULL;
}
int AdicionarQuantidade(int idLivro) {
    FILE *temp = fopen("Livros_Registrados_Temporario.txt", "w");
    FILE *arquivo = fopen("Livros_Registrados.txt", "r");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    char linha[256];
    int idAtual = -1;
    int quantidade = 0;
    int encontrado = 0;
    int atualizarStatus = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "ID do livro: %d", &idAtual) == 1) {
            fprintf(temp, "%s", linha);
            continue;
        }

        if (sscanf(linha, "Quantidade em estoque: %d", &quantidade) == 1 && idAtual == idLivro) {
            if (quantidade == 0) {
                quantidade+=1;
                fprintf(temp, "Quantidade em estoque: %d\n", quantidade);
                atualizarStatus = 1;
                encontrado = 1;
            }else if(quantidade > 0){
                quantidade += 1;
                fprintf(temp, "Quantidade em estoque: %d\n", quantidade);
                atualizarStatus = 1;
                encontrado = 1;
            } else {
                fprintf(temp, "%s", linha);
                encontrado = -1;
            }
            continue;
        }

        if (atualizarStatus && strncmp(linha, "Status:", 7) == 0) {
            fprintf(temp, "Status: DISPONÍVEL\n");
            atualizarStatus = 0;
            continue;
        }

        fprintf(temp, "%s", linha);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado == 1) {
        remove("Livros_Registrados.txt");
        rename("Livros_Registrados_Temporario.txt", "Livros_Registrados.txt");
        return 1;
    } else {
        remove("Livros_Registrados_Temporario.txt");
        return encontrado;
    }
}
void RegistroLivrosLocadosPorUsuario(const int idLivro,const int idUsuarioLogado,const char *nomeLivro){
    FILE *arquivo = fopen("Livros_Alugados.txt","a");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return;
    }
    fprintf(arquivo,"\nID do locatario: %d\n",idUsuarioLogado);
    fprintf(arquivo,"ID do livro locado: %d\n",idLivro);
    fprintf(arquivo,"Nome do livro locado: %s\n",nomeLivro);
    fprintf(arquivo,"Data e horario locado: %s\n",DataAtual());

    fflush(arquivo);
    fclose(arquivo);
}
int VerificarLocacoes(int idLocatorio, int idLivro){
    FILE *arquivo = fopen("Livros_Alugados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return -1;
    }
    char linhaAtual[256];
    int idlivroAtual = 0;
    int idlocatorioAtual = 0;
    int contadorLocacoes = 0;
    int mesmoLivro = 0;

    while(fgets(linhaAtual,sizeof(linhaAtual),arquivo)){
        if(sscanf(linhaAtual,"ID do locatario: %d",&idlocatorioAtual) == 1){
            if(fgets(linhaAtual,sizeof(linhaAtual),arquivo)){
                if(sscanf(linhaAtual,"ID do livro locado: %d",&idlivroAtual) == 1){
                    if(idlocatorioAtual == idLocatorio){
                        contadorLocacoes ++;
                        if(idlivroAtual == idLivro){
                            mesmoLivro = 1;
                        }
                    }
                }
                fgets(linhaAtual,sizeof(linhaAtual),arquivo);
            }
        }
    }
    fclose(arquivo);

    if(mesmoLivro == 1){
        return 1;
    }else if (contadorLocacoes >= 3){
        return 2;
    }
    return 0;
}
void SessaoListarLivrosAlugadosAdministrador(){
    char *nomeArquivo = "Livros_Alugados.txt";
    if(VerificarArquivoVazio(nomeArquivo)){
        printf("Nenhum livro alugado!\n");
    }else{
        FILE *arquivo = fopen("Livros_Alugados.txt","r");
        if(arquivo == NULL){
            printf("Error ao abrir o arquivo!\n");
            return;
        }
        char linhaAtual[256];
        while(fgets(linhaAtual,sizeof(linhaAtual),arquivo)){
            printf("%s",linhaAtual);
        }
        fclose(arquivo);
    }
}
void SessaoListarLivrosAlugadosUsuarios(const int idLocatario){
    FILE *arquivo = fopen("Livros_Alugados.txt", "r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return;
    }

    char linhaAtual[256];
    int campoID = 0;
    int campoIDLivro = 0;
    char campoTitulo[60] = "";
    int mostrarProximo = 0;

    while(fgets(linhaAtual, sizeof(linhaAtual), arquivo)) {
        if(sscanf(linhaAtual, "ID do livro locado: %d", &campoIDLivro) == 1) {
            continue;
        }
        if(sscanf(linhaAtual, "ID do locatario: %d", &campoID) == 1) {
            if(campoID == idLocatario) {
                mostrarProximo = 1;
            } else {
                mostrarProximo = 0;
            }
            continue;
        }

        if(mostrarProximo && sscanf(linhaAtual, "Nome do livro locado: %[^\n]", campoTitulo) == 1) {
            printf("ID do livro: %d - Nome: %s\n", campoIDLivro, campoTitulo);
        }
    }

    fclose(arquivo);
    EsperarInputUsuario();
}
int DecrementaQuantidadeLivro(int idLivro) {
    FILE *arquivo = fopen("Livros_Registrados.txt", "r");
    FILE *temp = fopen("Livros_Registrados_Temporario.txt", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return -2;
    }

    char linha[256];
    int idAtual = -1;
    int quantidade = 0;
    int encontrado = 0;
    int atualizarStatus = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "ID do livro: %d", &idAtual) == 1) {
            fprintf(temp, "%s", linha);
            continue;
        }
        if (sscanf(linha, "Quantidade em estoque: %d", &quantidade) == 1 && idAtual == idLivro) {
            if (quantidade > 0) {
                quantidade--;
                fprintf(temp, "Quantidade em estoque: %d\n", quantidade);
                encontrado = 1;
                if (quantidade == 0) {
                    atualizarStatus = 1;
                }
                continue;
            } else {
                encontrado = -1;
                fprintf(temp, "%s", linha);
                continue;
            }
        }
        if (atualizarStatus && strncmp(linha, "Status:", 7) == 0) {
            fprintf(temp, "Status: INDISPONÍVEL\n");
            atualizarStatus = 0;
            continue;
        }
        fprintf(temp, "%s", linha);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado == 1) {
        remove("Livros_Registrados.txt");
        rename("Livros_Registrados_Temporario.txt", "Livros_Registrados.txt");
        return 1;
    } else if (encontrado == -1) {
        remove("Livros_Registrados_Temporario.txt");
        return -1;
    } else {
        remove("Livros_Registrados_Temporario.txt");
        return 0;
    }
    return 0;
}
void VisualizarLivrosDevolvidos(){
    if(VerificarArquivoVazio("Livros_Devolvidos.txt")){
        printf("Nenhum livro devolvido!\n");
    }else{
        FILE *arquivo = fopen("Livros_Devolvidos.txt", "r");

        if(arquivo == NULL){
            printf("Erro no arquivo!\n");
            return;
        }

        char linhas[256];
        printf("\n====REGISTRO DOS LIVROS DEVOLVIDOS====\n");
        while(fgets(linhas,sizeof(linhas),arquivo)){
            printf("%s",linhas);
        }
    }
    EsperarInputUsuario();
}
