#pragma once
#include <vector>
#include "Pomieszczenie.h"
#include "Grzejnik.h"
#include "Regulator.h"
#include "Regulator_BB.h"
#include "Regulator_PID.h"

class Symulacja {
private:
	Pomieszczenie pokoj;
	Grzejnik grzej;
	std::vector <float> t;
	std::vector <float> q;
	std::vector <float> temp;
	Regulator_BB reg_bb;
	Regulator_PID reg_pid;
	Regulator* reg_1 = &reg_bb;
	Regulator* reg_2 = &reg_pid;

public:
	Symulacja(float _x, float _y, float _z, float _moc);
	Regulator* dostep_do_reg_bb();
	Regulator* dostep_do_reg_pid();
	int wybor_regulacji();
	void iteracja(float _probkowanie);
	void przebieg(int _ile_razy, float _probkowanie);
	void zapis(int _ile_razy);
	void uzyj_regulator_BB(float _temp_zad);
	void uzyj_regulator_PID(float _dt, float _temp_zad);
	void zabez_1(int* _input);
	void zabez_2(float* _input);
};

