#pragma once
#include "Regulator.h"

class Regulator_PID : public Regulator {
private:
	float e_pop = 0;
public:
	float const kp = 4.0;
	float const ki = 0.02;
	float const kd = 0.1;

	void ustaw_e_pop(float _e_pop);
	float podaj_e_pop();
	void steruj(float _temp_zad, float _dt, float _temp_akt);
};

