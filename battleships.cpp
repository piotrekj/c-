#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;


class Board;
class Ship;


class Board
{
private:
	int x, y;
	char **tab;
public:
	Board(int = 25, int = 25);
	~Board();

	void wypisz();

	friend int wstaw(Board &p, Ship &s);
	friend class Menu;
	friend void ustaw(Board &p, Menu &m);
	friend int ustaw_gracz(Board &p, Menu &m);
	friend int strzal(Board &p, int x, int y, Board &p2);
	void zeroj();
	int czy_brak_statkow();
	int random(char);
};

Board::Board(int xx, int yy)
{
	x = xx;
	y = yy;
	tab = new char*[x];
	for (int i = 0; i < x; i++)
	{
		tab[i] = new char[y];
		for (int j = 0; j < y; j++)
			tab[i][j] = ' ';
	}
}
Board::~Board()
{
	for (int i = 0; i < x; i++)
		delete[] tab[i];
	delete tab;
	tab = NULL;
}
void Board::wypisz()
{
	char z = 'A';
	cout << "   | ";
	for (int i = 0; i < x; i++)
		cout << (char)(z + i);
	cout << endl;

	cout << "   | ";
	for (int i = 0; i < x; i++)
		cout << "_";
	cout << endl;

	for (int i = 0; i < y; i++, cout << endl)
	{
		if (i < 10)
			cout << i << "  | ";
		else
			cout << i << " | ";
		for (int j = 0; j < x; j++)
			cout << tab[j][i];
	}

}
void Board::zeroj()
{
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			tab[i][j] = ' ';
}
int Board::czy_brak_statkow()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
			if ('1' < tab[i][j] && tab[i][j] < '6')
				return 0;
	}
	return 1;
}
int Board::random(char znak)
{
	switch (znak)
	{

	case 'x':
		return rand() % x;
		break;
	case 'y':
		return rand() % y;
		break;
	default:
		break;
	}
	return 0;
}


class Ship
{
private:
	int x, y, kierunek, dlugosc;

public:
	Ship(int = 1, int = 1, int = 1, int = 1);
	~Ship();

	friend int wstaw(Board &p, Ship &s);
	void load(int, int, int, int);
};

Ship::Ship(int xx, int yy, int d, int k)
{
	x = xx;
	y = yy;
	dlugosc = d;
	kierunek = k;
}
Ship::~Ship()
{

}
void Ship::load(int xx, int yy, int dd, int kk)
{
	x = xx;
	y = yy;
	dlugosc = dd;
	kierunek = kk;
}



class Menu
{
private:
	int m1;
	int m2;
	int m3;

	int m;
	int n;
	int mm;
	int nn;

	int ship[6];
	int cheat;

	int ilosc_pol;
	int zajete_pola;

public:
	Menu();
	~Menu();

	friend void ustaw(Board &p, Menu &m);
	friend int ustaw_gracz(Board &p, Menu &m);

	int wyswietl();
	int opcje();
	int ustawienia();

	int get(char);

};

