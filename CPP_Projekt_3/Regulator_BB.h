#pragma once
#include "Regulator.h"

class Regulator_BB : public Regulator {
private:

public:
	void steruj(float _temp_zad, float _dt, float _temp_akt);
};

