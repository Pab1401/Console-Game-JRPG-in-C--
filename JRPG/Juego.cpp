#include "Juego.h"

Juego::Juego()
{
	// Creates all the requeired variables for the game to occur
	time_t now = time(0); // Uses the current date as a method of creating pesudo random stats
	char* dt = ctime(&now);
	srand(now);

	// Creates lists of characters that get linked between them through pointers
	myStart = Crear(NULL); 
	myEnd = Crear(myStart);
	myStart->next = myEnd;
	myNode = Crear(myEnd);
	myEnd->next = myNode;
	myEnd = myNode;
	myNode = Crear(myEnd);
	myEnd->next = myNode;
	myEnd = myNode;
	myEnd->next = NULL;
	myNode = nullptr;

	// Does a similar process to the first list but generates the enemies for the game
	CrearEnemigos();


}

Juego::~Juego()
{

}

int Juego::StatsCreator(int start, int marg)
{	// this is a fucntion used to create stats with a minimal value and a with a max margin of error, which will be divided by a random number in order to get the final stat
	return start + (rand() % marg);
}

void Juego::DesignateName(Party* ref) // A simple function to get the name of each of the player´s characters
{
	string name;
	cout << "What is the name of the Character?" << endl;
	cin >> name;
	ref->name = name;
}

Party* Juego::Crear(Party* Past) 
// Function to create all the stats for the party. Using the same margins for each character but using a different random number to create more unique characters
// The function creates designates the possibility of linking allied units through pointers
{
	Party* temp = new Party;
	DesignateName(temp);
	temp->HP = StatsCreator(70, 90);
	temp->ATK = StatsCreator(20, 50);
	temp->DEF = StatsCreator(15, 30);
	temp->MP = StatsCreator(20, 20);
	temp->RES = StatsCreator(15, 30);
	temp->MAG = StatsCreator(15, 30);
	temp->SPD = StatsCreator(10, 50);
	temp->alive = true;
	temp->prev = Past;
	return temp;
}

Party* Juego::CrearEn(Party* Past, int cont)
// Similar to the previous function, creates the stats but the margin is changed here in order to generate the enemies
{
	Party* temp = new Party;
	temp->name = ("Enemy " + to_string(cont));
	temp->HP = StatsCreator(50, 20);
	temp->ATK = StatsCreator(15, 30);
	temp->DEF = StatsCreator(20, 10);
	temp->MP = StatsCreator(50, 50);
	temp->RES = StatsCreator(15, 10);
	temp->MAG = StatsCreator(15, 30);
	temp->SPD = StatsCreator(10, 50);
	temp->alive = true;
	temp->prev = Past;
	return temp;
}

void Juego::CrearEnemigos()
// Creates a linked list with a random number of enemies with a minimun of 1 and a maximum of 5, in order to add more uniqueness to each instance of the game
// Links all units in the enemies through pointers
{
	int i = 1 + (rand() % 4);
	enemyStart = CrearEn(nullptr, 1);
	enemyEnd = enemyStart;
	for (int j = 0; j < i; j++)
	{
		enemyNode = CrearEn(enemyEnd, j + 2);
		enemyEnd->next = enemyNode;
		enemyEnd = enemyNode;
	}
	enemyEnd->next = NULL;
}

void Juego::SpeedPile()
{
}

bool Juego::CheckAlive(Party* ref)
// Checks if all characters on either side are dead or alive.
// Conditions for the game require all characters of either side to be dead in order to progress the game.
{
	int cont, fond;
	fond = cont = 0;
	bool found = true;;
	while (ref != NULL)
	{
		if (ref->alive == false)
			fond++;
		cont++;
		ref = ref->next;
	}
	if (fond == cont)
		found = false;
	return found;
}

int Juego::Gameplay()
// Function where the majority of the game calculations take place.
// Uses two boolean values for the while loop, which is modified by the previous function

{
	bool aParty, aEnemy;
	aParty = true;
	aEnemy = true;
	do
	{
		myNode = myStart;
		aParty = CheckAlive(myNode);
		enemyNode = enemyStart;
		aEnemy = CheckAlive(enemyNode);
		if (aParty == false || aEnemy == false)
			continue;
		while (myNode != NULL)
		{
			bool l = true;
			if (myNode->alive = true)
			{
				while (l == true)
				{
					myNode->des[0] = MuestraMenu();
					if (myNode->des[0] == 4)
					{
						if (myNode->MP < 5)
						{
							COORD pos1 = { 5, 18 };
							SetConsoleCursorPosition(hConsole, pos1);
							cout << "You do not have enough Mana to use a spell";
							placeholder = getch();
							continue;
						}
						myNode->des[1] = MuestraMenu2();
					}
					l = false;
				}
				if (myNode->des[0] != 2)
					myNode->target = TargetSelect();
			}
			myNode = myNode->next;
		}
		enemyNode = enemyStart;
		while (enemyNode != NULL)
		{
			enemyNode->des[0] = 2 * (rand() % 2);
			if (enemyNode->des[0] > 2)
				enemyNode->des[1] = 2 * (rand() % 3);
			enemyNode->target = (rand() % 4);
			enemyNode = enemyNode->next;
		}
		myNode = myStart;
		enemyNode = enemyStart;
		Combat(myNode, enemyNode);
		myNode = myStart;
		enemyNode = enemyStart;
		Combat(enemyNode, myNode);
	} while (aParty == true && aEnemy == true);
	if (aParty == false)
		return 0;
	return 1;
}

