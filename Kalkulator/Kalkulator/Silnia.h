#include "MainWindow.h"
#include <vector>
#include <ctime>
#include <string>
#include <stdlib.h>

using namespace std;

class Silnia
{
public:
	vector <int> VtSilnia;
	int sign;
	int podstawa;
	int ilosc;

	~Silnia();
	Silnia();
	Silnia(int i);
	Silnia(const Silnia & s);

	friend Silnia operator* (Silnia s, int y)
	{
		Silnia Sil(s);
		if (y < 0) Sil.sign = (Sil.sign + 1) % 2;
		int c = 0;
		for (int i = 0; i < Sil.VtSilnia.size(); i++)
		{
			Sil.VtSilnia[i] = int(((long long)(Sil.VtSilnia[i]) * y + c) % Sil.podstawa);
			c = int(((long long)(Sil.VtSilnia[i]) * y + c) / Sil.podstawa);
		}
		while (c > 0)
		{
			Sil.VtSilnia.push_back(c % Sil.podstawa);
			c /= Sil.podstawa;

		}
		return Sil;
	}

	friend Silnia operator* (Silnia x, Silnia y)
	{
		Silnia Sil(0);
		for (int i = 0; i < y.VtSilnia.size(); ++i)
		{
			Silnia pom(x * y.VtSilnia[i]);
			Silnia pom2(0);
			for (int j = 1; j<i; ++j)
			{
				pom2.VtSilnia.push_back(0);

			}
			if (i != 0) { pom.VtSilnia.insert(pom.VtSilnia.begin(), pom2.VtSilnia.begin(), pom2.VtSilnia.end()); }
			Sil = Sil + pom;

		}
		Sil.sign = (x.sign + y.sign) % 2;
		return Sil;
	}
	friend Silnia operator+ (Silnia x, Silnia y)
	{
		// jesli dodajemy 2 liczby ujemne to nic nie zmieniamy
		if ((x.sign == 1 && y.sign == 1) || (x.sign == 0 && y.sign == 0))
		{
			Silnia Sil(x);
			for (int i = 0; i<y.VtSilnia.size(); ++i)
			{
				if (Sil.VtSilnia.size() == i) { Sil.VtSilnia.push_back(0); }
				Sil.VtSilnia[i] = Sil.VtSilnia[i] + y.VtSilnia[i];

				if (Sil.VtSilnia[i] > Sil.podstawa - 1)
				{
					unsigned int tmp = Sil.VtSilnia[i] % Sil.podstawa;
					Sil.VtSilnia[i] -= tmp;
					if (Sil.VtSilnia.size() <= i) // za ma³a pojemnosc wektora
					{
						Sil.VtSilnia.push_back(Sil.VtSilnia[i] / Sil.podstawa);
					}
					else // wystarczajaca pojemnosc wektora
					{
						Sil.VtSilnia[i + 1] += Sil.VtSilnia[i] / Sil.podstawa;
					}
					Sil.VtSilnia[i] = tmp;
				}
			}

			return Sil;
		} // gdy liczby sa tych samych znakow
		else // kiedy sa roznych znakow
		{
			Silnia s;
			if (x.sign == 0)
			{
				// x jest dodatni wiec od dodatniej odejmujemy ujemna ze zmienionym znakiem
				y.sign = 0;
				s = x - y;
			}
			else
			{
				// y jest dodatni wiec od dodatniego y odejmujemy ujemnego x ze zmienionym znakiem
				x.sign = 0;
				y.sign = 0;
				s = x - y;
				s.sign = (s.sign + 1) % 2;
			}

			return s;
		}
	}
	friend void operator++ (Silnia & s)
	{
		if (s.sign == 0)
		{
			s.VtSilnia[0] += 1;
			for (unsigned i = 0; i<s.VtSilnia.size(); ++i)
			{
				if (s.VtSilnia[i] > s.podstawa - 1)
				{
					if (i<s.VtSilnia.size() - 1)
					{
						s.VtSilnia[i + 1] += 1;
						s.VtSilnia[i] -= s.podstawa;
					}
					else
					{
						s.VtSilnia.push_back(1);
						s.VtSilnia[i] -= s.podstawa;
					}
				}
			}
		}
		else
		{ // uwzgledniamy liczby ujemne
			s.VtSilnia[0] -= 1;
			for (int i = s.VtSilnia.size() - 1; i >= 0; --i)
			{
				if (s.VtSilnia[i] < 0)
				{
					if (i<s.VtSilnia.size() - 1)
					{
						s.VtSilnia[i + 1] -= 1;
						s.VtSilnia[i] += s.podstawa;
						if (s.VtSilnia[i + 1] == 0) s.VtSilnia.pop_back();
					}
					else
					{ // zmianimy znak na dodatni
						s.sign = 0;
						s.VtSilnia[i] = abs(s.VtSilnia[i]);
					}
				}
			}
		}
	}
	friend Silnia operator- (Silnia x, Silnia y)
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
			Silnia Sil(x);
			//cout << "\nLiczba z"<<z<< endl;
			//cout << "\nLiczba y"<<y<< endl;

