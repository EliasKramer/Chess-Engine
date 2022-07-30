// ChessProject.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include "game.h"
#include "Player.h"
#include "HumanPlayer.h"
int main()
{
	Game currentGame = Game(
		std::make_unique<HumanPlayer>(),
		std::make_unique<HumanPlayer>());
		currentGame.start();
}