Menu::Menu()
{
	m1 = 0;
	m2 = 0;
	m3 = 0;

	m = n = 12;

	mm = nn = 12;

	cheat = 0;

	ship[0] = 0;
	ship[1] = 0;
	ship[2] = 4;
	ship[3] = 3;
	ship[4] = 2;
	ship[5] = 1;

	ilosc_pol = m*n;
	zajete_pola = 0;
	for (int i = 2; i <= 5; i++)
		zajete_pola += ship[i] * i;
}
Menu::~Menu()
{

}
int Menu::wyswietl()
{

	do
	{
		system("cls");

		cout << "1 Graj" << endl;
		cout << "2 Ustawienia" << endl;

		cout << endl << "3 Wyjscie" << endl;

		cout << endl << "Wybierz : ";

		cin.sync();
		cin.clear();
		cin >> m1;

		if (!cin.good())
		{
			cout << endl << "Podales zly znak" << endl;
			cout << endl << "wylaczam program :/" << endl;
			system("pause");
			return 5;
		}
		if (1 > m1 || m1 > 4)
		{
			cout << "Podales zla liczbe" << endl;
			system("pause");
		}

	} while (1 > m1 || m1 > 4);

	return m1;
}
int Menu::opcje()
{
	switch (m1)
	{
	case 1:
		do
		{
			system("cls");

			cout << "1 Player vs Player" << endl;
			cout << "2 Player vs PC" << endl;
			cout << "3 PC vs PC" << endl;
			cout << endl << "4 Wroc" << endl;


			cout << endl << "Wybierz: ";
			cin >> m2;

			if (!cin.good())
			{
				cout << endl << "Podales zly znak" << endl;
				cout << endl << "wylaczam program :/" << endl;
				system("pause");
				return 5;
			}
			if (1 > m2 || m2 > 4)
			{
				cout << "Podales zla liczbe" << endl;
				system("pause");
			}

		} while (1 > m2 || m2 > 4);
		break;
	case 2:
		do
		{
			system("cls");

			cout << "1 Wielkosc planszy" << endl;
			cout << "   szerokosc  : " << m << endl;
			cout << "   wysokosc   : " << n << endl;

			cout << endl << "2 Ilosc statkow" << endl;

			for (int i = 2; i < 6; i++)
				cout << "   ship " << i << "x1 : " << ship[i] << endl;

			cout << endl << "3 CHEAT MODE : ";
			if (cheat == 0)
				cout << "OFF" << endl;
			else
				cout << "ON" << endl;

			cout << endl << "4 Wroc" << endl;


			cout << endl << "Wybierz: ";

			cin >> m2;
			if (!cin.good())
			{
				cout << endl << "Podales zly znak" << endl;
				cout << endl << "wylaczam program :/" << endl;
				system("pause");
				return 5;
			}
			if (1 > m2 || m2 > 4)
			{
				cout << "Podales zla liczbe" << endl;
				system("pause");
			}

		} while (1 > m2 || m2 > 4);
		break;

	default:
		break;
	}
	return m2;
}
int Menu::ustawienia()
{

	switch (m2)
	{
	case 1:

		do {
			system("cls");
			cout << "Podaj szerokosc (od 5 do 26): ";
			cin >> mm;

			if (!cin.good())
			{
				cout << endl << "Podales zly znak" << endl;
				cout << endl << "wylaczam program :/" << endl;
				system("pause");
				return 5;
			}
			if (5 > mm || mm > 26)
			{
				cout << "Podales zla liczbe" << endl;
				system("pause");
			}

			ilosc_pol = mm*n;

			if (ilosc_pol < (zajete_pola * 4))
			{
				cout << endl << "Niewystarczajaca ilosc miejsca na tyle statkow!" << endl;
				mm = 30;
				cout << "ilosc_pol = " << ilosc_pol << "  zajete_pola*4 = " << zajete_pola * 4 << endl;
				system("pause");
			}

		} while (5 > mm || mm > 26);

		m = mm;
		ilosc_pol = m * n;

		do {
			cout << "Podaj wysokosc (od 5 do 100): ";
			cin >> nn;

			if (!cin.good())
			{
				cout << endl << "Podales zly znak" << endl;
				cout << endl << "wylaczam program :/" << endl;
				system("pause");
				return 5;
			}
			if (5 > nn || nn > 100)
			{
				cout << "Podales zla liczbe" << endl;
				system("pause");
			}

			ilosc_pol = m * nn;

			if (ilosc_pol < (zajete_pola * 4))
			{
				cout << endl << "Niewystarczajaca ilosc miejsca na tyle statkow!" << endl;
				nn = 101;
				cout << "ilosc_pol = " << ilosc_pol << "  zajete_pola*4 = " << zajete_pola * 4 << endl;
				system("pause");
			}

		} while (5 > nn || nn > 100);

		n = nn;

		ilosc_pol = m * n;
		break;
	case 2:
		for (int i = 2; i < 6; i++)
		{
			do {
				system("cls");
				cout << "Podaj ilosc statkow " << i << "x1 : ";
				cin >> ship[i];

				if (!cin.good())
				{
					cout << endl << "Podales zly znak" << endl;
					cout << endl << "wylaczam program :/" << endl;
					system("pause");
					return 5;
				}
				if (ship < 0)
				{
					cout << "Podales zla liczbe" << endl;
					system("pause");
				}

				zajete_pola = 0;
				for (int j = 2; j < 6; j++)
					zajete_pola += ship[i] * i;

				if (ilosc_pol < (zajete_pola * 4))
				{
					cout << endl << "Niewystarczajaca ilosc miejsca na tyle statkow!" << endl;
					ship[i] = -1;
					system("pause");

				}
			} while (ship[i] < 0);
		}
		break;
	case 3:
		do {
			system("cls");
			cout << "0 = OFF" << endl;
			cout << "1 = ON" << endl;
			cout << endl << "Podaj liczbe (od 0 do 1): ";
			cin >> cheat;
			cout << cheat << endl;

			if (!cin.good())
			{
				cout << endl << "Podales zly znak" << endl;
				cout << endl << "wylaczam program :/" << endl;
				system("pause");
				return 5;
			}

			if (cheat < 0 || cheat >1)
			{
				cout << "Podales zla liczbe" << endl;
				system("pause");
			}

		} while (cheat < 0 || cheat >1);

		break;
	case 4:
		break;
	default:
		break;
	}

	return 0;
}
int Menu::get(char z)
{
	switch (z)
	{
	case 'm':
		return m;
		break;
	case 'n':
		return n;
		break;
	case 'c':
		return cheat;
		break;
	default:
		cout << "Nie ma takiego parametru w Menu!" << endl;
		return 0;
		break;
	}
}



