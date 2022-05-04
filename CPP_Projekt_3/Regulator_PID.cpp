#include <iostream>
#include <math.h>
#include "Regulator_PID.h"
#include "Grzejnik.h"
#include "Pomieszczenie.h"
#include "Regulator.h"

void Regulator_PID::ustaw_e_pop(float _e_pop) {
	e_pop = _e_pop;
}

float Regulator_PID::podaj_e_pop() {
	return e_pop;
}

void Regulator_PID::steruj(float _temp_zad, float _dt, float _temp_akt) {
	float e = 0, e_cal = 0, delta_e = 0;
	float u_p, u_i, u_d, u;
	
	e = _temp_zad - _temp_akt;
	e_cal += e * _dt;
	delta_e = (e - e_pop)/_dt;

	u_p = kp * e;
	u_i = ki * e_cal;
	u_d = kd * delta_e;
	u = u_p + u_i + u_d;

	g.ustaw_poziom(u);

	e_pop = e;
}
