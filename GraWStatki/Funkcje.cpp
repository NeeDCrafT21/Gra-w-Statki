#include "Funkcje.h"
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

void statki::zapelnianie_planszy()
{
	char znak_miejsca1 = '1';
	char znak_miejsca2 = '0';
	string temp1, temp2;
	plansza[0][0] = "  ";
	for (int i = 1; i <= 30; i++) {
		if (i < 10) {
			temp1 = znak_miejsca1;
			plansza[i][0] = ' ' + temp1;
			znak_miejsca1++;
		}
		else {
			if (znak_miejsca1 == ('9' + 1)) {
				znak_miejsca1 = '0';
				znak_miejsca2++;
			}
			temp1 = znak_miejsca1;
			temp2 = znak_miejsca2;
			plansza[i][0] = temp2 + temp1;
			znak_miejsca1++;
		}
	}

	znak_miejsca1 = 'A';
	znak_miejsca2 = 'A' - 1;
	for (int i = 1; i <= 30; i++) {
		if (i <= 26) {
			temp1 = znak_miejsca1;
			plansza[0][i] = ' ' + temp1;
			znak_miejsca1++;
		}
		else {
			if (znak_miejsca1 == ('Z' + 1)) {
				znak_miejsca1 = 'A';
				znak_miejsca2++;
			}
			temp1 = znak_miejsca1;
			temp2 = znak_miejsca2;
			plansza[0][i] = temp2 + temp1;
			znak_miejsca1++;
		}
	}

	for (int i = 1; i < 31; i++) {
		for (int j = 1; j < 31; j++) {
			plansza[i][j] = " .";
		}
	}
}
void statki::wypisz_plansze()
{
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 31; j++) {
			cout << plansza[i][j];
		}
		cout << endl;
	}
}
void statki::wypisz_plansze1()
{
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 31; j++) {
			cout << plansza_gracza1[i][j];
		}
		cout << endl;
	}
}
void statki::wypisz_plansze2()
{
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 31; j++) {
			cout << plansza_gracza2[i][j];
		}
		cout << endl;
	}
}
void statki::ilosc_statkow()
{
	int ilosc;
	cout << "UWAGA: max 10 statkow kazdego rodzaju!" << endl;
	cout << "-------------------------------------" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "Ilosc " << i + 2 << "-masztowcow: ";
		cin >> ilosc;
		if (ilosc > 10 || ilosc < 0) {
			cout << "Nieprawidlowe dane" << endl;
			return;
		}
		statki[i] = ilosc;
	}
}
void statki::zliczanie_punktow()
{
	punkty_gracza1 = 0;
	punkty_gracza2 = 0;
	for (int i = 0; i < 4; i++) {
		punkty_gracza1 = punkty_gracza1 + ((i + 2) * statki[i]);
		punkty_gracza2 = punkty_gracza2 + ((i + 2) * statki[i]);
	}
	//cout << punkty_gracza1 << ' ' << punkty_gracza2 << endl;
}
void statki::typ_rozgrywki()
{
	int tryb;
	cout << "UWAGA: domyslny tryb to PvP" << endl;
	cout << "---------------------------" << endl;
	cout << "1. gra dla 2 osob (PvP)" << endl;
	cout << "2. gra 1 osoba z komputerem (PvPC)" << endl;
	cout << "3. gra komputera z komputerem (PCvPC)" << endl;
	cout << "Opcja: ";
	cin >> tryb;
	if (tryb > 3 || tryb < 1) {
		cout << "Nieprawidlowe dane" << endl;
		return;
	}
	tryb_gry = tryb;
}
int statki::czy_statek_do_tab(string pozycja, int statek)
{
	int statek_curr = statek + 2;
	int litery, liczby;
	char kierunek;
	if (pozycja[0] >= 'A' && pozycja[0] <= 'Z' && pozycja[1] >= '0' && pozycja[1] <= '9') {
		litery = pozycja[0] - 64;
		if (pozycja[1] >= '0' && pozycja[1] <= '9' && (pozycja[2] < '0' || pozycja[2] > '9')) {
			liczby = pozycja[1] - 48;
			kierunek = pozycja[2];
		}
		else {
			liczby = (pozycja[1] - 48) * 10 + pozycja[2] - 48;
			kierunek = pozycja[3];
		}
	}
	else {
		litery = 26 + pozycja[1] - 64;
		if (pozycja[2] >= '0' && pozycja[2] <= '9' && (pozycja[3] < '0' || pozycja[3] > '9')) {
			liczby = pozycja[2] - 48;
			kierunek = pozycja[3];
		}
		else {
			liczby = (pozycja[2] - 48) * 10 + pozycja[3] - 48;
			kierunek = pozycja[4];
		}
	}
	//cout << litery << ' ' << liczby << ' ' << kierunek << endl;
	char plansza_temp[32][32];
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if (i == 0 || j == 0 || i == 31 || j == 31)
				plansza_temp[i][j] = 'a';
			else
				plansza_temp[i][j] = plansza[i][j][1];
		}
	}
	if (kierunek == '^') {
		for (int i = 0; i < statek_curr; i++) {
			if (plansza_temp[liczby][litery] == '.') {
				plansza_temp[liczby][litery] = '0' + statek_curr;
				liczby++;
			}
			else
				return 1;
		}
		for (int i = 0; i < statek_curr; i++) {
			if (i == 0) {
				//cout << liczby << endl;
				if ((plansza_temp[liczby][litery] == '.' || plansza_temp[liczby][litery] == 'a') && (plansza_temp[liczby][litery + 1] == '.' || plansza_temp[liczby][litery + 1] == 'a') && (plansza_temp[liczby - 1][litery + 1] == '.' || plansza_temp[liczby - 1][litery + 1] == 'a') && (plansza_temp[liczby][litery - 1] == '.' || plansza_temp[liczby][litery - 1] == 'a') && (plansza_temp[liczby - 1][litery - 1] == '.' || plansza_temp[liczby - 1][litery - 1] == 'a')) {
					//plansza_temp[liczby][litery] = plansza_temp[liczby][litery + 1] = plansza_temp[liczby-1][litery + 1] = plansza_temp[liczby][litery - 1] = plansza_temp[liczby-1][litery - 1] = 'o';
					liczby -= 2;
				}
				else {
					return 1;
				}

			}
			else if (i == statek_curr - 1) {
				if ((plansza_temp[liczby - 1][litery] == '.' || plansza_temp[liczby - 1][litery] == 'a') && (plansza_temp[liczby - 1][litery + 1] == '.' || plansza_temp[liczby - 1][litery + 1] == 'a') && (plansza_temp[liczby - 1][litery - 1] == '.' || plansza_temp[liczby - 1][litery - 1] == 'a') && (plansza_temp[liczby][litery - 1] == '.' || plansza_temp[liczby][litery - 1] == 'a') && (plansza_temp[liczby][litery + 1] == '.' || plansza_temp[liczby][litery + 1] == 'a')) {
					//plansza_temp[liczby - 1][litery] = plansza_temp[liczby - 1][litery + 1] = plansza_temp[liczby - 1][litery - 1] = plansza_temp[liczby][litery - 1] = plansza_temp[liczby][litery + 1] = 'o';
				}
				else
					return 1;
			}

			else {
				if ((plansza_temp[liczby][litery + 1] == '.' || plansza_temp[liczby][litery + 1] == 'a') && (plansza_temp[liczby][litery - 1] == '.' || plansza_temp[liczby][litery - 1] == 'a')) {
					//plansza_temp[liczby][litery + 1] = plansza_temp[liczby][litery - 1] = 'o';
					liczby--;
				}
				else
					return 1;
			}
		}
	}
	if (kierunek == 'v') {
		for (int i = 0; i < statek_curr; i++) {
			if (plansza_temp[liczby][litery] == '.') {
				plansza_temp[liczby][litery] = '0' + statek_curr;
				liczby--;
			}
			else
				return 1;
		}
		for (int i = 0; i < statek_curr; i++) {
			if (i == 0) {
				//cout << liczby << endl;
				if ((plansza_temp[liczby][litery] == '.' || plansza_temp[liczby][litery] == 'a') && (plansza_temp[liczby][litery + 1] == '.' || plansza_temp[liczby][litery + 1] == 'a') && (plansza_temp[liczby + 1][litery + 1] == '.' || plansza_temp[liczby + 1][litery + 1] == 'a') && (plansza_temp[liczby][litery - 1] == '.' || plansza_temp[liczby][litery - 1] == 'a') && (plansza_temp[liczby + 1][litery - 1] == '.' || plansza_temp[liczby + 1][litery - 1] == 'a')) {
					//plansza_temp[liczby][litery] = plansza_temp[liczby][litery + 1] = plansza_temp[liczby+1][litery + 1] = plansza_temp[liczby][litery - 1] = plansza_temp[liczby+1][litery - 1] = 'o';
					liczby += 2;
				}
				else {
					return 1;
				}

			}
			else if (i == statek_curr - 1) {
				if ((plansza_temp[liczby + 1][litery] == '.' || plansza_temp[liczby + 1][litery] == 'a') && (plansza_temp[liczby + 1][litery + 1] == '.' || plansza_temp[liczby + 1][litery + 1] == 'a') && (plansza_temp[liczby + 1][litery - 1] == '.' || plansza_temp[liczby + 1][litery - 1] == 'a') && (plansza_temp[liczby][litery - 1] == '.' || plansza_temp[liczby][litery - 1] == 'a') && (plansza_temp[liczby][litery + 1] == '.' || plansza_temp[liczby][litery + 1] == 'a')) {
					//plansza_temp[liczby + 1][litery] = plansza_temp[liczby + 1][litery + 1] = plansza_temp[liczby + 1][litery - 1] = plansza_temp[liczby][litery - 1] = plansza_temp[liczby][litery + 1] = 'o';
				}
				else
					return 1;
			}

			else {
				if ((plansza_temp[liczby][litery + 1] == '.' || plansza_temp[liczby][litery + 1] == 'a') && (plansza_temp[liczby][litery - 1] == '.' || plansza_temp[liczby][litery - 1] == 'a')) {
					//plansza_temp[liczby][litery + 1] = plansza_temp[liczby][litery - 1] = 'o';
					liczby++;
				}
				else
					return 1;
			}
		}
	}
	if (kierunek == '>') {
		for (int i = 0; i < statek_curr; i++) {
			if (plansza_temp[liczby][litery] == '.') {
				plansza_temp[liczby][litery] = '0' + statek_curr;
				litery--;
			}
			else
				return 1;
		}
		for (int i = 0; i < statek_curr; i++) {
			if (i == 0) {
				//cout << liczby << endl;
				if ((plansza_temp[liczby][litery] == '.' || plansza_temp[liczby][litery] == 'a') && (plansza_temp[liczby - 1][litery] == '.' || plansza_temp[liczby - 1][litery] == 'a') && (plansza_temp[liczby - 1][litery + 1] == '.' || plansza_temp[liczby - 1][litery + 1] == 'a') && (plansza_temp[liczby + 1][litery] == '.' || plansza_temp[liczby + 1][litery] == 'a') && (plansza_temp[liczby + 1][litery + 1] == '.' || plansza_temp[liczby + 1][litery + 1] == 'a')) {
					//plansza_temp[liczby][litery] = plansza_temp[liczby - 1][litery] = plansza_temp[liczby - 1][litery + 1] = plansza_temp[liczby + 1][litery] = plansza_temp[liczby + 1][litery + 1] = 'o';
					litery += 2;
				}
				else {
					return 1;
				}

			}
			else if (i == statek_curr - 1) {
				if ((plansza_temp[liczby][litery + 1] == '.' || plansza_temp[liczby][litery + 1] == 'a') && (plansza_temp[liczby - 1][litery + 1] == '.' || plansza_temp[liczby - 1][litery + 1] == 'a') && (plansza_temp[liczby - 1][litery] == '.' || plansza_temp[liczby - 1][litery] == 'a') && (plansza_temp[liczby + 1][litery + 1] == '.' || plansza_temp[liczby + 1][litery + 1] == 'a') && (plansza_temp[liczby + 1][litery] == '.' || plansza_temp[liczby + 1][litery] == 'a')) {
					//plansza_temp[liczby][litery + 1] = plansza_temp[liczby - 1][litery + 1] = plansza_temp[liczby - 1][litery] = plansza_temp[liczby + 1][litery + 1] = plansza_temp[liczby + 1][litery] = 'o';
				}
				else
					return 1;
			}

			else {
				if ((plansza_temp[liczby + 1][litery] == '.' || plansza_temp[liczby + 1][litery] == 'a') && (plansza_temp[liczby - 1][litery] == '.' || plansza_temp[liczby - 1][litery] == 'a')) {
					//plansza_temp[liczby + 1][litery] = plansza_temp[liczby - 1][litery] = 'o';
					litery++;
				}
				else
					return 1;
			}
		}
	}
	if (kierunek == '<') {
		for (int i = 0; i < statek_curr; i++) {
			if (plansza_temp[liczby][litery] == '.') {
				plansza_temp[liczby][litery] = '0' + statek_curr;
				litery++;
			}
			else
				return 1;
		}
		for (int i = 0; i < statek_curr; i++) {
			if (i == 0) {
				//cout << liczby << endl;
				if ((plansza_temp[liczby][litery] == '.' || plansza_temp[liczby][litery] == 'a') && (plansza_temp[liczby - 1][litery] == '.' || plansza_temp[liczby - 1][litery] == 'a') && (plansza_temp[liczby - 1][litery - 1] == '.' || plansza_temp[liczby - 1][litery - 1] == 'a') && (plansza_temp[liczby + 1][litery] == '.' || plansza_temp[liczby + 1][litery] == 'a') && (plansza_temp[liczby + 1][litery - 1] == '.' || plansza_temp[liczby + 1][litery - 1] == 'a')) {
					//plansza_temp[liczby][litery] = plansza_temp[liczby - 1][litery] = plansza_temp[liczby - 1][litery - 1] = plansza_temp[liczby + 1][litery] = plansza_temp[liczby + 1][litery - 1] = 'o';
					litery -= 2;
				}
				else {
					return 1;
				}

			}
			else if (i == statek_curr - 1) {
				if ((plansza_temp[liczby][litery - 1] == '.' || plansza_temp[liczby][litery - 1] == 'a') && (plansza_temp[liczby - 1][litery - 1] == '.' || plansza_temp[liczby - 1][litery - 1] == 'a') && (plansza_temp[liczby - 1][litery] == '.' || plansza_temp[liczby - 1][litery] == 'a') && (plansza_temp[liczby + 1][litery - 1] == '.' || plansza_temp[liczby + 1][litery - 1] == 'a') && (plansza_temp[liczby + 1][litery] == '.' || plansza_temp[liczby + 1][litery] == 'a')) {
					//plansza_temp[liczby][litery - 1] = plansza_temp[liczby - 1][litery - 1] = plansza_temp[liczby - 1][litery] = plansza_temp[liczby + 1][litery - 1] = plansza_temp[liczby + 1][litery] = 'o';
				}
				else
					return 1;
			}

			else {
				if ((plansza_temp[liczby + 1][litery] == '.' || plansza_temp[liczby + 1][litery] == 'a') && (plansza_temp[liczby - 1][litery] == '.' || plansza_temp[liczby - 1][litery] == 'a')) {
					//plansza_temp[liczby + 1][litery] = plansza_temp[liczby - 1][litery] = 'o';
					litery--;
				}
				else
					return 1;
			}
		}
	}
	string temp;
	for (int i = 1; i < 31; i++) {
		for (int j = 1; j < 31; j++) {
			temp = plansza_temp[i][j];
			plansza[i][j] = ' ' + temp;
		}
	}
	return 0;
}
string statki::wstawianie_statku_man(int gracz, string check_if_ready)
{
	string pozycja;
	for (int i = 0; i < 4; i++) {
		if (statki[i] > 0) {
			int j = 1;
			while (j <= statki[i]) {
				wypisz_plansze();
				cout << "Wstawianie " << j << ". statku " << i + 2 << "-masztowego" << endl;
				cout << "---------------------------------" << endl;
				cout << "kierunek wstawiania statku:\n^ - gora, v - dol, < - lewo, > - prawo" << endl;
				cout << "przykladowy format zapisu pozycji: A1^" << endl;
				cout << "--------------------------------------" << endl;
				cout << "Pozycja: ";
				cin >> pozycja;
				//cout << pozycja << endl;
				if (czy_statek_do_tab(pozycja, i) == 0)
					j++;
				else
					cout << "Nie mozna tu wstawic statku" << endl;
			}
		}
	}

	if (gracz == 1) {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 31; j++) {
				plansza_gracza1[i][j] = plansza[i][j];
			}
		}
		check_if_ready[0] = '1';
	}
	else if (gracz == 2) {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 31; j++) {
				plansza_gracza2[i][j] = plansza[i][j];
			}
		}
		check_if_ready[1] = '2';
	}
	return check_if_ready;
}
string statki::wstawianie_statku_aut(int gracz, string check_if_ready)
{
	srand(time(NULL));
	string pozycja;
	for (int i = 0; i < 4; i++) {
		if (statki[i] > 0) {
			int j = 1;
			while (j <= statki[i]) {
				string temp;
				int ilosc_liter = (rand() % 2) + 1;
				if (ilosc_liter == 1) {
					char litera = (rand() % 26) + 65;
					pozycja = litera;
				}
				else if (ilosc_liter == 2) {
					char litera1 = (rand() % 26) + 65;
					pozycja = litera1;
					char litera2 = (rand() % 4) + 65;
					temp = litera2;
					pozycja += temp;
				}
				char liczba1 = (rand() % 10) + 48;
				temp = liczba1;
				pozycja += temp;
				char liczba2 = (rand() % 10) + 48;
				temp = liczba2;
				pozycja += temp;
				char znak = '^';
				int ktory_znak = (rand() % 4) + 1;
				if (ktory_znak == 1)
					znak = '^';
				else if (ktory_znak == 2)
					znak = 'v';
				else if (ktory_znak == 3)
					znak = '<';
				else if (ktory_znak == 4)
					znak = '>';
				temp = znak;
				pozycja += temp;
				//cout << pozycja << endl;
				if (czy_statek_do_tab(pozycja, i) == 0)
					j++;
			}
		}
	}

	if (gracz == 1) {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 31; j++) {
				plansza_gracza1[i][j] = plansza[i][j];
			}
		}
		check_if_ready[0] = '1';
	}
	else if (gracz == 2) {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 31; j++) {
				plansza_gracza2[i][j] = plansza[i][j];
			}
		}
		check_if_ready[1] = '2';
	}
	return check_if_ready;
	//wypisz_plansze();
}
void statki::zakryj_plansze(int gracz)
{
	string plansza_temp[31][31];
	if (gracz == 1) {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 31; j++) {
				plansza_temp[i][j] = plansza_gracza1[i][j];
			}
		}
	}
	else if (gracz == 2) {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 31; j++) {
				plansza_temp[i][j] = plansza_gracza2[i][j];
			}
		}
	}
	for (int i = 1; i < 31; i++) {
		for (int j = 1; j < 31; j++) {
			if (plansza_temp[i][j] == " ." || plansza_temp[i][j] == " 2" || plansza_temp[i][j] == " 3" || plansza_temp[i][j] == " 4" || plansza_temp[i][j] == " 5")
				plansza_temp[i][j] = " *";
			else if (plansza_temp[i][j] == " O")
				plansza_temp[i][j] = " O";
			else if (plansza_temp[i][j] == " X")
				plansza_temp[i][j] = " X";
		}
	}
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 31; j++) {
			cout << plansza_temp[i][j];
		}
		cout << endl;
	}
}
void statki::strzal(int gracz)
{
	string pozycja;
	int litery, liczby, czy_dalej = 0;
	while (czy_dalej == 0) {
		cout << "Miejsce strzalu (np. A1): ";
		cin >> pozycja;

		if (pozycja[0] >= 'A' && pozycja[0] <= 'Z' && pozycja[1] >= '0' && pozycja[1] <= '9') {
			litery = pozycja[0] - 64;
			if (pozycja[1] >= '0' && pozycja[1] <= '9' && (pozycja[2] < '0' || pozycja[2] > '9')) {
				liczby = pozycja[1] - 48;
			}
			else {
				liczby = (pozycja[1] - 48) * 10 + pozycja[2] - 48;
			}
		}
		else {
			litery = 26 + pozycja[1] - 64;
			if (pozycja[2] >= '0' && pozycja[2] <= '9' && (pozycja[3] < '0' || pozycja[3] > '9')) {
				liczby = pozycja[2] - 48;
			}
			else {
				liczby = (pozycja[2] - 48) * 10 + pozycja[3] - 48;
			}
		}
		//cout << liczby << ' ' << litery << endl;
		if (gracz == 1) {
			if (plansza_gracza1[liczby][litery] == " 2" || plansza_gracza1[liczby][litery] == " 3" || plansza_gracza1[liczby][litery] == " 4" || plansza_gracza1[liczby][litery] == " 5") {
				plansza_gracza1[liczby][litery] = " X";
				punkty_gracza1--;
				czy_dalej = 1;
				//cout << punkty_gracza1 << endl;
			}
			else if (plansza_gracza1[liczby][litery] == " .") {
				plansza_gracza1[liczby][litery] = " O";
				czy_dalej = 1;
			}
			else
				cout << "To miejsce zostalo juz ostrzelane" << endl;
		}
		else if (gracz == 2) {
			if (plansza_gracza2[liczby][litery] == " 2" || plansza_gracza2[liczby][litery] == " 3" || plansza_gracza2[liczby][litery] == " 4" || plansza_gracza2[liczby][litery] == " 5") {
				plansza_gracza2[liczby][litery] = " X";
				punkty_gracza2--;
				czy_dalej = 1;
				//cout << punkty_gracza2 << endl;
			}
			else if (plansza_gracza2[liczby][litery] == " .") {
				plansza_gracza2[liczby][litery] = " O";
				czy_dalej = 1;
			}
			else
				cout << "To miejsce zostalo juz ostrzelane" << endl;
		}
	}

	zakryj_plansze(gracz);
}
void statki::strzal_aut(int gracz)
{
	srand(time(NULL));
	int litery, liczby, czy_dalej = 0;
	while (czy_dalej == 0) {
		if (gracz == 1) { //strzelanie do 1. gracza
			if (tryb_strzalu1 == 0) {
				litery = (rand() % 30) + 1;
				liczby = (rand() % 30) + 1;
			}
			else if (tryb_strzalu1 == 1) {
				litery = trafione_litery1;
				liczby = trafione_liczby1 + 1;
				if (liczby > 30)
					tryb_strzalu1 = 2;
			}
			else if (tryb_strzalu1 == 2) {
				litery = trafione_litery1 - 1;
				liczby = trafione_liczby1;
				if (litery < 1)
					tryb_strzalu1 = 3;
			}
			else if (tryb_strzalu1 == 3) {
				litery = trafione_litery1;
				liczby = trafione_liczby1 - 1;
				if (liczby < 1)
					tryb_strzalu1 = 4;
			}
			else if (tryb_strzalu1 == 4) {
				litery = trafione_litery1 + 1;
				liczby = trafione_liczby1;
			}
			else if (tryb_strzalu1 == 5) {
				litery = trafione_litery1;
				liczby = trafione_liczby1;
			}
			else if (tryb_strzalu1 == 6) {
				if (kierunek_strzalu1 == 1) {
					litery = trafione_litery_pocz1;
					liczby = trafione_liczby_pocz1--;
				}
				else if (kierunek_strzalu1 == 2) {
					litery = trafione_litery_pocz1++;
					liczby = trafione_liczby_pocz1;
				}
				else if (kierunek_strzalu1 == 3) {
					litery = trafione_litery_pocz1;
					liczby = trafione_liczby_pocz1++;
				}
				else if (kierunek_strzalu1 == 4) {
					litery = trafione_litery_pocz1--;
					liczby = trafione_liczby_pocz1;
				}
			}
			cout << liczby << ' ' << litery << ' ' << gracz << kierunek_strzalu1 << endl;
			if (plansza_gracza1[liczby][litery] == " 2" || plansza_gracza1[liczby][litery] == " 3" || plansza_gracza1[liczby][litery] == " 4" || plansza_gracza1[liczby][litery] == " 5") {
				plansza_gracza1[liczby][litery] = " X";
				punkty_gracza1--;
				czy_dalej = 1;
				if (tryb_strzalu1 == 0) {
					tryb_strzalu1 = 1;
					trafione_liczby1 = liczby;
					trafione_liczby_pocz1 = liczby;
					trafione_litery1 = litery;
					trafione_litery_pocz1 = litery;
				}
				else if (tryb_strzalu1 == 1 || tryb_strzalu1 == 2 || tryb_strzalu1 == 3 || tryb_strzalu1 == 4) {
					kierunek_strzalu1 = tryb_strzalu1;
					tryb_strzalu1 = 5;
					trafione_liczby1 = liczby;
					trafione_litery1 = litery;
				}
				if (tryb_strzalu1 == 5) {
					if (kierunek_strzalu1 == 1) {
						trafione_liczby1++;
						if (trafione_liczby1 > 30)
							tryb_strzalu1 = 6;
					}
					else if (kierunek_strzalu1 == 2) {
						trafione_litery1--;
						if (trafione_litery1 < 1)
							tryb_strzalu1 = 6;
					}
					else if (kierunek_strzalu1 == 3) {
						trafione_liczby1--;
						if (trafione_liczby1 < 1)
							tryb_strzalu1 = 6;
					}
					else if (kierunek_strzalu1 == 4) {
						trafione_litery1++;
						if (trafione_litery1 > 30)
							tryb_strzalu1 = 6;
					}
				}
				if (tryb_strzalu1 == 6) {
					trafione_liczby_pocz1 = liczby;
					trafione_litery_pocz1 = litery;
				}
			}
			else if (plansza_gracza1[liczby][litery] == " .") {
				plansza_gracza1[liczby][litery] = " O";
				czy_dalej = 1;
				if (tryb_strzalu1 == 1 || tryb_strzalu1 == 2 || tryb_strzalu1 == 3 || tryb_strzalu1 == 4) {
					tryb_strzalu1++;
				}
				else if (tryb_strzalu1 == 5) {
					tryb_strzalu1 = 6;
				}
				else if (tryb_strzalu1 == 6) {
					tryb_strzalu1 = 0;
				}
			}
			else if (plansza_gracza1[liczby][litery] == " O") {
				if (tryb_strzalu1 == 1)
					tryb_strzalu1 = 2;
				else if (tryb_strzalu1 == 2)
					tryb_strzalu1 = 3;
				else if (tryb_strzalu1 == 3)
					tryb_strzalu1 = 4;
				else if (tryb_strzalu1 == 5)
					tryb_strzalu1 = 6;
				else if (tryb_strzalu1 == 6)
					tryb_strzalu1 = 0;
			}
		}
		else if (gracz == 2) { //strzelanie do 2. gracza
			if (tryb_strzalu2 == 0) {
				litery = (rand() % 30) + 1;
				liczby = (rand() % 30) + 1;
			}
			else if (tryb_strzalu2 == 1) {
				litery = trafione_litery2;
				liczby = trafione_liczby2 + 1;
				if (liczby > 30)
					tryb_strzalu2 = 2;
			}
			else if (tryb_strzalu2 == 2) {
				litery = trafione_litery2 - 1;
				liczby = trafione_liczby2;
				if (litery < 1)
					tryb_strzalu2 = 3;
			}
			else if (tryb_strzalu2 == 3) {
				litery = trafione_litery2;
				liczby = trafione_liczby2 - 1;
				if (liczby < 1)
					tryb_strzalu2 = 4;
			}
			else if (tryb_strzalu2 == 4) {
				litery = trafione_litery2 + 1;
				liczby = trafione_liczby2;
			}
			else if (tryb_strzalu2 == 5) {
				litery = trafione_litery2;
				liczby = trafione_liczby2;
			}
			else if (tryb_strzalu2 == 6) {
				if (kierunek_strzalu2 == 1) {
					litery = trafione_litery_pocz2;
					liczby = trafione_liczby_pocz2--;
				}
				else if (kierunek_strzalu2 == 2) {
					litery = trafione_litery_pocz2++;
					liczby = trafione_liczby_pocz2;
				}
				else if (kierunek_strzalu2 == 3) {
					litery = trafione_litery_pocz2;
					liczby = trafione_liczby_pocz2++;
				}
				else if (kierunek_strzalu2 == 4) {
					litery = trafione_litery_pocz2--;
					liczby = trafione_liczby_pocz2;
				}
			}
			cout << liczby << ' ' << litery << ' ' << gracz << kierunek_strzalu2 << endl;
			if (plansza_gracza2[liczby][litery] == " 2" || plansza_gracza2[liczby][litery] == " 3" || plansza_gracza2[liczby][litery] == " 4" || plansza_gracza2[liczby][litery] == " 5") {
				plansza_gracza2[liczby][litery] = " X";
				punkty_gracza2--;
				czy_dalej = 1;
				if (tryb_strzalu2 == 0) {
					tryb_strzalu2 = 1;
					trafione_liczby2 = liczby;
					trafione_liczby_pocz2 = liczby;
					trafione_litery2 = litery;
					trafione_litery_pocz2 = litery;
				}
				else if (tryb_strzalu2 == 1 || tryb_strzalu2 == 2 || tryb_strzalu2 == 3 || tryb_strzalu2 == 4) {
					kierunek_strzalu2 = tryb_strzalu2;
					tryb_strzalu2 = 5;
					trafione_liczby2 = liczby;
					trafione_litery2 = litery;
				}
				if (tryb_strzalu2 == 5) {
					if (kierunek_strzalu2 == 1) {
						trafione_liczby2++;
						if (trafione_liczby2 > 30)
							tryb_strzalu2 = 6;
					}
					else if (kierunek_strzalu2 == 2) {
						trafione_litery2--;
						if (trafione_litery2 < 1)
							tryb_strzalu2 = 6;
					}
					else if (kierunek_strzalu2 == 3) {
						trafione_liczby2--;
						if (trafione_liczby2 < 1)
							tryb_strzalu2 = 6;
					}
					else if (kierunek_strzalu2 == 4) {
						trafione_litery2++;
						if (trafione_litery2 > 30)
							tryb_strzalu2 = 6;
					}
				}
				if (tryb_strzalu2 == 6) {
					trafione_liczby_pocz2 = liczby;
					trafione_litery_pocz2 = litery;
				}
			}
			else if (plansza_gracza2[liczby][litery] == " .") {
				plansza_gracza2[liczby][litery] = " O";
				czy_dalej = 1;
				if (tryb_strzalu2 == 1 || tryb_strzalu2 == 2 || tryb_strzalu2 == 3 || tryb_strzalu2 == 4) {
					tryb_strzalu2++;
				}
				else if (tryb_strzalu2 == 5) {
					tryb_strzalu2 = 6;
				}
				else if (tryb_strzalu2 == 6) {
					tryb_strzalu2 = 0;
				}
			}
			else if (plansza_gracza2[liczby][litery] == " O") {
				if (tryb_strzalu2 == 1)
					tryb_strzalu2 = 2;
				else if (tryb_strzalu2 == 2)
					tryb_strzalu2 = 3;
				else if (tryb_strzalu2 == 3)
					tryb_strzalu2 = 4;
				else if (tryb_strzalu2 == 5)
					tryb_strzalu2 = 6;
				else if (tryb_strzalu2 == 6)
					tryb_strzalu2 = 0;
			}
		}
	}
}