int Juego::TargetSelect()
// Uses ints and player inputs in order to select the target from the enemy team.
{
	int mark = 0;
	int tar = -1;
	while (tar == -1)
	{
		MuestraMenuPrincipal();
		enemyNode = enemyStart;
		int j = 0;
		while (enemyNode != NULL)
		{
			if (enemyNode->alive == true)
			{
				COORD pos1 = { j + 30, 10 };
				SetConsoleCursorPosition(hConsole, pos1);
				cout << "o";
				COORD pos2 = { j + 30, 11 };
				SetConsoleCursorPosition(hConsole, pos2);
				cout << "t";
				if (mark == j)
				{
					COORD pos3 = { j + 30, 13 };
					SetConsoleCursorPosition(hConsole, pos3);
					cout << "^";
					MuestraStatsPersonaje(enemyNode);
				}
				j = j + 2;
			}
			enemyNode = enemyNode->next;
		}
		SetConsoleCursorPosition(hConsole, end);
		char Men = _getch();
		if (Men == 32 || Men == 10)
		{
			tar = mark;
		}
		else if (Men == 75)
		{
			if (mark >= 2)
			{
				mark = mark - 2;
			}
		}
		else if (Men == 77)
		{
			if (mark <= j - 3)
			{
				mark = mark + 2;
			}
		}
		else
			;

	}
	return tar;
}

void Juego::Mostrar()
// Shows the main information needed for the game to progress
{
	Party* nodo;
	nodo = myStart;
	do
	{
		cout << "Stats Party Member " << nodo->name << endl;
		cout << "Attack " << nodo->ATK << endl;
		cout << "HP " << nodo->HP << endl;
		cout << "Defense " << nodo->DEF << endl;
		cout << "Mana " << nodo->MP << endl;
		cout << "Resistance " << nodo->RES << endl;
		cout << "Speed " << nodo->SPD << endl;
		cout << "Magic " << nodo->MAG << endl;
		nodo = nodo->next;
	} while (nodo != NULL);
	nodo = enemyStart;
	do
	{
		cout << "Stats " << nodo->name << endl;
		cout << "Attack " << nodo->ATK << endl;
		cout << "HP " << nodo->HP << endl;
		cout << "Defense " << nodo->DEF << endl;
		cout << "Mana " << nodo->MP << endl;
		cout << "Resistance " << nodo->RES << endl;
		cout << "Speed " << nodo->SPD << endl;
		cout << "Magic " << nodo->MAG << endl;
		nodo = nodo->next;
	} while (nodo != NULL);

}

int Juego::MuestraMenu()
// Creates and shows the options menu for each character choice, including the possible choice highlighted by the arrows wrapping the text
{
	int marker = 0;
	int des = -1;
	while (des == -1)
	{
		MuestraMenuPrincipal();
		MuestraStatsPersonaje(myNode);
		for (int j = 0; j < 5; j++)
		{
			COORD opt1 = { 6, j + 22 };
			SetConsoleCursorPosition(hConsole, opt1);
			if (j == marker)
			{
				cout << ("->" + optionsMain[j] + "<-");
			}
			else
			{
				cout << (optionsMain[j]);
			}
		}
		SetConsoleCursorPosition(hConsole, end);
		char Men = _getch();
		if (Men == 32 || Men == 10)
		{
			des = marker;
		}
		if (Men == 72)
		{
			if (marker >= 2)
			{
				marker = marker - 2;
			}
		}
		else if (Men == 80)
		{
			if (marker <= 2)
			{
				marker = marker + 2;
			}
		}
	}
	return des;
}

