#include "Liczby.h"
#include <vector>

Liczby::Liczby() 
{
	VtLiczby.push_back(0);
	sign = 0;
	podstawa = 1000000000;
	ilosc = 9;
}

Liczby::Liczby(QString sLiczba)
{
	VtLiczby.clear();
	sign = 0;
	podstawa = 1000000000;
	ilosc = 9;

	int nCurrentIndex = sLiczba.length() - 1;
	while (true)
	{
		QString sTMP = sLiczba.mid(nCurrentIndex - 8, 9);
		VtLiczby.push_back(sTMP.toInt());

		nCurrentIndex -= 9;

		if (nCurrentIndex < 0)
		{
			break;
		}
	}
}

Liczby::Liczby(int liczba)
{
	sign = 0;
	podstawa = 1000000000;
	ilosc = 9;

	//qDebug() <<"liczba" << liczba;
	int c=0;
	if(liczba>podstawa -1)
    { // ³adujemy wiecej niz 1 raz
        sign = 0;
		VtLiczby.push_back(liczba % podstawa);
		c = liczba / podstawa;
        while (c > 0)
        {
			VtLiczby.push_back(c % podstawa);
            c /= podstawa;
        }
    }
	if(liczba<podstawa && liczba>-1)
    { // kiedy miesci sie w 1 polu wektora i jest +
        sign = 0;
		VtLiczby.push_back(liczba % podstawa);
    }
    if(liczba<0 && liczba>-podstawa+1)
    { // kiedy miesci sie w 1 polu wektora i jest -
        sign = 1;
        liczba=abs(liczba);
		VtLiczby.push_back(liczba % podstawa);
    }
    if(liczba<-podstawa+1)
    {
        sign = 1;
        liczba = abs(liczba);
		VtLiczby.push_back(liczba % podstawa);
        c = liczba / podstawa;
        while (c > 0)
        {
			VtLiczby.push_back(c % podstawa);
            c /= podstawa;
        }
    }
}

Liczby::Liczby(const Liczby &l)
{
	sign = l.sign;
	podstawa = l.podstawa;
	ilosc = l.ilosc;

	VtLiczby.clear();
	for (unsigned i = 0; i<l.VtLiczby.size(); ++i)
	{
		VtLiczby.push_back(l.VtLiczby[i]);
	}
}

