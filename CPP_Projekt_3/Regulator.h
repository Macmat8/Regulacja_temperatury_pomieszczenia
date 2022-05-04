#pragma once
#include <iostream>
#include"Grzejnik.h"
#include "Pomieszczenie.h"

class Regulator {
private:
	float zadanaTemperatura;
public:
	Regulator();
	Grzejnik g;
	Pomieszczenie p;
	virtual void steruj(float _temp_zad, float _dt, float _temp_akt) = 0;
	void ustaw_temp_zad(float _temp_zad);
	float podaj_temp_zad();
};