void Juego::MuestraMenuPrincipal()
// Creates the border for the choice menu as well as a graphical display of the remaining enemies
{
	int j = 0;
	system("cls");
	for (int i = 0; i < 16; i++)
	{
		COORD pos1 = { i + 4, 20 };
		SetConsoleCursorPosition(hConsole, pos1);
		cout << "-";
		COORD pos2 = { i + 4, 30 };
		SetConsoleCursorPosition(hConsole, pos2);
		cout << ("-");
	}
	for (int i = 0; i < 9; i++)
	{
		COORD pos1 = { 3, i + 21 };
		SetConsoleCursorPosition(hConsole, pos1);
		cout << "|";
		COORD pos2 = { 20, i + 21 };
		SetConsoleCursorPosition(hConsole, pos2);
		cout << ("|");
	}
	enemyNode = enemyStart;
	while (enemyNode != NULL)
	{
		if (enemyNode->alive == true)
		{
			COORD pos1 = { j + 30, 10 };
			SetConsoleCursorPosition(hConsole, pos1);
			cout << "o";
			COORD pos2 = { j + 30, 11 };
			SetConsoleCursorPosition(hConsole, pos2);
			cout << "t";
		}
		j = j + 2;
		enemyNode = enemyNode->next;
	}
}

void Juego::MuestraStatsPersonaje(Party* ref)
// Shows current character´s stats
{
	COORD pos1 = { 25, 23 };
	SetConsoleCursorPosition(hConsole, pos1);
	cout << "Name: " << ref->name << "\tHitpoints: " << ref->HP << "\tAttack: " << ref->ATK << "\tDefense: " << ref->DEF;
	COORD pos2 = { 25, 26 };
	SetConsoleCursorPosition(hConsole, pos2);
	cout << "Speed: " << ref->SPD << "\tMagic: " << ref->MAG << "\tMana: " << ref->MP << "\tResistance: " << ref->RES;
}

int Juego::MuestraMenu2()
// Similar to the menu function, but this one is used for the sub menus.
{
	int marker = 0;
	int des = -1;
	while (des == -1)
	{
		MuestraMenuPrincipal();
		MuestraStatsPersonaje(myNode);
		for (int j = 0; j < 5; j++)
		{
			COORD opt1 = { 6, j + 22 };
			SetConsoleCursorPosition(hConsole, opt1);
			if (j == marker)
			{
				cout << ("->" + optionMenuMagic[j] + "<-");
			}
			else
			{
				cout << (optionMenuMagic[j]);
			}
		}
		SetConsoleCursorPosition(hConsole, end);
		char Men = _getch();
		if (Men == 32 || Men == 10)
		{
			des = marker;
		}
		if (Men == 72)
		{
			if (marker >= 2)
			{
				marker = marker - 2;
			}
		}
		else if (Men == 80)
		{
			if (marker <= 2)
			{
				marker = marker + 2;
			}
		}
		else
			;
	}
	return des;
}

void Juego::Combat(Party* ref, Party* target)
// This functions processes all the combat data after all actions are selected.
// Uses the number designated earlier in the menu, which was assigned to a character, in ordere to identify which enemy to unfold the action desired.
{
	Party* temp;
	do
	{
		temp = target;
		for (int i = 0; temp != NULL; i = i + 2, temp = temp->next)
		{
			if (ref->target == i && temp->alive == true)
			{
				choiceProcess(ref, temp);
				break;
			}
		}
		ref = ref->next;
	} while (ref != NULL);
}

void Juego::choiceProcess(Party* reference, Party* targeted)
// This functions processes the actual stat modification for the receiving characters.
{
	MuestraMenuPrincipal();
	COORD pos1 = { 24, 30 };
	int damage;
	SetConsoleCursorPosition(hConsole, pos1);
	switch (reference->des[0])
	{
	case 0:
		damage = ((reference->ATK / (1 + rand() % 1)) - targeted->DEF);
		if (damage > 0)
		{
			targeted->HP = targeted->HP - damage;
			cout << targeted->name << " took " << damage << " damage.";
		}
		else
			cout << targeted->name << " took no damage";
		placeholder = getch();
		break;
	case 2:
		reference->DEF++;
		cout << "Defended";
		break;
	case 4:
		damage = ((reference->MAG / (1 + rand() % 1)) - targeted->RES);
		if (damage > 0)
		{
			targeted->HP = targeted->HP - damage;
			cout << targeted->name << " took " << damage << " damage.";
			placeholder = getch();
		}
		reference->MP = reference->MP - 5;
		break;
	default:
		break;
	}
	if (targeted->HP <= 0)
		targeted->alive = false;
}

// Binary tree used for a later iteration of the code

void Juego::Recorrer(AB* root)
{

}

void Juego::Agregar(AB* ref, Party* Pref)
{
	AB* node;
	node = BB;
	if (BB->raiz == NULL)
	{
		BB->raiz = Pref;
		return;
	}
	if (BB->raiz->SPD > Pref->SPD)
		Agregar(BB->left, Pref);
	Agregar(BB->right, Pref);
}

Party* Juego::SacarInfo(AB* root)
{
	AB* temp;
	temp = root;
	if (temp->right != NULL)
	{
		SacarInfo(temp->right);
	}
	else
	{
		return temp->raiz;
	}
	if (temp->left != NULL)
		SacarInfo(temp->left);
}
