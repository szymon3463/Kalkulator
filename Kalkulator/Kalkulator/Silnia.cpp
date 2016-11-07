#include "Silnia.h"

Silnia::~Silnia()
{
	VtSilnia.clear();
}
Silnia::Silnia()
{
	VtSilnia.push_back(0);
	sign = 0;
	podstawa = 1000000000;
	ilosc = 9;
}

Silnia::Silnia(int i)
{
	int c = 0;
	if (i>podstawa - 1)
	{ // ładujemy wiecej niz 1 raz
		sign = 0;
		VtSilnia.push_back(i % podstawa);
		c = i / podstawa;
		while (c > 0)
		{
			VtSilnia.push_back(c % podstawa);
			c /= podstawa;
		}
	}
	if (i<podstawa && i>-1)
	{ // kiedy miesci sie w 1 polu wektora i jest +
		sign = 0;
		VtSilnia.push_back(i % podstawa);
	}
	if (i<0 && i>-podstawa + 1)
	{ // kiedy miesci sie w 1 polu wektora i jest -
		sign = 1;
		i = abs(i);
		VtSilnia.push_back(i % podstawa);
	}
	if (i<-podstawa + 1)
	{
		sign = 1;
		i = abs(i);
		VtSilnia.push_back(i % podstawa);
		c = i / podstawa;
		while (c > 0)
		{
			VtSilnia.push_back(c % podstawa);
			c /= podstawa;
		}
	}
}

Silnia::Silnia(const Silnia & s)
{
	sign = s.sign;
	VtSilnia.clear();
	for (unsigned i = 0; i<s.VtSilnia.size(); ++i)
	{
		VtSilnia.push_back(s.VtSilnia[i]);
	}
}

Silnia & Silnia::ObliczSilnie(int liczbaI)
{
	Silnia s(liczbaI);
	for (int i = 2; i < liczbaI; i++)
	{
		s = s * i;
	}
	return s;
}