Liczby Liczby::operator- ( Liczby &y)
{
	// musimy rozpatrzec przypadek liczb ujemnych
	if (this->sign == 1 && y.sign == 1)
	{ // mamy -cos--(+)cos2(cos2-cos) 2 ujemne wiec zmieniamy znaki na przeciwne i odejmujemy
		this->sign = 1;
		y.sign = 0;
		Liczby tmp = *this + y;
		return tmp;
	}
	else if (this->sign == 1 && y.sign == 0)
	{ // dodanie 2 liczb ujemnych 1 ujemna 1 dodatnia
		this->sign = 1;
		y.sign = 1;
		Liczby tmp = *this + y;
		return tmp;
	}
	else if (this->sign == 0 && y.sign == 1)
	{ // dodanie 2 liczb ujemnych 1 ujemna 1 dodatnia
		this->sign = 0;
		y.sign = 0;
		Liczby tmp = *this + y;
		return tmp;
	}
	else if (this->sign == 0 && y.sign == 0)
	{
		Liczby Licz(*this);
		// zapobiega bledowi przy odejmowaniu wiekszych liczb
		if (*this<y) { Licz = y; Licz.sign = 1; y = *this; }

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
	return *this;
}

ostream & Liczby::operator << (ostream & out)
{ // musimy wypisaæ minus na poczatku reszta standart
	if (this->sign == 1) out << "-";
	int a = 0, d = 0;
	for (int i = this->VtLiczby.size() - 1; i >= 0; --i)
	{
		if (this->VtLiczby[i] > 0)
		{
			a = this->VtLiczby[i]; d = 0;
			while (a) { d++; a /= 10; }
			while (d != this->ilosc) { out << "0"; d++; }
			out << this->VtLiczby[i];
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

bool Liczby::operator<( const Liczby &y)
{
	// sprawdzenie + -
	if (this->sign > y.sign) return true;
	if (this->sign < y.sign) return false;

	// maja takie same znaki
	// wiec sprawdzamy dlugosc dluzsza = wieksza
	if (this->VtLiczby.size() > y.VtLiczby.size()) return false;
	if (this->VtLiczby.size() < y.VtLiczby.size()) return true;

	// teraz wiemy ze sa tak samo dlugie a maja ten sam znak wiec zostaje sprawdzanie znak po znaku
	// zaczniemy sprawdzanie od konca liczb

	for (int i = this->VtLiczby.size() - 1; i >= 0; ++i)
	{
		if (this->VtLiczby[i] < y.VtLiczby[i])
		{
			return true;
		}
		if (this->VtLiczby[i] > y.VtLiczby[i])
		{
			return false;
		}
	}
}

bool Liczby::operator> (Liczby &y)
{
	return y < *this;
}

Liczby Liczby::operator+ (Liczby &y)
{
	// jesli dodajemy 2 liczby ujemne to nic nie zmieniamy
	if ((this->sign == 1 && y.sign == 1) || (this->sign == 0 && y.sign == 0))
	{
		Liczby Licz(*this);
		for (unsigned int i = 0; i<y.VtLiczby.size(); ++i)
		{
			if (Licz.VtLiczby.size() == i) { Licz.VtLiczby.push_back(0); }
			Licz.VtLiczby[i] = Licz.VtLiczby[i] + y.VtLiczby[i];

			if (Licz.VtLiczby[i] > Licz.podstawa - 1)
			{
				unsigned int tmp = Licz.VtLiczby[i] % Licz.podstawa;
				Licz.VtLiczby[i] -= tmp;
				if (Licz.VtLiczby.size() <= i) // za mala pojemnosc wektora
				{
					Licz.VtLiczby.push_back(Licz.VtLiczby[i] / Licz.podstawa);
				}
				else // wystarczajaca pojemnosc wektora
				{
					Licz.VtLiczby[i+1] = Licz.VtLiczby[i] / Licz.podstawa;
				}
				Licz.VtLiczby[i] = tmp;
			}
		}
		return Licz;
	} // gdy liczby sa tych samych znakow
	else // kiedy sa roznych znakow
	{
		Liczby l;
		if (this->sign == 0)
		{
			// x jest dodatni wiec od dodatniej odejmujemy ujemna ze zmienionym znakiem
			y.sign = 0;
			l = *this + y;
		}
		else
		{
			// y jest dodatni wiec od dodatniego y odejmujemy ujemnego x ze zmienionym znakiem
			this->sign = 0;
			y.sign = 0;
			l = *this + y;
			l.sign = (l.sign + 1) % 2;
		}
		return l;
	}
}

Liczby Liczby::operator++ ()
{
	if (this->sign == 0)
	{
		this->VtLiczby[0] += 1;
		for (unsigned i = 0; i<this->VtLiczby.size(); ++i)
		{
			if (this->VtLiczby[i] > this->podstawa - 1)
			{
				if (i<this->VtLiczby.size() - 1)
				{
					this->VtLiczby[i + 1] += 1;
					this->VtLiczby[i] -= this->podstawa;
				}
				else
				{
					this->VtLiczby.push_back(1);
					this->VtLiczby[i] -= this->podstawa;
				}
			}
		}
	}
	else
	{ // uwzgledniamy liczby ujemne
		this->VtLiczby[0] -= 1;
		for (unsigned int i = this->VtLiczby.size() - 1; i >= 0; --i)
		{
			if (this->VtLiczby[i] < 0)
			{
				if (i<this->VtLiczby.size() - 1)
				{
					this->VtLiczby[i + 1] -= 1;
					this->VtLiczby[i] += this->podstawa;
					if (this->VtLiczby[i + 1] == 0) this->VtLiczby.pop_back();
				}
				else
				{ // zmianimy znak na dodatni
					this->sign = 0;
					this->VtLiczby[i] = abs(this->VtLiczby[i]);
				}
			}
		}
	}
	return *this;
}

Liczby Liczby::operator/ (const int & y)
{
	if (y < 0) this->sign = (this->sign + 1) % 2;
	int c = 0;
	for (unsigned int i = 0; i < this->VtLiczby.size(); i++)
	{
		this->VtLiczby[i] = int(((long long)(this->VtLiczby[i]) / y + c) % this->podstawa);
		c = int(((long long)(this->VtLiczby[i]) / y + c) / this->podstawa);
	}
	while (c > 0)
	{
		this->VtLiczby.push_back(c % this->podstawa);
		c /= this->podstawa;
	}
	return *this;
}

Liczby Liczby::operator/ (const Liczby &y)
{
	Liczby Licz(0);
	for (unsigned int i = 0; i < y.VtLiczby.size(); ++i)
	{
		Liczby pom(*this / y.VtLiczby[i]);
		Liczby pom2(0);
		for (unsigned int j = 1; j<i; ++j)
		{
			pom2.VtLiczby.push_back(0);
		}
		if (i != 0) { pom.VtLiczby.insert(pom.VtLiczby.begin(), pom2.VtLiczby.begin(), pom2.VtLiczby.end()); }
		Licz = Licz + pom;
	}
	Licz.sign = (this->sign + y.sign) % 2;
	return *this;
}

Liczby Liczby::operator* ( const int & y)
{
	if (y < 0) sign = (sign + 1) % 2;
	int c = 0;
	for (unsigned int i = 0; i < VtLiczby.size(); i++)
	{
		QString sTmp = QString::number((long long)VtLiczby[i] * y + c);
		VtLiczby[i] = int(((long long)(VtLiczby[i]) * y + c) % podstawa);
		c = int((long long)(sTmp.toLongLong() / podstawa));
	}
	while (c > 0)
	{
		VtLiczby.push_back(c % podstawa);
		c /= podstawa;
	}
	return *this;
}

Liczby Liczby::operator* (const Liczby &y)
{
	Liczby Licz(0);
	for (unsigned int i = 0; i < y.VtLiczby.size(); ++i)
	{
		Liczby pom(*this * y.VtLiczby[i]);
		Liczby pom2(0);
		for (unsigned int j = 1; j<i; ++j)
		{
			pom2.VtLiczby.push_back(0);
		}
		if (i != 0) { pom.VtLiczby.insert(pom.VtLiczby.begin(), pom2.VtLiczby.begin(), pom2.VtLiczby.end()); }
		Licz = Licz + pom;
	}
	Licz.sign = (this->sign + y.sign) % 2;
	return *this;
}

void Liczby::DebugToConsole()
{
	QString sTMP;
	for (int i = VtLiczby.size() - 1; i >= 0; i--)
	{
		QString sMyNumber = QString::number(VtLiczby[i]);
		if (VtLiczby[i] == 0)
		{
			for (int j = 0; j < ilosc; ++j)
			{
				sTMP += "0";
			}
		}
		else if (i != VtLiczby.size() - 1)
		{
			if (sMyNumber.size() < 9)
			{
				for (int j = 0; j < 9 - sMyNumber.size(); ++j)
				{
					sTMP += "0";
				}
			}
			sTMP += sMyNumber + " ";
		}
		else
		{
			sTMP += sMyNumber + " ";
		}
	}

	qDebug() << sTMP;
}

QString Liczby::ToString()
{
	QString sTMP;
	for (int i = VtLiczby.size()-1; i >= 0; i--)
	{
		QString sMyNumber = QString::number(VtLiczby[i]);
		if (VtLiczby[i] == 0)
		{
			for (int j = 0; j < ilosc; ++j)
			{
				sTMP += "0";
			}
		}
		else if (i != VtLiczby.size() - 1)
		{
			if (sMyNumber.size() < 9 )
			{
				for (int j = 0; j < 9 - sMyNumber.size(); ++j)
				{
					sTMP += "0";
				}
			}
			sTMP += sMyNumber + " ";
		}
		else
		{
			sTMP += sMyNumber;
		}
		
	}

	return sTMP;
}

Liczby Liczby::Silnia()
{
	Liczby l(1);
	int nTmp = VtLiczby[0];  
	for (int i = 2; i <= nTmp; i++)
	{
		l = l*i;
	}
	return l;
}

Liczby Liczby::Potega()
{
	int nTmp = VtLiczby[0];
	Liczby l(nTmp);

	l = l*l;
	qDebug() << l.ToString();
	return l;
}

