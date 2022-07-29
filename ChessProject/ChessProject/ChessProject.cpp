// ChessProject.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include "game.h"
#include "Player.h"
int main()
{
	Game currentGame = Game(
		std::make_unique<Player>(),
		std::make_unique<Player>());
		currentGame.start();
}