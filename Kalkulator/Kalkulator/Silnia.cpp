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
	{ // ładujemy wiecej niz 1 raz
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

Silnia::Silnia(const Silnia & l)
{
	sign = l.sign;
	Vt.clear();
	for (unsigned i = 0; i<l.Vt.size(); ++i)
	{
		Vt.push_back(l.Vt[i]);
	}
}

Silnia operator+ (Silnia x, Silnia y)
{
	// jesli dodajemy 2 liczby ujemne to nic nie zmieniamy
	if ((x.sign == 1 && y.sign == 1) || (x.sign == 0 && y.sign == 0))
	{
		Silnia z(x);
		for (int i = 0; i<y.Vt.size(); ++i)
		{
			if (z.Vt.size() == i) { z.Vt.push_back(0); }
			z.Vt[i] = z.Vt[i] + y.Vt[i];

			if (z.Vt[i] > x.podstawa - 1)
			{
				unsigned int tmp = z.Vt[i] % x.podstawa;
				z.Vt[i] -= tmp;
				if (z.Vt.size() <= i) // za ma³a pojemnosc wektora
				{
					z.Vt.push_back(z.Vt[i] / x.podstawa);
				}
				else // wystarczajaca pojemnosc wektora
				{
					z.Vt[i + 1] += z.Vt[i] / x.podstawa;
				}
				z.Vt[i] = tmp;
			}
		}

		return z;
	} // gdy liczby sa tych samych znakow
	else // kiedy sa roznych znakow
	{
		Silnia z;
		if (x.sign == 0)
		{
			// x jest dodatni wiec od dodatniej odejmujemy ujemna ze zmienionym znakiem
			y.sign = 0;
			//z = x - y;
		}
		else
		{
			// y jest dodatni wiec od dodatniego y odejmujemy ujemnego x ze zmienionym znakiem
			x.sign = 0;
			y.sign = 0;
			//z = x - y;
			z.sign = (z.sign + 1) % 2;
		}

		return z;
	}
}
bool operator< (Silnia x, Silnia y)
{
	// sprawdzenie + -
	if (x.sign > y.sign) return true;
	if (x.sign < y.sign) return false;

	// maja takie same znaki
	// wiec sprawdzamy dlugosc dluzsza = wieksza
	if (x.Vt.size() > y.Vt.size()) return false;
	if (x.Vt.size() < y.Vt.size()) return true;

	// teraz wiemy ze sa tak samo dlugie a maja ten sam znak wiec zostaje sprawdzanie znak po znaku
	// zaczniemy sprawdzanie od konca liczb

	for (int i = x.Vt.size() - 1; i >= 0; ++i)
	{
		if (x.Vt[i] < y.Vt[i])
		{
			return true;
		}
		if (x.Vt[i] > y.Vt[i])
		{
			return false;
		}
	}
}

Silnia operator- (Silnia x, Silnia y)
{
	// musimy rozpatrzec przypadek liczb ujemnych
	if (x.sign == 1 && y.sign == 1)
	{ // mamy -cos--(+)cos2(cos2-cos) 2 ujemne wiec zmieniamy znaki na przeciwne i odejmujemy
		x.sign = 1;
		y.sign = 0;
		Silnia tmp = x + y;
		return tmp;
	}
	else
	if (x.sign == 1 && y.sign == 0)
	{ // dodanie 2 liczb ujemnych 1 ujemna 1 dodatnia
		x.sign = 1;
		y.sign = 1;
		Silnia tmp = x + y;
		return tmp;
	}
	else

	if (x.sign == 0 && y.sign == 1)
	{ // dodanie 2 liczb ujemnych 1 ujemna 1 dodatnia
		x.sign = 0;
		y.sign = 0;
		Silnia tmp = x + y;
		return tmp;
	}
	else
	if (x.sign == 0 && y.sign == 0)
	{
		Silnia z(x);
		//cout << "\nLiczba z"<<z<< endl;
		//cout << "\nLiczba y"<<y<< endl;

		// zapobiega bledowi przy odejmowaniu wiekszych liczb
		if (x<y) { z = y; z.sign = 1; y = x; }

		//cout << "Size z = " << z.t.size();
		for (int i = 0; i<y.Vt.size(); ++i)
		{

			if (z.Vt.size() <= i){ z.Vt.push_back(0); } //cout << "dodaje"; }
			//cout << "\nZ.t["<<i<<"] = " << z.t[i] << "\tminus" << "\ty.t["<<i<<"] = " << y.t[i];
			z.Vt[i] = z.Vt[i] - y.Vt[i];
			//cout << "\nZ.t["<<i<<"] = " << z.t[i];
			if (z.Vt[i] < 0)
			{

				// jesli mniejsze niz 0 to musimy pozyczyc
				if (z.Vt.size() <= i + 1)
				{
					// nie mamy z czego pozyczac wiec stajemy sie liczba ujemna
					z.sign = 1;


				}
				else
				{
					int j = i + 1;
					while (j<z.Vt.size() && j != i) // szuakamy pozyczki
					{
						if (z.Vt[j] > 0) // jesli znajdujemy
						{
							z.Vt[j] -= 1;
							z.Vt[j - 1] += z.podstawa;
							j--;
						}
						else j++;
					} // while pozyczka
				} // else istnieje pozyczka
			} // if musimy pozyczac
		}

		// sprawdzamy czy aby na pewno wszystkie elementy wektora dodatnie
		for (unsigned i = 0; i<z.Vt.size(); ++i)
		{
			if (z.Vt[i]<0) z.Vt[i] = abs(z.Vt[i]);
		}
		for (int i = z.Vt.size() - 1; i >= 1; --i)
		{
			if (z.Vt[i] == 0) z.Vt.pop_back();
		}
		return z;
	}
}
void operator++ (Silnia & x)
{
	if (x.sign == 0)
	{
		x.Vt[0] += 1;
		for (unsigned i = 0; i<x.Vt.size(); ++i)
		{
			if (x.Vt[i] > x.podstawa - 1)
			{
				if (i<x.Vt.size() - 1)
				{
					x.Vt[i + 1] += 1;
					x.Vt[i] -= x.podstawa;
				}
				else
				{
					x.Vt.push_back(1);
					x.Vt[i] -= x.podstawa;
				}
			}
		}
	}
	else
	{ // uwzgledniamy liczby ujemne
		x.Vt[0] -= 1;
		for (int i = x.Vt.size() - 1; i >= 0; --i)
		{
			if (x.Vt[i] < 0)
			{
				if (i<x.Vt.size() - 1)
				{
					x.Vt[i + 1] -= 1;
					x.Vt[i] += x.podstawa;
					if (x.Vt[i + 1] == 0) x.Vt.pop_back();
				}
				else
				{ // zmianimy znak na dodatni
					x.sign = 0;
					x.Vt[i] = abs(x.Vt[i]);
				}
			}
		}
	}

}

Silnia operator* (Silnia x, int y)
{
	Silnia z(x);
	if (y < 0) z.sign = (z.sign + 1) % 2;
	int c = 0;
	for (int i = 0; i < x.Vt.size(); i++)
	{
		z.Vt[i] = int(((long long)(x.Vt[i]) * y + c) % x.podstawa);
		c = int(((long long)(x.Vt[i]) * y + c) / x.podstawa);
	}
	while (c > 0)
	{
		z.Vt.push_back(c % x.podstawa);
		c /= x.podstawa;

	}
	return z;
}

Silnia operator* (Silnia x, Silnia y)
{
	Silnia z(0);
	for (int i = 0; i < y.Vt.size(); ++i)
	{
		Silnia pom(x * y.Vt[i]);
		Silnia pom2(0);
		for (int j = 1; j<i; ++j)
		{
			pom2.Vt.push_back(0);

		}
		if (i != 0) { pom.Vt.insert(pom.Vt.begin(), pom2.Vt.begin(), pom2.Vt.end()); }
		z = z + pom;

	}
	z.sign = (x.sign + y.sign) % 2;
	return z;
}
