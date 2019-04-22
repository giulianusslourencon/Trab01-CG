#include"CataventoOpenGl.hpp"

// Funcao responsavel por iniciar a aplicacao, nela sera dado todos os passos
// para a criacao e funcionalidades do catavento
void CataventoOpenGl::iniciar(){
	DinamicaCatavento aux;	// Variavel aux para a criacao da janela do catavento e de sua dinamica
	aux.createWindow(); 	// Cria a janela onde a aplicacao sera executada
	aux.loadShaders();		// Carrega os shaders necessarios
	aux.prepare(); 			// Passa e aloca as dimensoes do catavento
	aux.run();				// Sobrescreve a funcao run do cg_window, muda a cor da
							// janela, alem de ficar responsavel pelo desenho do catavento
							// e tambem de suas transformacoes
};
