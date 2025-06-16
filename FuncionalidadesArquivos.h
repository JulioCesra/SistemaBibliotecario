#ifndef FUNCIONALIDADES_ARQUIVOS_H
#define FUNCIONALIDADES_ARQUIVOS_H
#include <stdio.h>
#include <stdlib.h>
#include "Estruturas.h"
#include <string.h>

//Sessão Usuários
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
        if(sscanf(linhas,"ID do usuário: %d",&idLido) == 1){
            printf("%s",linhas);
        }
        if(sscanf(linhas,"Nome do usuário: %s",nomeLido) == 1){
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

//Sessão Livros
void RegistrarLivrosEmArquivo(const char *titulo, const char *autor, const char *generoLiterario, const int anoLancamento, const int quantidadeEmEstoque){
    FILE *arquivo;
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
    fprintf(arquivo,"Gênero literário: %s\n",generoLiterario);
    fprintf(arquivo,"Ano de lançamento: %d\n",anoLancamento);
    fprintf(arquivo,"Quantidade em estoque: %d\n",quantidadeEmEstoque);
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



//Sessão Livros Alugados
void RegistroLivrosLocadosPorUsuario(const int idLivro,const int idUsuarioLogado,const char *nomeLivro){
    FILE *arquivo = fopen("Livros_Alugados.txt","a");
    if(arquivo == NULL){
        printf("Error ao abrir o arquivo!\n");
        return;
    }
    fprintf(arquivo,"\nID do livro locado: %d\n",idLivro);
    fprintf(arquivo,"ID do locatário: %d\n",idUsuarioLogado);
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
                if(sscanf(linhaAtual,"ID do locatário: %d",&idlocatorioAtual) == 1){
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
        if(sscanf(linhaAtual,"ID do locatário: %d",&campoID) == 1){
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
#endif
