#ifndef FUNCIONALIDADES_MENU_H
#define FUNCIONALIDADES_MENU_H

void EntradaSistema();
void CadastrarUsuario();
//Funcionalidades do menu do usuário
void AlugarLivro(int idUsuarioLogado);
void Devolver(int idUsuarioLogado);
void DevolverLivroID(int idUsuarioLogado);
//Funcionalidades do menu dos administradores
void RegistrarLivro();
void ConsultarLivroPorID();
void VisualizarUsuariosCadastrados();
void VisualizarLivrosAlugados();
void AdicionarEstoque();
//Funcionalidades para todos os menus
void LimparTela();
void EsperarInputUsuario();
void LimparBuffer();

#endif
