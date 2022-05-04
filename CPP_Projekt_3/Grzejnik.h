#pragma once
class Grzejnik {
private:
	const float moc_nom;
	float poziom_mocy;
public:
	Grzejnik(float _moc);
	float emitowane_cieplo(float _probkowanie);
	void ustaw_poziom(float _poziom);
	float podaj_poziom_mocy();
};