int wstaw(Board &p, Ship &s)
{
	bool z = 0;

	if (p.tab[s.x][s.y] == ' ')
	{
		int gora, dol, prawo, lewo;

		switch (s.kierunek)
		{

		case 2://kierunek V
			if ((s.y + s.dlugosc) < p.y)
				for (int i = 0; i < s.dlugosc; i++)
				{
					if (p.tab[s.x][s.y + i] != ' ')
						z = 1;
				}
			else
				z = 1;

			if (z == 0)
			{
				gora = s.y;
				dol = s.y + s.dlugosc - 1;
				prawo = s.x;
				lewo = s.x;

				for (int i = lewo - 1; i <= prawo + 1; i++)   //bufor statku
					if (0 <= i && i < p.x)
						for (int j = gora - 1; j <= dol + 1; j++)
						{
							if (0 <= j && j < p.y)
							{
								p.tab[i][j] = '#';
							}

						}



				for (int i = 0; i < s.dlugosc; i++)
				{
					p.tab[s.x][s.y + i] = 48 + s.dlugosc;
				}
			}
			else
			{


				return 2;
			}
			return 0;
			break;


		case 4:
			if ((s.x - s.dlugosc + 1) >= 0)
				for (int i = 0; i < s.dlugosc; i++)
				{
					if (p.tab[s.x - i][s.y] != ' ')
						z = 1;
				}
			else
				z = 1;

			if (z == 0)
			{
				gora = s.y;
				dol = s.y;
				prawo = s.x;
				lewo = s.x - s.dlugosc + 1;

				for (int i = lewo - 1; i <= prawo + 1; i++)   //bufor statku
					if (0 <= i && i < p.x)
						for (int j = gora - 1; j <= dol + 1; j++)
						{
							if (0 <= j && j < p.y)
							{
								p.tab[i][j] = '#';
							}

						}

				for (int i = 0; i < s.dlugosc; i++)
				{
					p.tab[s.x - i][s.y] = 48 + s.dlugosc;
				}

			}
			else
			{

				//	cout << endl << "Nie mozna wstawic statku w to miejsce case 4:" << endl;
				//	system("pause");
				return 2;
			}
			return 0;
			break;


		case 6:			//kierunek >
			if ((s.x + s.dlugosc + 1) <= p.x)
				for (int i = 0; i < s.dlugosc; i++)
				{
					if (p.tab[s.x + i][s.y] != ' ')
						z = 1;
				}
			else
				z = 1;

			if (z == 0)
			{
				gora = s.y;
				dol = s.y;
				prawo = s.x + s.dlugosc - 1;
				lewo = s.x;

				for (int i = lewo - 1; i <= prawo + 1; i++)   //bufor statku
					if (0 <= i && i < p.x)
						for (int j = gora - 1; j <= dol + 1; j++)
						{
							if (0 <= j && j < p.y)
							{
								p.tab[i][j] = '#';
							}

						}


				for (int i = 0; i < s.dlugosc; i++)
				{
					p.tab[s.x + i][s.y] = 48 + s.dlugosc;
				}
			}
			else
			{

				//	cout << endl << "Nie mozna wstawic statku w to miejsce case 6:" << endl;
				//	system("pause");
				return 2;
			}
			return 0;
			break;


		case 8:
			if ((s.y - s.dlugosc) + 1 >= 0)
				for (int i = 0; i < s.dlugosc; i++)
				{
					if (p.tab[s.x][s.y - i] != ' ')
						z = 1;
				}
			else
				z = 1;

			if (z == 0)		//kierunek ^
			{
				gora = s.y - s.dlugosc + 1;
				dol = s.y;
				prawo = s.x;
				lewo = s.x;

				for (int i = lewo - 1; i <= prawo + 1; i++)   //bufor statku
					if (0 <= i && i < p.x)
						for (int j = gora - 1; j <= dol + 1; j++)
						{
							if (0 <= j && j < p.y)
							{
								p.tab[i][j] = '#';
							}

						}


				for (int i = 0; i < s.dlugosc; i++)
				{
					p.tab[s.x][s.y - i] = 48 + s.dlugosc;
				}
			}
			else
			{

				//	cout << endl << "Nie mozna wstawic statku w to miejsce case 8:" << endl;
				//	system("pause");
				return 2;
			}
			return 0;
			break;



		case 1:
			if ((s.x - s.dlugosc + 1) >= 0 && (s.y + s.dlugosc) < p.y)
				for (int i = 0; i < s.dlugosc; i++)
				{
					if (p.tab[s.x - i][s.y + i] != ' ')
						z = 1;
				}
			else
				z = 1;

			if (z == 0)		//kierunek ^
			{
				gora = s.y;
				dol = s.y + s.dlugosc - 1;
				prawo = s.x;
				lewo = s.x - s.dlugosc + 1;

				for (int i = 0; i < s.dlugosc; i++)   //bufor statku
					for (int j = lewo - 1; j <= lewo + 1; j++)
						for (int k = dol - 1; k <= dol + 1; k++)
							if (0 <= j + i && j + i < p.x)
								if (0 <= k - i && k - i < p.y)
									p.tab[j + i][k - i] = '#';


				for (int i = 0; i < s.dlugosc; i++)
				{
					p.tab[s.x - i][s.y + i] = 48 + s.dlugosc;
				}
			}
			else
			{

				//	cout << endl << "Nie mozna wstawic statku w to miejsce case 1:" << endl;
				//	system("pause");
				return 2;
			}
			return 0;
			break;


		case 3:
			if ((s.x + s.dlugosc) < p.x && (s.y + s.dlugosc) < p.y)
				for (int i = 0; i < s.dlugosc; i++)
				{
					if (p.tab[s.x + i][s.y + i] != ' ')
						z = 1;
				}
			else
				z = 1;

			if (z == 0)		//kierunek ^
			{
				gora = s.y;
				dol = s.y + s.dlugosc;
				prawo = s.x + s.dlugosc;
				lewo = s.x;

				for (int i = 0; i < s.dlugosc; i++)   //bufor statku
					for (int j = lewo - 1; j <= lewo + 1; j++)
						for (int k = gora - 1; k <= gora + 1; k++)
							if (0 <= j + i && j + i < p.x)
								if (0 <= k + i && k + i < p.y)
									p.tab[j + i][k + i] = '#';


				for (int i = 0; i < s.dlugosc; i++)
				{
					p.tab[s.x + i][s.y + i] = 48 + s.dlugosc;
				}
			}
			else
			{

				//	cout << endl << "Nie mozna wstawic statku w to miejsce case 3:" << endl;
				//	system("pause");
				return 2;
			}
			return 0;
			break;


		case 7:
			if ((s.x - s.dlugosc + 1) > 0 && (s.y - s.dlugosc + 1) >= 0)
				for (int i = 0; i < s.dlugosc; i++)
				{
					if (p.tab[s.x - i][s.y - i] != ' ')
						z = 1;
				}
			else
				z = 1;

			if (z == 0)		//kierunek ^
			{
				gora = s.y - s.dlugosc + 1;
				dol = s.y;
				prawo = s.x;
				lewo = s.x - s.dlugosc + 1;

				for (int i = 0; i < s.dlugosc; i++)   //bufor statku
					for (int j = lewo - 1; j <= lewo + 1; j++)
						for (int k = gora - 1; k <= gora + 1; k++)
							if (0 <= j + i && j + i < p.x)
								if (0 <= k + i && k + i < p.y)
									p.tab[j + i][k + i] = '#';


				for (int i = 0; i < s.dlugosc; i++)
				{
					p.tab[s.x - i][s.y - i] = 48 + s.dlugosc;
				}
			}
			else
			{

				//	cout << endl << "Nie mozna wstawic statku w to miejsce case 7:" << endl;
				//	system("pause");
				return 2;
			}
			return 0;
			break;

		case 9:
			if ((s.x + s.dlugosc) < p.x && (s.y - s.dlugosc + 1) >= 0)
				for (int i = 0; i < s.dlugosc; i++)
				{

					if (p.tab[s.x + i][s.y - i] != ' ')
						z = 1;
				}
			else
				z = 1;

			if (z == 0)		//kierunek ^
			{
				gora = s.y - s.dlugosc;
				dol = s.y;
				prawo = s.x + s.dlugosc;
				lewo = s.x;

				for (int i = 0; i < s.dlugosc; i++)   //bufor statku
					for (int j = lewo - 1; j <= lewo + 1; j++)
						for (int k = dol - 1; k <= dol + 1; k++)
							if (0 <= j + i && j + i < p.x)
								if (0 <= k - i && k - i < p.y)
									p.tab[j + i][k - i] = '#';


				for (int i = 0; i < s.dlugosc; i++)
				{
					p.tab[s.x + i][s.y - i] = 48 + s.dlugosc;
				}
			}
			else
			{

				//	cout << endl << "Nie mozna wstawic statku w to miejsce case 9:" << endl;
				//	system("pause");
				return 2;
			}
			return 0;
			break;

		default:
			cout << "default: " << endl;

			return 3;
			break;
		}
	}
	else
	{

		//	cout <<endl<< "Nie mozna wstawic statku w to miejsce tab = "<< p.tab[s.x][s.y] <<endl;
		//	system("pause");
		return 1;
	}


	return 0;
}

