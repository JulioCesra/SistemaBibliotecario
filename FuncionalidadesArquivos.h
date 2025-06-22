#ifndef FUNCIONALIDADES_ARQUIVOS_H
#define FUNCIONALIDADES_ARQUIVOS_H
//Sessão Usuários
int ValidarEntradaUsuario(const char *nomeUsuario, const char *senhaUsuario);
int VerificarUsuarioExistente(const char *nomeUsuario);
int GeradorIdUsuario();
void RegistrarUsuarioEmArquivo(const char *nomeUsuario, const char *senhaUsuario);
void ListarUsuariosRegistrados();
int IdUsuarioAtual(const char *nomeUsuario);
//Sessão Livros
void RegistrarLivrosEmArquivo(const char *titulo, const char *autor, const char *generoLiterario, const int anoLancamento, const int quantidadeEmEstoque, const char *statusLivro);
int GeradorIDLivro();
void VisualizarLivrosRegistrados();
void BuscarLivroPorID(const int IDProcurar);
int ValidarIdLivro(const int idLivro);
char* LocalizarTitutoLivroPorID(const int idLivro);
int VerificarArquivoVazio(const char *nomeArquivo);
int AdicionarQuantidade(int idLivro);
//Sessão Livros Alugados
void RegistroLivrosLocadosPorUsuario(const int idLivro,const int idUsuarioLogado,const char *nomeLivro);
int VerificarLocacoes(int idLocatorio, int idLivro);
void SessaoListarLivrosAlugadosAdministrador();
void SessaoListarLivrosAlugadosUsuarios(const int idLocatario);
int DecrementaQuantidadeLivro(int idLivro);
#endif
