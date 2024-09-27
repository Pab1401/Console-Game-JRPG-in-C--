#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <conio.h>
#pragma warning(disable : 4996)
#pragma once

using namespace std;

struct Party
{
	Party* next;
	string name;
	int HP;
	int ATK;
	int SPD;
	int DEF;
	int RES;
	int MAG;
	int MP;
	bool alive;
	int des[2];
	int target;
	Party* prev;
};
struct AB
{
	AB* left;
	AB* right;
	Party* raiz;
};
class Juego
{
public:
	// Para el Juego
	Juego();
	~Juego();

	//int refHP(int);
	int StatsCreator(int, int);
	void DesignateName(Party*);
	Party* Crear(Party*);
	Party* CrearEn(Party*, int);
	void CrearEnemigos();
	void SpeedPile();
	bool CheckAlive(Party*);
	int Gameplay();
	int TargetSelect();
	void Mostrar();
	int MuestraMenu();
	void MuestraMenuPrincipal();
	void MuestraStatsPersonaje(Party* ref);
	int MuestraMenu2();
	void Combat(Party*, Party*);
	void choiceProcess(Party*, Party*);


	// Para el arbol
	void Recorrer(AB*);
	void Agregar(AB*, Party*);
	Party* SacarInfo(AB*);

private:

	Party* myStart = new Party;
	Party* myNode = new Party;
	Party* myEnd = new Party;
	Party* enemyStart = new Party;
	Party* enemyNode = new Party;
	Party* enemyEnd = new Party;
	AB* BB;
	string optionsMain[5] = { "Attack", "", "Defend", "", "Magic" };
	string optionMenuMagic[7] = { "Burn", "", "Breeze", "", "Lightning", "", "Heal" };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD end = { 1, 1 };
	char placeholder;
};
