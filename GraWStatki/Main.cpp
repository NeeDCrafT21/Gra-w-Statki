#include "Funkcje.h"
#include <iostream>

using namespace std;

int main()
{
	statki ships;
	string check_if_ready = "gg";
	char opcja = 'a';
	int stan_menu = 0, gracz = 1;
	ships.zapelnianie_planszy();
	while (opcja != 'E') {
		if (stan_menu == 0) {
			cout << "Menu:" << endl;
			cout << "1. wybierz ilosc poszczegolnych statkow" << endl;
			cout << "2. wybierz typ rozgrywki" << endl;
			cout << "3. wybierz rozstawienie statkow" << endl;
			cout << "E. wyjdz z programu" << endl;
			cout << "Opcja: ";
			cin >> opcja;
			switch (opcja)
			{
			case '1':
				ships.ilosc_statkow();
				ships.zliczanie_punktow();
				break;
			case '2':
				ships.typ_rozgrywki();
				break;
			case '3':
				if (ships.statki[0] > 0 || ships.statki[1] > 0 || ships.statki[2] > 0 || ships.statki[3] > 0)
					stan_menu = 1;
				else
					cout << "Wprowadz ilosc statkow" << endl;
				break;
			default:
				break;
			}
		}
		else if (stan_menu == 1 || stan_menu == 2) {
			//cout << check_if_ready << endl;
			if (check_if_ready == "12")
				stan_menu = 2;
			cout << "Wybieranie dla " << gracz << ". gracza" << endl;
			cout << "------------------------" << endl;
			cout << "Menu:" << endl;
			cout << "1. wstaw statki manualnie" << endl;
			cout << "2. wstaw statki automatycznie" << endl;
			cout << "3. zmien gracza" << endl;
			if (stan_menu == 2)
				cout << "4. graj" << endl;
			cout << "Opcja: ";
			cin >> opcja;
			switch (opcja)
			{
			case '1':
				ships.zapelnianie_planszy();
				check_if_ready = ships.wstawianie_statku_man(gracz, check_if_ready);
				ships.wypisz_plansze();
				break;
			case '2':
				ships.zapelnianie_planszy();
				check_if_ready = ships.wstawianie_statku_aut(gracz, check_if_ready);
				ships.wypisz_plansze();
				break;
			case '3':
				int gracz_temp;
				cout << "Wybierz gracza 1/2: " << endl;
				cin >> gracz_temp;
				if (gracz_temp == 1 || gracz_temp == 2)
					gracz = gracz_temp;
				else
					cout << "Nie ma takiego gracza" << endl;
				break;
			case '4':
				if (stan_menu != 2)
					break;
				if (ships.tryb_gry == 1)
					stan_menu = 3;
				else if (ships.tryb_gry == 2)
					stan_menu = 4;
				else if (ships.tryb_gry == 3)
					stan_menu = 5;
				gracz = 2;
				break;
			default:
				break;
			}
		}
		else if (stan_menu == 3) { //tryb PvP
			//cout << "bruh" << endl;
			//cout << ships.punkty_gracza1 << ' ' << ships.punkty_gracza2 << endl;
			if (ships.punkty_gracza1 == 0) {
				gracz = 2;
				cout << "Wygrywa gracz " << gracz << ". !!!" << endl;
				return 0;
			}
			else if (ships.punkty_gracza2 == 0) {
				gracz = 1;
				cout << "Wygrywa gracz " << gracz << ". !!!" << endl;
				return 0;
			}
			if (gracz == 2 && ships.punkty_gracza1 != 0 && ships.punkty_gracza2 != 0) {
				ships.wypisz_plansze1();
				ships.zakryj_plansze(gracz);
				ships.strzal(gracz);
				gracz = 1;
				//ships.wypisz_plansze2();
			}
			else if (gracz == 1 && ships.punkty_gracza1 != 0 && ships.punkty_gracza2 != 0) {
				ships.wypisz_plansze2();
				ships.zakryj_plansze(gracz);
				ships.strzal(gracz);
				gracz = 2;
				//ships.wypisz_plansze1();
			}
		}
		else if (stan_menu == 4) { //tryb PvPC
			if (ships.punkty_gracza1 == 0) {
				gracz = 2;
				cout << "Wygrywa gracz " << gracz << ". !!!" << endl;
				return 0;
			}
			else if (ships.punkty_gracza2 == 0) {
				gracz = 1;
				cout << "Wygrywa gracz " << gracz << ". !!!" << endl;
				return 0;
			}
			if (gracz == 2 && ships.punkty_gracza1 != 0 && ships.punkty_gracza2 != 0) {
				ships.wypisz_plansze1();
				ships.zakryj_plansze(gracz);
				ships.strzal(gracz);
				gracz = 1;
			}
			else if (gracz == 1 && ships.punkty_gracza1 != 0 && ships.punkty_gracza2 != 0) {
				ships.strzal_aut(gracz);
				gracz = 2;
			}
		}
		else if (stan_menu == 5) { //tryb PCvPC
			if (ships.punkty_gracza1 == 0) {
				gracz = 2;
				cout << "Wygrywa gracz " << gracz << ". !!!" << endl;
				return 0;
			}
			else if (ships.punkty_gracza2 == 0) {
				gracz = 1;
				cout << "Wygrywa gracz " << gracz << ". !!!" << endl;
				return 0;
			}
			if (gracz == 2 && ships.punkty_gracza1 != 0 && ships.punkty_gracza2 != 0) {
				ships.wypisz_plansze1();
				ships.strzal_aut(gracz);
				gracz = 1;
			}
			else if (gracz == 1 && ships.punkty_gracza1 != 0 && ships.punkty_gracza2 != 0) {
				ships.wypisz_plansze2();
				ships.strzal_aut(gracz);
				gracz = 2;
			}
		}
	}
	return 0;
}