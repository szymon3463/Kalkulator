#include "Silnia.h"

Silnia::~Silnia()
{
	Vt.clear();
}
Silnia::Silnia()
{
	Vt.push_back(0);
	sign = 0;
	podstawa = 1000000000;
	ilosc = 9;
}

Silnia::Silnia(int i)
{
	int c = 0;
	if (i>podstawa - 1)
	{ // ³adujemy wiecej niz 1 raz
		sign = 0;
		Vt.push_back(i % podstawa);
		c = i / podstawa;
		while (c > 0)
		{
			Vt.push_back(c % podstawa);
			c /= podstawa;
		}
	}
	if (i<podstawa && i>-1)
	{ // kiedy miesci sie w 1 polu wektora i jest +
		sign = 0;
		Vt.push_back(i % podstawa);
	}
	if (i<0 && i>-podstawa + 1)
	{ // kiedy miesci sie w 1 polu wektora i jest -
		sign = 1;
		i = abs(i);
		Vt.push_back(i % podstawa);
	}
	if (i<-podstawa + 1)
	{
		sign = 1;
		i = abs(i);
		Vt.push_back(i % podstawa);
		c = i / podstawa;
		while (c > 0)
		{
			Vt.push_back(c % podstawa);
			c /= podstawa;
		}
	}
}