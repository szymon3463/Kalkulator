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
	friend Liczby operator* (Liczby l, int y)
	{
		Liczby Licz(l);
		if (y < 0) Licz.sign = (Licz.sign + 1) % 2;
		int c = 0;
		for (unsigned int i = 0; i < Licz.VtLiczby.size(); i++)
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
		for (unsigned int i = 0; i < y.VtLiczby.size(); ++i)
		{
			Liczby pom(x * y.VtLiczby[i]);
			Liczby pom2(0);
			for (unsigned int j = 1; j<i; ++j)
			{
				pom2.VtLiczby.push_back(0);

			}
			if (i != 0) { pom.VtLiczby.insert(pom.VtLiczby.begin(), pom2.VtLiczby.begin(), pom2.VtLiczby.end()); }
			Licz = Licz + pom;

		}
		Licz.sign = (x.sign + y.sign) % 2;
		return Licz;
	}
	friend Liczby operator+ (Liczby x, Liczby y)
	{
		// jesli dodajemy 2 liczby ujemne to nic nie zmieniamy
		if ((x.sign == 1 && y.sign == 1) || (x.sign == 0 && y.sign == 0))
		{
			Liczby Licz(x);
			for (unsigned int i = 0; i<y.VtLiczby.size(); ++i)
			{
				if (Licz.VtLiczby.size() == i) { Licz.VtLiczby.push_back(0); }
				Licz.VtLiczby[i] = Licz.VtLiczby[i] + y.VtLiczby[i];

				if (Licz.VtLiczby[i] > Licz.podstawa - 1)
				{
					unsigned int tmp = Licz.VtLiczby[i] % Licz.podstawa;
					Licz.VtLiczby[i] -= tmp;
					if (Licz.VtLiczby.size() <= i) // za ma³a pojemnosc wektora
					{
						Licz.VtLiczby.push_back(Licz.VtLiczby[i] / Licz.podstawa);
					}
					else // wystarczajaca pojemnosc wektora
					{
						Licz.VtLiczby[i + 1] += Licz.VtLiczby[i] / Licz.podstawa;
					}
					Licz.VtLiczby[i] = tmp;
				}
			}
			return Licz;
		} // gdy liczby sa tych samych znakow
		else // kiedy sa roznych znakow
		{
			Liczby l;
			if (x.sign == 0)
			{
				// x jest dodatni wiec od dodatniej odejmujemy ujemna ze zmienionym znakiem
				y.sign = 0;
				l = x - y;
			}
			else
			{
				// y jest dodatni wiec od dodatniego y odejmujemy ujemnego x ze zmienionym znakiem
				x.sign = 0;
				y.sign = 0;
				l = x - y;
				l.sign = (l.sign + 1) % 2;
			}

			return l;
		}
	}
	friend void operator++ (Liczby & l)
	{
		if (l.sign == 0)
		{
			l.VtLiczby[0] += 1;
			for (unsigned i = 0; i<l.VtLiczby.size(); ++i)
			{
				if (l.VtLiczby[i] > l.podstawa - 1)
				{
					if (i<l.VtLiczby.size() - 1)
					{
						l.VtLiczby[i + 1] += 1;
						l.VtLiczby[i] -= l.podstawa;
					}
					else
					{
						l.VtLiczby.push_back(1);
						l.VtLiczby[i] -= l.podstawa;
					}
				}
			}
		}
		else
		{ // uwzgledniamy liczby ujemne
			l.VtLiczby[0] -= 1;
			for (unsigned int i = l.VtLiczby.size() - 1; i >= 0; --i)
			{
				if (l.VtLiczby[i] < 0)
				{
					if (i<l.VtLiczby.size() - 1)
					{
						l.VtLiczby[i + 1] -= 1;
						l.VtLiczby[i] += l.podstawa;
						if (l.VtLiczby[i + 1] == 0) l.VtLiczby.pop_back();
					}
					else
					{ // zmianimy znak na dodatni
						l.sign = 0;
						l.VtLiczby[i] = abs(l.VtLiczby[i]);
					}
				}
			}
		}
	}
	friend Liczby operator- (Liczby x, Liczby y)
	{
		// musimy rozpatrzec przypadek liczb ujemnych
		if (x.sign == 1 && y.sign == 1)
		{ // mamy -cos--(+)cos2(cos2-cos) 2 ujemne wiec zmieniamy znaki na przeciwne i odejmujemy
			x.sign = 1;
			y.sign = 0;
			Liczby tmp = x + y;
			return tmp;
		}
		else
		if (x.sign == 1 && y.sign == 0)
		{ // dodanie 2 liczb ujemnych 1 ujemna 1 dodatnia
			x.sign = 1;
			y.sign = 1;
			Liczby tmp = x + y;
			return tmp;
		}
		else

		if (x.sign == 0 && y.sign == 1)
		{ // dodanie 2 liczb ujemnych 1 ujemna 1 dodatnia
			x.sign = 0;
			y.sign = 0;
			Liczby tmp = x + y;
			return tmp;
		}
		else
		if (x.sign == 0 && y.sign == 0)
		{
			Liczby Licz(x);
			//cout << "\nLiczba z"<<z<< endl;
			//cout << "\nLiczba y"<<y<< endl;

			// zapobiega bledowi przy odejmowaniu wiekszych liczb
			if (x<y) { Licz = y; Licz.sign = 1; y = x; }

			//cout << "Size z = " << z.t.size();
			for (unsigned int i = 0; i<y.VtLiczby.size(); ++i)
			{

				if (Licz.VtLiczby.size() <= i){ Licz.VtLiczby.push_back(0); } //cout << "dodaje"; }
				//cout << "\nZ.t["<<i<<"] = " << z.t[i] << "\tminus" << "\ty.t["<<i<<"] = " << y.t[i];
				Licz.VtLiczby[i] = Licz.VtLiczby[i] - y.VtLiczby[i];
				//cout << "\nZ.t["<<i<<"] = " << z.t[i];
				if (Licz.VtLiczby[i] < 0)
				{

					// jesli mniejsze niz 0 to musimy pozyczyc
					if (Licz.VtLiczby.size() <= i + 1)
					{
						// nie mamy z czego pozyczac wiec stajemy sie liczba ujemna
						Licz.sign = 1;


					}
					else
					{
						unsigned int j = i + 1;
						while (j<Licz.VtLiczby.size() && j != i) // szuakamy pozyczki
						{
							if (Licz.VtLiczby[j] > 0) // jesli znajdujemy
							{
								Licz.VtLiczby[j] -= 1;
								Licz.VtLiczby[j - 1] += Licz.podstawa;
								j--;
							}
							else j++;
						} // while pozyczka
					} // else istnieje pozyczka
				} // if musimy pozyczac
			}

			// sprawdzamy czy aby na pewno wszystkie elementy wektora dodatnie
			for (unsigned i = 0; i<Licz.VtLiczby.size(); ++i)
			{
				if (Licz.VtLiczby[i]<0) Licz.VtLiczby[i] = abs(Licz.VtLiczby[i]);
			}
			for (int i = Licz.VtLiczby.size() - 1; i >= 1; --i)
			{
				if (Licz.VtLiczby[i] == 0) Licz.VtLiczby.pop_back();
			}
			return Licz;
		}
	}
	friend ostream& operator <<(ostream & out, Liczby l)
	{ // musimy wypisać minus na poczatku reszta standart
		if (l.sign == 1) out << "-";
		int a = 0, d = 0;
		for (int i = l.VtLiczby.size() - 1; i >= 0; --i)
		{
			if (l.VtLiczby[i] > 0)
			{
				a = l.VtLiczby[i]; d = 0;
				while (a) { d++; a /= 10; }
				while (d != l.ilosc) { out << "0"; d++; }
				out << l.VtLiczby[i];
			}
			else
			{
				for (int j = 0; j<9; ++j)
				{
					out << "0";
				}
			}
		}
		return out;
	}
	friend bool operator< (Liczby x, Liczby y)
	{
		// sprawdzenie + -
		if (x.sign > y.sign) return true;
		if (x.sign < y.sign) return false;

		// maja takie same znaki
		// wiec sprawdzamy dlugosc dluzsza = wieksza
		if (x.VtLiczby.size() > y.VtLiczby.size()) return false;
		if (x.VtLiczby.size() < y.VtLiczby.size()) return true;

		// teraz wiemy ze sa tak samo dlugie a maja ten sam znak wiec zostaje sprawdzanie znak po znaku
		// zaczniemy sprawdzanie od konca liczb

		for (int i = x.VtLiczby.size() - 1; i >= 0; ++i)
		{
			if (x.VtLiczby[i] < y.VtLiczby[i])
			{
				return true;
			}
			if (x.VtLiczby[i] > y.VtLiczby[i])
			{
				return false;
			}
		}
	} // bool operator <

	friend bool operator> (Liczby x, Liczby y)
	{
		return y < x;
	}
	void FromStringToInt();
};