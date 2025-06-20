#ifndef FUNCIONALIDADES_ARQUIVOS_H
#define FUNCIONALIDADES_ARQUIVOS_H
#include <stdio.h>
#include <stdlib.h>
#include "Estruturas.h"
#include <string.h>

//Sess�o Usu�rios
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
        if (sscanf(linhas,"Nome do usu�rio: %[^\n]",campoUsuario) == 1){
            continue;
        }
        if(sscanf(linhas,"Senha do usu�rio: %[^\n]",campoSenha) == 1){
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
        if(sscanf(linhas,"Nome do usu�rio: %[^\n]",campoUsuario) == 1){
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
        if(sscanf(linhas,"ID do usu�rio: %d",&id) == 1){
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
    fprintf(arquivo,"\nID do usu�rio: %d\n",usuario.ID);
    fprintf(arquivo,"Nome do usu�rio: %s\n",nomeUsuario);
    fprintf(arquivo,"Senha do usu�rio: %s\n",senhaUsuario);
    fclose(arquivo);
}
void ListarUsuariosRegistrados(){
    FILE *arquivo = fopen("Usuarios_Cadastrados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo\n");
        return;
    }
    int idLido;
    char nomeLido[60];
    char linhas[256];
    while(fgets(linhas,sizeof(linhas),arquivo)){
        if(sscanf(linhas,"ID do usu�rio: %d",&idLido) == 1){
            printf("%s",linhas);
        }
        if(sscanf(linhas,"Nome do usu�rio: %s",nomeLido) == 1){
            printf("%s",linhas);
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
        if(sscanf(linhasAtual,"Nome do usu�rio: %[^\n]",campoNome) == 1){
            if(strcmp(campoNome,nomeUsuario) == 0){
                if(sscanf(linhasAnterior,"ID do usu�rio: %d",&idUsuario) == 1){
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

//Sess�o Livros
void RegistrarLivrosEmArquivo(const char *titulo, const char *autor, const char *generoLiterario, const int anoLancamento, const int quantidadeEmEstoque, const char statusLivro){
    arquivo = fopen("Livros_Registrados.txt","a");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!");
        return;
    }
    struct Livro livro;
    livro.ID = GeradorIDLivro();
    fprintf(arquivo,"\nID do livro: %d\n",livro.ID);
    fprintf(arquivo,"Titulo: %s\n",titulo);
    fprintf(arquivo,"Autor: %s\n",autor);
    fprintf(arquivo,"G�nero liter�rio: %s\n",generoLiterario);
    fprintf(arquivo,"Ano de lan�amento: %d\n",anoLancamento);
    fprintf(arquivo,"Quantidade em estoque: %d\n",quantidadeEmEstoque);
    fprintf(arquivo,"Status: %s\n", statusLivro);//DISPONIVEL OR INDISPONIVEL
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
    FILE *arquivo = fopen("Livros_Registrados.txt","r");
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
                for(int i = 0; i < 5; i ++){
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
        printf("Livro de ID %d n�o encontrado.\n",IDProcurar);
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



//Sess�o Livros Alugados
void RegistroLivrosLocadosPorUsuario(const int idLivro,const int idUsuarioLogado,const char *nomeLivro){
    FILE *arquivo = fopen("Livros_Alugados.txt","a");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return;
    }
    fprintf(arquivo,"\nID do livro locado: %d\n",idLivro);
    fprintf(arquivo,"ID do locat�rio: %d\n",idUsuarioLogado);
    fprintf(arquivo,"Nome do livro locado: %s\n",nomeLivro);

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
        if(sscanf(linhaAtual,"ID do livro locado: %d",&idlivroAtual) == 1){
            if(fgets(linhaAtual,sizeof(linhaAtual),arquivo)){
                if(sscanf(linhaAtual,"ID do locat�rio: %d",&idlocatorioAtual) == 1){
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
void SessaoListarLivrosAlugadosUsuarios(const int idLocatario){
    FILE *arquivo = fopen("Livros_Alugados.txt","r");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return;
    }
    char linhaAtual[256];
    char campoTitulo[60] = "";
    int campoID = 0;
    while(fgets(linhaAtual,sizeof(linhaAtual),arquivo)){
        if(sscanf(linhaAtual,"ID do locat�rio: %d",&campoID) == 1){
            if(campoID == idLocatario){
                if(fgets(linhaAtual,sizeof(linhaAtual),arquivo) != NULL){
                    if(sscanf(linhaAtual,"Nome do livro locado: %[^\n]",campoTitulo) == 1){
                        printf("%s",linhaAtual);
                    }
                }
            }
        }
    }
    fclose(arquivo);
    EsperarInputUsuario();
}
void DesativarLivrosAdministrador(const int idDesativar) {//Desativar
    FILE *arquivo = fopen("Livros_Registrados.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    FILE *doacao = fopen("Livros_Doacao.txt", "a"); // acumula livros para doa��o
    if (arquivo == NULL || temp == NULL || doacao == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        if (arquivo) fclose(arquivo);
        if (temp) fclose(temp);
        if (doacao) fclose(doacao);
        return;
    }
    char linha[256];
    int idLido = -1;
    int livroEncontrado = 0;
    int dentroDoLivro = 0; // flag para saber se estamos copiando o livro atual
    char bufferLivro[1024] = ""; // para armazenar o livro inteiro
    bufferLivro[0] = '\0';
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "ID do livro: %d", &idLido) == 1) {
            // Se encontramos outro livro, checar se o anterior era o desativado
            if (dentroDoLivro) {
                if (livroEncontrado) {
                    fprintf(doacao, "%s", bufferLivro);
                } else {
                    fprintf(temp, "%s", bufferLivro);
                }
                bufferLivro[0] = '\0';
                livroEncontrado = 0;
            }
            dentroDoLivro = 1;
        }
        // Se estamos dentro do livro alvo, marca que encontramos
        if (dentroDoLivro && idLido == idDesativar) {
            livroEncontrado = 1;
        }
        // Se for a linha do status e � o livro a desativar, atualiza no buffer
        if (livroEncontrado && strstr(linha, "Status:")) {
            strcat(bufferLivro, "Status: Indisponivel\n");
        } else {
            strcat(bufferLivro, linha);
        }
    }
    // Grava o �ltimo livro lido
    if (dentroDoLivro) {
        if (livroEncontrado) {
            fprintf(doacao, "%s", bufferLivro);
        } else {
            fprintf(temp, "%s", bufferLivro);
        }
    }
    fclose(arquivo);
    fclose(temp);
    fclose(doacao);
    // Substitui o arquivo original
    remove("Livros_Registrados.txt");
    rename("temp.txt", "Livros_Registrados.txt");

    if (livroEncontrado) {
        printf("Livro de ID %d desativado e movido para doa��o.\n", idDesativar);
    } else {
        printf("Livro de ID %d n�o encontrado.\n", idDesativar);
    }
}
int UsuarioJaAlugouGenero(int idUsuario, const char *genero) {
    FILE *f = fopen("Livros_Usuario.txt", "r");
    if (!f) return 0;
    int idUser, idLivro;
    char generoLido[60];
    while (fscanf(f, "%d|%d|%29[^\n]", &idUser, &idLivro, generoLido) == 3) {
        if (idUser == idUsuario && strcmp(generoLido, genero) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
int LocalizarGeneroPorID(int idLivro, char *genero) {
    FILE *f = fopen("Livros_Alugados.txt", "r");
    if (!f) {
        printf("Erro ao abrir Livros_Alugados.txt\n");
        return 0;
    }
    struct Livro livro;
    while (fscanf(f, "%d|%99[^|]|%29[^|]|%d\n",
                  &livro.ID,
                  livro.titulo,
                  livro.generoLiterario,
                  &livro.quantidadeEmEstoque == 4) {
        if (livro.ID == idLivro) {
            strcpy(genero, livro.generoLiterario);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
int DecrementaQuantidadeLivro(int idLivro) {
    FILE *f = fopen("Livros_Alugados.txt", "r");
    if (!f) return 0;
    struct Livro livro[60];
    int total = 0;
    while (fscanf(f, "%d|%99[^|]|%29[^|]|%d\n",
           &livro[total].ID,
           livro[total].titulo,
           livro[total].generoLiterario,
           &livro[total].quantidadeEmEstoque) == 4) {
        total++;
    }
    fclose(f);
    int encontrado = 0;
    for (int i = 0; i < total; ++i) {
        if (livro[i].ID == idLivro) {
            if (livro[i].quantidadeEmEstoque <= 0) {
                return 0;
            }
            livro[i].quantidadeEmEstoque--; // decrementa
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        return 0;
    }
    f = fopen("Livros_Alugados.txt", "w");
    if (!f) return 0;
    for (int i = 0; i < total; ++i) {
        fprintf(f, "%d|%s|%s|%d\n",
                livro[i].id,
                livro[i].titulo,
                livro[i].generoLiterario,
                livro[i].quantidadeEmEstoque);
    }
    fclose(f);
    return 1;
}
int RegistroLivrosLocadosPorUsuario(int idLivro, int idUsuario, const char *genero) {
    FILE *f = fopen("Livros_Usuario.txt", "a");
    if (!f) {
        printf("Erro ao abrir Livros_Usuario.txt\n");
        return 0;
    }
    fprintf(f, "%d|%d|%s\n", idUsuario, idLivro, genero);
    fclose(f);
    return 1;
}


#endif
