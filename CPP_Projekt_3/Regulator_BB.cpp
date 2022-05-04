#include "Regulator_BB.h"
#include"Grzejnik.h"
#include "Pomieszczenie.h"

void Regulator_BB::steruj(float _temp_zad, float _dt, float _temp_akt) {
	if (_temp_akt <= _temp_zad) {
		g.ustaw_poziom(1);
	}

	if (_temp_akt > _temp_zad) {
		g.ustaw_poziom(0);
	}
}