void ustaw(Board &p, Menu &m)
{
	int ile = 0;
	int x, y, k;

	for (int i = 2; i < 6; i++)
		ile += m.ship[i];

	Ship* ship = new Ship[ile];

	for (int i = 5; i > 1; i--)
	{
		for (int j = 0; j < m.ship[i]; j++)
		{
			do {
				x = rand() % p.x;
				y = rand() % p.y;
				k = rand() % 8 + 1;
				if (k > 4)
					k++;
				ship[j].load(x, y, i, k);
				//				system("cls");
				//				p.wypisz();
			} while (wstaw(p, ship[j]) > 0);
		}
	}

	//	cout << "statki rozstawione ;)" << endl;
	//	system("pause");

	delete[] ship;
}

int ustaw_gracz(Board &p, Menu &m)
{
	int ile = 0;
	char x_char;
	int x, y, k;
	int u;

	for (int i = 2; i < 6; i++)
		ile += m.ship[i];

	Ship* ship = new Ship[ile];

	for (int i = 5; i > 1; i--)
	{
		for (int j = 0; j < m.ship[i]; j++)
		{
			system("cls");
			p.wypisz();
			cout << endl << "podaj wspolrzedne statku o dlugosci " << i << endl;
			cout << "zostalo " << m.ship[i] - j << " statkow do ustawienia tej wielkosci" << endl;
			do {


				do {
					cout << "Podaj x (a do " << char(m.n + 96) << "): ";
					cin >> x_char;

					if (!cin.good())
					{
						cout << endl << "Podales zly znak" << endl;
						cout << endl << "wylaczam program :/" << endl;
						system("pause");
						return 5;
					}

					if (x_char<'a' || x_char>char(m.n + 96))
					{
						cout << endl << "to nie jest znak z przedzialu od a do " << char(m.n + 96) << endl;
					}

				} while (x_char<'a' || x_char>char(m.n + 96));

				x = (int)x_char - 97;

				cout << "Podaj y (0 do " << m.n << "): ";
				do {
					cin >> y;

					if (!cin.good())
					{
						cout << endl << "Podales zly znak" << endl;
						cout << endl << "wylaczam program :/" << endl;
						system("pause");
						return 5;
					}

					if (y<0 || y>m.n)
					{
						cout << endl << "Podales zla liczbe" << endl;
					}

				} while (y<0 || y>m.n);


				cout << "Podaj kierunek ( 1,2,3,4,6,7,8,9 ): ";
				do {
					cin >> k;

					if (!cin.good())
					{
						cout << endl << "Podales zly znak" << endl;
						cout << endl << "wylaczam program :/" << endl;
						system("pause");
						return 5;
					}

					if (k < 1 || k>9 || k == 5)
					{
						cout << endl << "Podales zla liczbe" << endl;
					}

				} while (k < 1 || k>9 || k == 5);


				cout << endl << "x = " << x << "  y = " << y << "  i = " << i << "  k = " << k << endl;

				ship[j].load(x, y, i, k);

				u = wstaw(p, ship[j]);

				if (u > 0)
				{
					cout << "Nie udalo sie umiescic statku w tym miejscu" << endl;
					system("pause");
				}


			} while (u > 0);
		}
	}

	//	cout << "statki rozstawione ;)" << endl;
	//	system("pause");

	delete[] ship;

	return 0;
}

