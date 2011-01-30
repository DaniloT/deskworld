/*
 * Universidade de Brasilia
 * Instituto de Ciencias Exatas
 * Departamento de Ciencia da Computacao
 *
 * Introducao ao Desenvolvimento de Jogos - 01/2010
 *
 * Alunos:  Danilo Gaby Andersen Trindade - 06/82039
 * 			Victor Sampaio Zucca 		  - 06/25566
 * Turma: A
 *
 * Descricao: Jogo livre onde o jogador pode criar o que desejar na tela. Os botoes
 * a esquerda permitem a selecao da ferramenta desejada para construcao, podendo alterar
 * entre objetos estaticos e dinamicos.
 */

#include "GameManager.h"

int main(int argc, char **argv) {
	//Call the game manager to start the game.
	GameManager *gameManager;
	gameManager = new GameManager();
	gameManager->run();
	delete gameManager;
	return 0;
}
