#include <iostream>
#include "Grzejnik.h"

Grzejnik::Grzejnik(float _moc) 
	: moc_nom(_moc),
	poziom_mocy(0.01) {
}

void Grzejnik::ustaw_poziom(float _poziom) {
	poziom_mocy = _poziom; 
}

float Grzejnik::podaj_poziom_mocy() {
	return poziom_mocy;
}

float Grzejnik::emitowane_cieplo(float _probkowanie) {
	float ciep;
	ciep = poziom_mocy * moc_nom * _probkowanie;
	return ciep;
}