int strzal(Board &p1, int x, int y, Board &p2)
{
	char znak = p1.tab[x][y];

	switch (znak)
	{
	case '1':
		p1.tab[x][y] = 'X';
		p2.tab[x][y] = '1';
		return 1;
		break;
	case '2':
		p1.tab[x][y] = 'X';
		p2.tab[x][y] = '2';
		return 1;
		break;
	case '3':
		p1.tab[x][y] = 'X';
		p2.tab[x][y] = '3';
		return 1;
		break;
	case '4':
		p1.tab[x][y] = 'X';
		p2.tab[x][y] = '4';
		return 1;
		break;
	case '5':
		p1.tab[x][y] = 'X';
		p2.tab[x][y] = '5';
		return 1;
		break;
	case ' ':
		p1.tab[x][y] = 'X';
		p2.tab[x][y] = 'X';
		return 0;
		break;
	case '#':
		p1.tab[x][y] = 'X';
		p2.tab[x][y] = 'X';
		return 0;
	case 'X':
		return 2;
		break;
	default:
		break;
	}

	return 0;
}


int main()
{
	srand((unsigned)time(NULL));
	Menu menu1;
	int wybor = 0;
	int wybor2 = 0;

	do {
		wybor = menu1.wyswietl();
		switch (wybor)
		{
		case 1:
			do
			{
				Board p1(menu1.get('m'), menu1.get('n'));
				Board p2(menu1.get('m'), menu1.get('n'));
				Board pp1(menu1.get('m'), menu1.get('n'));
				Board pp2(menu1.get('m'), menu1.get('n'));
				wybor2 = menu1.opcje();
				if (wybor2 == 5)
					return 0;

				switch (wybor2)								// GRA
				{
				case 1:										//Player vs Player

					int plx, ply, pls;
					char charplx;
					system("cls");				//Czy auto Player 1
					cout << "Player 1" << endl;
					cout << "Czy automatycznie rozstawic statki?" << endl;
					cout << "1 Tak" << endl;
					cout << "2 Nie" << endl;

					int pl1;

					do {
						cout << "Podaj liczbe ( 1 lub 2 ): ";
						cin >> pl1;

						if (!cin.good())
						{
							cout << endl << "Podales zly znak" << endl;
							cout << endl << "wylaczam program :/" << endl;
							system("pause");
							return 0;
						}

						if (pl1 < 1 || pl1 > 2)
						{
							cout << endl << "Podales zla liczbe" << endl;
						}

					} while (pl1 < 1 || pl1 > 2);

					if (pl1 == 1)
					{
						system("cls");
						ustaw(p1, menu1);
						cout << "Statki zostaly rozstawione automatycznie" << endl << endl;
					}
					else
					{
						system("cls");
						ustaw_gracz(p1, menu1);
						system("cls");
						cout << "Statki zostaly rozstawione";
					}
					system("pause");

					system("cls");
					cout << "Tura Player 2" << endl << endl;
					system("pause");

					system("cls");
					cout << "Player 2" << endl;
					cout << "Czy automatycznie rozstawic statki?" << endl;
					cout << "1 Tak" << endl;
					cout << "2 Nie" << endl;

					int pl2;

					do {
						cout << "Podaj liczbe ( 1 lub 2 ): ";
						cin >> pl2;

						if (!cin.good())
						{
							cout << endl << "Podales zly znak" << endl;
							cout << endl << "wylaczam program :/" << endl;
							system("pause");
							return 0;
						}

						if (pl2 < 1 || pl2 > 2)
						{
							cout << endl << "Podales zla liczbe" << endl;
						}

					} while (pl2 < 1 || pl2 > 2);

					if (pl2 == 1)
					{
						system("cls");
						ustaw(p2, menu1);
						cout << "Statki zostaly rozstawione automatycznie" << endl << endl;
					}
					else
					{
						system("cls");
						ustaw_gracz(p2, menu1);
						system("cls");
						cout << "Statki zostaly rozstawione" << endl << endl;
					}
					system("pause");


					while (p1.czy_brak_statkow() != 1 && p2.czy_brak_statkow() != 1) //Rozpoczecie gry Player vs Player
					{
						system("cls");												//Tura Player 1
						cout << "Tura Player 1" << endl << endl;
						system("pause");



						do
						{
							system("cls");
							cout << "Player 1" << endl;
							p1.wypisz();
							cout << endl << endl;
							pp1.wypisz();

							cout << endl << "Podaj wspolrzedne strzalu" << endl;

							do {					//Player 1 stral_x
								cout << "Podaj x (od a do " << (char)(menu1.get('m') + 96) << "): ";
								cin >> charplx;
								plx = charplx - 97;


								if (!cin.good())
								{
									cout << endl << "Podales zly znak" << endl;
									cout << endl << "wylaczam program :/" << endl;
									system("pause");
									return 0;
								}

								if (plx < 0 || plx > menu1.get('m') - 1)
								{
									cout << endl << "Podales zly znak " << plx << menu1.get('m') << endl;
								}

							} while (plx < 0 || plx > menu1.get('m') - 1);

							do {				//Player 1 strzal_y
								cout << "Podaj y (od 0 do " << menu1.get('n') - 1 << "): ";
								cin >> ply;

								if (!cin.good())
								{
									cout << endl << "Podales zly znak" << endl;
									cout << endl << "wylaczam program :/" << endl;
									system("pause");
									return 0;
								}

								if (ply < 0 || ply > menu1.get('n') - 1)
								{
									cout << endl << "Podales zla liczbe" << endl;
									system("pause");
								}

							} while (ply < 0 || ply > menu1.get('n') - 1);

							pls = strzal(p2, plx, ply, pp1);

							if (pls == 2)
							{
								cout << endl << "Strzelales juz w to miejsce" << endl;
								system("pause");
							}

						} while (pls == 1 || pls == 2);

						system("cls");
						cout << "Player 1" << endl;
						p1.wypisz();
						cout << endl << endl;
						pp1.wypisz();

						cout << endl << endl << "Koniec tury Player 1" << endl << endl;
						system("pause");

						if (p2.czy_brak_statkow() == 0)
						{
							system("cls");												//Tura Player 2
							cout << "Tura Player 2" << endl << endl;
							system("pause");


							do
							{
								system("cls");
								cout << "Player 2" << endl;
								p2.wypisz();
								cout << endl << endl;
								pp2.wypisz();

								cout << endl << "Podaj wspolrzedne strzalu" << endl;

								do {					//Player 2 stral_x
									cout << "Podaj x (od a do " << (char)(menu1.get('m') + 96) << "): ";
									cin >> charplx;
									plx = charplx - 97;


									if (!cin.good())
									{
										cout << endl << "Podales zly znak" << endl;
										cout << endl << "wylaczam program :/" << endl;
										system("pause");
										return 0;
									}

									if (plx < 0 || plx > menu1.get('m') - 1)
									{
										cout << endl << "Podales zly znak " << plx << menu1.get('m') << endl;
									}

								} while (plx < 0 || plx > menu1.get('m') - 1);

								do {				//Player 2 strzal_y
									cout << "Podaj y (od 0 do " << menu1.get('n') - 1 << "): ";
									cin >> ply;

									if (!cin.good())
									{
										cout << endl << "Podales zly znak" << endl;
										cout << endl << "wylaczam program :/" << endl;
										system("pause");
										return 0;
									}

									if (ply<0 || ply>menu1.get('n') - 1)
									{
										cout << endl << "Podales zla liczbe" << endl;
									}

								} while (ply<0 || ply>menu1.get('n') - 1);

								pls = strzal(p1, plx, ply, pp2);

								if (pls == 2)
								{
									cout << endl << "Strzelales juz w to miejsce" << endl;
									system("pause");
								}

							} while (pls == 1 || pls == 2);

							system("cls");
							cout << "Player 2" << endl;
							p2.wypisz();
							cout << endl << endl;
							pp2.wypisz();

							cout << endl << endl << "Koniec tury Player 2" << endl << endl;
							system("pause");

						}

					}

					if (p1.czy_brak_statkow() == 1)
					{
						system("cls");
						cout << "Wygral Player 2" << endl;
						system("pause");
					}
					else
						if (p2.czy_brak_statkow() == 1)
						{
							system("cls");
							cout << "Wygral Player 1" << endl;
							system("pause");
						}


					break;									//Koniec gry Player vs Player

				case 2:										//Player vs PC

					int plpcx, plpcy, plpcs;
					char charplpcx;
					system("cls");
					cout << "Player 1" << endl;
					cout << "Czy automatycznie rozstawic statki?" << endl;
					cout << "1 Tak" << endl;
					cout << "2 Nie" << endl;

					int plpc1;

					do {
						cout << "Podaj liczbe ( 1 lub 2 ): ";
						cin >> plpc1;

						if (!cin.good())
						{
							cout << endl << "Podales zly znak" << endl;
							cout << endl << "wylaczam program :/" << endl;
							system("pause");
							return 0;
						}

						if (plpc1 < 1 || plpc1 > 2)
						{
							cout << endl << "Podales zla liczbe" << endl;
						}

					} while (plpc1 < 1 || plpc1 > 2);

					if (plpc1 == 1)
					{
						system("cls");
						ustaw(p1, menu1);
						cout << "Statki zostaly rozstawione automatycznie" << endl << endl;
					}
					else
					{
						system("cls");
						ustaw_gracz(p1, menu1);
						system("cls");
						cout << "Statki zostaly rozstawione";
					}
					system("pause");


					ustaw(p2, menu1);

					while (p1.czy_brak_statkow() != 1 && p2.czy_brak_statkow() != 1) //Rozpoczecie gry Player vs PC
					{

						system("cls");												//Tura Player 1
						cout << "Tura Player 1" << endl << endl;
						system("pause");

						do
						{
							system("cls");
							cout << "Player 1 " << endl;
							p1.wypisz();
							cout << endl << endl;
							if (menu1.get('c') == 0)
								pp1.wypisz();
							else
								p2.wypisz();

							cout << endl << "Podaj wspolrzedne strzalu" << endl;

							do {					//Player 1 stral_x
								cout << "Podaj x (od a do " << (char)(menu1.get('m') + 96) << "): ";
								cin >> charplpcx;
								plpcx = charplpcx - 97;


								if (!cin.good())
								{
									cout << endl << "Podales zly znak" << endl;
									cout << endl << "wylaczam program :/" << endl;
									system("pause");
									return 0;
								}

								if (plpcx < 0 || plpcx > menu1.get('m') - 1)
								{
									cout << endl << "Podales zly znak " << plpcx << menu1.get('m') << endl;
								}

							} while (plpcx < 0 || plpcx > menu1.get('m') - 1);

							do {				//Player 1 strzal_y
								cout << "Podaj y (od 0 do " << menu1.get('n') - 1 << "): ";
								cin >> plpcy;

								if (!cin.good())
								{
									cout << endl << "Podales zly znak" << endl;
									cout << endl << "wylaczam program :/" << endl;
									system("pause");
									return 0;
								}

								if (plpcy < 0 || plpcy > menu1.get('n') - 1)
								{
									cout << endl << "Podales zla liczbe" << endl;
									system("pause");
								}

							} while (plpcy < 0 || plpcy > menu1.get('n') - 1);

							plpcs = strzal(p2, plpcx, plpcy, pp1);

							if (plpcs == 2)
							{
								cout << endl << "Strzelales juz w to miejsce" << endl;
								system("pause");
							}

						} while (plpcs == 1 || plpcs == 2);

						system("cls");
						cout << "Player 1" << endl;
						p1.wypisz();
						cout << endl << endl;
						if (menu1.get('c') == 0)
							pp1.wypisz();
						else
							p2.wypisz();


						cout << endl << endl << "Koniec tury Player 1" << endl << endl;
						system("pause");


						system("cls");												//Tura PC2
						cout << "Tura PC 2" << endl << endl;
						system("pause");


						if (p2.czy_brak_statkow() == 0)					//tura komputera
						{
							/*system("cls");
							cout << "PC 2" << endl;
							p2.wypisz();
							cout << endl << endl;
							pp2.wypisz();

							cout << endl << endl;
							system("pause");
							*/
							while (strzal(p1, p1.random('x'), p1.random('y'), pp2) == 1 || strzal(p2, p2.random('x'), p2.random('y'), pp1) == 2);
							/*
							system("cls");
							cout << "PC 2" << endl;
							p2.wypisz();
							cout << endl << endl;
							pp2.wypisz();

							cout << endl << endl;
							system("pause");*/
						}




					}

					if (p1.czy_brak_statkow() == 1)
					{
						system("cls");
						cout << "Wygral PC 2" << endl;
						system("pause");
					}
					else
						if (p2.czy_brak_statkow() == 1)
						{
							system("cls");
							cout << "Wygral Player 1" << endl;
							system("pause");
						}

					break;									//Koniec gry Player vs PC

				case 3:										//PC vs PC
					ustaw(p1, menu1);
					ustaw(p2, menu1);

					while (p1.czy_brak_statkow() != 1 && p2.czy_brak_statkow() != 1)
					{

						while (strzal(p2, p2.random('x'), p2.random('y'), pp1) == 1 || strzal(p2, p2.random('x'), p2.random('y'), pp1) == 2);

						system("cls");
						cout << "PC 1" << endl;
						p1.wypisz();
						cout << endl << endl;
						pp1.wypisz();

						system("pause");

						if (p2.czy_brak_statkow() == 0)
						{
							while (strzal(p1, p1.random('x'), p1.random('y'), pp2) == 1 || strzal(p2, p2.random('x'), p2.random('y'), pp1) == 2);

							system("cls");
							cout << "PC 2" << endl;
							p2.wypisz();
							cout << endl << endl;
							pp2.wypisz();

							system("pause");
						}

					}

					if (p1.czy_brak_statkow() == 1)
					{
						system("cls");
						cout << "Wygral PC 2" << endl;
						system("pause");
					}
					else
						if (p2.czy_brak_statkow() == 1)
						{
							system("cls");
							cout << "Wygral PC 1" << endl;
							system("pause");
						}

					break;									//Koniec gry PC vs  PC
				default:
					break;
				}											//Koniec GRY
			} while (wybor2 != 4);
			break;
		case 2:
			do
			{
				wybor2 = menu1.opcje();
				if (wybor2 == 5)
					return 0;
				if (wybor2 != 4)
					if (menu1.ustawienia() == 5)
						return 0;

			} while (wybor2 != 4);
			break;
		case 3:
			do
			{
				wybor2 = menu1.opcje();
				if (wybor2 == 5)
					return 0;
			} while (wybor2 != 4);
			break;

		default:
			return 0;
			break;
		}
	} while (wybor != 4);

	cout << "exit" << endl;
	system("pause");
	return 0;
}

