#pragma once
#include <iostream>

using namespace std;

class statki
{
public:
	string plansza[31][31];
	string plansza_gracza1[31][31];
	string plansza_gracza2[31][31];
	int statki[4]; //0 - 2-masztowiec, 1 - 3-masztowiec, 2 - 4-masztowiec, 3 - 5-masztowiec
	int tryb_gry = 1, tryb_strzalu1 = 0, tryb_strzalu2 = 0;
	int punkty_gracza1, punkty_gracza2;
	int trafione_litery1, trafione_litery_pocz1, trafione_liczby1, trafione_liczby_pocz1, kierunek_strzalu1 = 0;
	int trafione_litery2, trafione_litery_pocz2, trafione_liczby2, trafione_liczby_pocz2, kierunek_strzalu2 = 0;
	void zapelnianie_planszy();
	void wypisz_plansze();
	void wypisz_plansze1();
	void wypisz_plansze2();
	void ilosc_statkow();
	void zliczanie_punktow();
	void typ_rozgrywki();
	int czy_statek_do_tab(string pozycja, int statek);
	string wstawianie_statku_man(int gracz, string check_if_ready);
	string wstawianie_statku_aut(int gracz, string check_if_ready);
	void zakryj_plansze(int gracz);
	void strzal(int gracz);
	void strzal_aut(int gracz);
};