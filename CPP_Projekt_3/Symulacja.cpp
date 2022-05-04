#include "Symulacja.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>

void Symulacja::zabez_1(int* _input) {
	while (std::cin.fail()) {
		std::cout << "Nieprawidlowe dane!\n";
		std::cin.clear();
		std::cin.ignore(200, '\n');
		std::cin >> *_input;
	}
}

void Symulacja::zabez_2(float* _input) {
	while (std::cin.fail()) {
		std::cout << "Nieprawidlowe dane!\n";
		std::cin.clear();
		std::cin.ignore(200, '\n');
		std::cin >> *_input;
	}
}

Symulacja::Symulacja(float _x, float _y, float _z, float _moc) 
:	pokoj(_x, _y, _z),
	grzej(_moc){
	std::cout << "Poczatek symulacji!";
}

void Symulacja::iteracja(float _probkowanie) {
	pokoj.aktualizuj(_probkowanie);
	reg_1->p.aktualizuj(_probkowanie);
	reg_2->p.aktualizuj(_probkowanie);
}

int Symulacja::wybor_regulacji() {
	int r;
	std::cout << "Ktorej regulacji chcesz uzyc?\n1.Regulacja bang_bang\n2.Regulacja PID\n";
	std::cin >> r;
	zabez_1(&r);

	if (r == 1 || r == 2) {
		return r;
	} else {
		throw -1;
	}
}

void Symulacja::przebieg(int _ile_razy, float _probkowanie) {
	float proc, proc_1, ciep, temp_zad = 0;
	int bramka = 0;
	float czas = 0;
	int k = 0, i = 0, w = 0, j = 1;

	try {
		w = wybor_regulacji();
	}
	catch (int blad) {
		std::cout << "Blad " << blad << std::endl;
		std::cout << "Niepoprawny wybor regulacji!\n";
	}

	if (w == 1) {
		std::cout << "Regulator bang bang:\n";
		std::cout << "Prosze podac temperature zadana:\n";
		std::cin >> temp_zad;
		zabez_2(&temp_zad);

		if (temp_zad < 19 || temp_zad > 300) {
			throw - 2;
		}
	}

	if (w == 2) {
		std::cout << "Regulator PID:\nJaka ma byc temperatura zadana?\n";
		std::cin >> temp_zad;
		zabez_2(&temp_zad);

		if (temp_zad < 19 || temp_zad > 300) {
			throw - 2;
		}
	}

	system("cls");
	for (i; i < _ile_razy; i++) {
		if (bramka == 0) {
			proc = 0.03 * k;
			grzej.ustaw_poziom(proc);
			k++;
		}

		if (grzej.podaj_poziom_mocy() >= 1 || bramka == 1) {
			bramka = 1;
			proc_1 = proc - (0.03 * j);
			grzej.ustaw_poziom(proc_1);
			j++;

			if (pokoj.getTemperatura() <= 19 || proc_1 < 0.03) {
				bramka = 0;
				k = 0;
				j = 0;
			}
		}

		if (w == 1) {
			uzyj_regulator_BB(temp_zad);
		}

		if (w == 2) {
			if (czas != 0) {
				try {
					uzyj_regulator_PID(_probkowanie, temp_zad);
				}
				catch(int blad) {
					std::cout << "Blad " << blad << "\n";
					std::cout << "Regulator wyszedl poza zakres!\n";
				}
			}
		}

		ciep = grzej.emitowane_cieplo(_probkowanie);
		pokoj.dodajCieplo(ciep);
		iteracja(_probkowanie);

		t.push_back(czas);
		q.push_back(grzej.podaj_poziom_mocy());
		temp.push_back(pokoj.getTemperatura());

		czas += _probkowanie;
	}
}

void Symulacja::zapis(int _ile_razy) {
	std::ofstream plik;
	plik.open("wykresy.csv", std::ios::out);
	std::locale pol("pl_PL");
	plik.imbue(pol);

	plik << "Czas;";
	plik << "Poziom mocy;";
	plik << "Temperatura;";
	plik << "\n";

	for (int i = 0; i < _ile_razy; i++) {
		plik << t[i] << ";";
		plik << q[i] << ";";
		plik << temp[i];
		plik << "\n";
	}

	plik.close();
}

void Symulacja::uzyj_regulator_BB(float _temp_zad) {
	float pelny, dt = 0;

	reg_1->ustaw_temp_zad(_temp_zad);
	reg_bb.steruj(reg_1->podaj_temp_zad(), dt, pokoj.getTemperatura());
	pelny = reg_bb.g.podaj_poziom_mocy();
	grzej.ustaw_poziom(pelny);
}

void Symulacja::uzyj_regulator_PID(float _dt, float _temp_zad) {
	float regulacja;

	reg_2->ustaw_temp_zad(_temp_zad);
	reg_pid.steruj(reg_2->podaj_temp_zad(), _dt, pokoj.getTemperatura());

	regulacja = reg_pid.g.podaj_poziom_mocy();

	if (regulacja > 1) {
		regulacja = 1;
	}

	if (regulacja <= 0) {
		throw -3;
	}

	grzej.ustaw_poziom(regulacja);
}

Regulator* Symulacja::dostep_do_reg_bb() {
	return reg_1;
}

Regulator* Symulacja::dostep_do_reg_pid() {
	return reg_2;
}