			// zapobiega bledowi przy odejmowaniu wiekszych liczb
			if (x<y) { Sil = y; Sil.sign = 1; y = x; }

			//cout << "Size z = " << z.t.size();
			for (int i = 0; i<y.VtSilnia.size(); ++i)
			{

				if (Sil.VtSilnia.size() <= i){ Sil.VtSilnia.push_back(0); } //cout << "dodaje"; }
				//cout << "\nZ.t["<<i<<"] = " << z.t[i] << "\tminus" << "\ty.t["<<i<<"] = " << y.t[i];
				Sil.VtSilnia[i] = Sil.VtSilnia[i] - y.VtSilnia[i];
				//cout << "\nZ.t["<<i<<"] = " << z.t[i];
				if (Sil.VtSilnia[i] < 0)
				{

					// jesli mniejsze niz 0 to musimy pozyczyc
					if (Sil.VtSilnia.size() <= i + 1)
					{
						// nie mamy z czego pozyczac wiec stajemy sie liczba ujemna
						Sil.sign = 1;


					}
					else
					{
						int j = i + 1;
						while (j<Sil.VtSilnia.size() && j != i) // szuakamy pozyczki
						{
							if (Sil.VtSilnia[j] > 0) // jesli znajdujemy
							{
								Sil.VtSilnia[j] -= 1;
								Sil.VtSilnia[j - 1] += Sil.podstawa;
								j--;
							}
							else j++;
						} // while pozyczka
					} // else istnieje pozyczka
				} // if musimy pozyczac
			}

			// sprawdzamy czy aby na pewno wszystkie elementy wektora dodatnie
			for (unsigned i = 0; i<Sil.VtSilnia.size(); ++i)
			{
				if (Sil.VtSilnia[i]<0) Sil.VtSilnia[i] = abs(Sil.VtSilnia[i]);
			}
			for (int i = Sil.VtSilnia.size() - 1; i >= 1; --i)
			{
				if (Sil.VtSilnia[i] == 0) Sil.VtSilnia.pop_back();
			}
			return Sil;
		}
	}
	friend ostream& operator <<(ostream & out, Silnia l)
	{ // musimy wypisać minus na poczatku reszta standart
		if (l.sign == 1) out << "-";
		int a = 0, d = 0;
		for (int i = l.VtSilnia.size() - 1; i >= 0; --i)
		{
			if (l.VtSilnia[i] > 0)
			{
				a = l.VtSilnia[i]; d = 0;
				while (a) { d++; a /= 10; }
				while (d != l.ilosc) { out << "0"; d++; }
				out << l.VtSilnia[i];
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
	friend bool operator< (Silnia x, Silnia y)
	{
		// sprawdzenie + -
		if (x.sign > y.sign) return true;
		if (x.sign < y.sign) return false;

		// maja takie same znaki
		// wiec sprawdzamy dlugosc dluzsza = wieksza
		if (x.VtSilnia.size() > y.VtSilnia.size()) return false;
		if (x.VtSilnia.size() < y.VtSilnia.size()) return true;

		// teraz wiemy ze sa tak samo dlugie a maja ten sam znak wiec zostaje sprawdzanie znak po znaku
		// zaczniemy sprawdzanie od konca liczb

		for (int i = x.VtSilnia.size() - 1; i >= 0; ++i)
		{
			if (x.VtSilnia[i] < y.VtSilnia[i])
			{
				return true;
			}
			if (x.VtSilnia[i] > y.VtSilnia[i])
			{
				return false;
			}
		}
	} // bool operator <

	friend bool operator> (Silnia x, Silnia y)
	{
		return y < x;
	}
	
	Silnia & ObliczSilnie(int liczbaI);
};
