#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Pomieszczenie.h"
#include "Symulacja.h"

void zabezpieczenie_1(int* _input) {
	while (std::cin.fail()) {
		std::cout << "Nieprawidlowe dane!\n";
		std::cin.clear();
		std::cin.ignore(200, '\n');
		std::cin >> *_input;
	}
}

void zabezpieczenie_2(float* _input) {
	while (std::cin.fail()) {
		std::cout << "Nieprawidlowe dane!\n";
		std::cin.clear();
		std::cin.ignore(200, '\n');
		std::cin >> *_input;
	}
}

void menu(int* wybierz) {

	int wybor, dane;

	do
	{
		std::cout << "\nMenu uzytkownika: \n\n";
		std::cout << "1. Przeprowadz symulacje\n2. Zapis do csv\n3. Zakoncz";
		std::cout << "\n\n";

		while (scanf_s("%d", &wybor) != 1)
		{
			do {
				dane = wybor;
			} while ((dane = getchar()) != '\n' && dane != EOF);
			printf("Wprowadz poprawna liczbe!!!\n");
		}

		*wybierz = wybor;
	} while (wybor != 1 && wybor != 2 && wybor != 3);

}

int main() {
	int ile = 400, bl = 0, w = 0, bramka = 0;
	float moc, dt, x, y, z;


		std::cout << "Ustaw ilosc prob:\n";
		std::cin >> ile;
		zabezpieczenie_1(&ile);

		system("cls");
		std::cout << "Ustaw czas probkowania:\n";
		std::cin >> dt;
		zabezpieczenie_2(&dt);

		system("cls");
		std::cout << "Ustaw poczatkowe parametry:\n";
		std::cout << "Podaj wymiary pokoju (x, y, z):\n";
		std::cin >> x;
		zabezpieczenie_2(&x);
		std::cin >> y;
		zabezpieczenie_2(&y);
		std::cin >> z;
		zabezpieczenie_2(&z);
		
		std::cout << "\nUstal moc grzejnika:\n";
		std::cin >> moc;
		zabezpieczenie_2(&moc);

		Symulacja symul(x, y, z, moc);
		system("cls");

	while (w != 3) {

		menu(&w);

		switch(w) {
		case 1:
			try {
				symul.przebieg(ile, dt);
			}
			catch (int b) {
				std::cout << "Blad " << b << "\n";
				bl = b;
				std::cout << "Niepoprawna temperatura!\n";
			}
			bramka++;
			break;
		case 2:
			system("cls");

			if (bl != -2 && bramka > 0) {
				symul.zapis(ile);
				std::cout << "Zapis udany!\n";
			} else {
				std::cout << "Nie mozna wykonac zapisu bez symulacji!\n";
			}
			break;
		case 3:
			system("cls");

			std::cout << "Koniec programu!\n";
			return 0;
			break;
		}
	}
	
	return 0;
}