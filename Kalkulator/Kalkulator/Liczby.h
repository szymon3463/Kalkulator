#include "MainWindow.h"
#include <vector>
#include <ctime>
#include <string>
#include <stdlib.h>

using namespace std;
class Liczby
{
public:
	vector <int> VtLiczby;
	int sign;
	int podstawa;
	int ilosc;
	
	~Liczby() { VtLiczby.clear(); }
	Liczby();
	Liczby(int liczba);
	Liczby(const Liczby &l);
	/*Liczby & operator =(const Liczby & l)
	{
		if (this != &l)
		{
			sign = l.sign;
			for (int i = 0; i < VtLiczby.size(); i++)
			{
				VtLiczby.push_back(l.VtLiczby[i]);
			}
		}
		
		return *this;
	}
	friend Liczby operator* (Liczby l, int y)
	{
		Liczby Licz(l);
		if (y < 0) Licz.sign = (Licz.sign + 1) % 2;
		int c = 0;
		for (int i = 0; i < Licz.VtLiczby.size(); i++)
		{
			Licz.VtLiczby[i] = int(((long long)(Licz.VtLiczby[i]) * y + c) % Licz.podstawa);
			c = int(((long long)(Licz.VtLiczby[i]) * y + c) / Licz.podstawa);
		}
		while (c > 0)
		{
			Licz.VtLiczby.push_back(c % Licz.podstawa);
			c /= Licz.podstawa;

		}
		return Licz;
	}

	friend Liczby operator* (Liczby x, Liczby y)
	{
		Liczby Licz(0);
		for (int i = 0; i < y.VtLiczby.size(); ++i)
		{
			Liczby pom(x * y.VtLiczby[i]);
			Liczby pom2(0);
			for (int j = 1; j<i; ++j)
			{
				pom2.VtLiczby.push_back(0);

			}
			if (i != 0) { pom.VtLiczby.insert(pom.VtLiczby.begin(), pom2.VtLiczby.begin(), pom2.VtLiczby.end()); }
			Licz = Licz + pom;

		}
		Licz.sign = (x.sign + y.sign) % 2;
		return Licz;
	}*/
	void FromStringToInt();
};