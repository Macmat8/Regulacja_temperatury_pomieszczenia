#include <iostream>
#include "Regulator.h"

Regulator::Regulator() 
	: zadanaTemperatura(0),
	  g(0), 
	  p(0, 0, 0) {}

void Regulator::ustaw_temp_zad(float _temp_zad) {
	zadanaTemperatura = _temp_zad;
}

float Regulator::podaj_temp_zad() {
	return zadanaTemperatura;
}