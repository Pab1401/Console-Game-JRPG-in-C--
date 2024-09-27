#include "Juego.h"

int main()
{
//Creates the class of the game
	Juego game;
	int i;
	i = game.Gameplay();
	system("cls");
	if (i == 1)
		cout << "YOU WON!";
	else
		cout << "You lost.";
}