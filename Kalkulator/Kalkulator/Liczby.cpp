#include "Liczby.h"
#include <vector>

Liczby::Liczby() 
{
	Vt.push_back(0);
	sign = 0;
	podstawa = 1000000000;
	ilosc = 9;

}

Liczby::Liczby(QString liczba)
{
	//qDebug() <<"liczba" << liczba;
	int c=0;
	if(liczba.toInt()>podstawa -1)
    { // �adujemy wiecej niz 1 raz
        sign = 0;
		Vt.push_back(liczba.toInt() % podstawa);
		c = liczba.toInt() / podstawa;
        while (c > 0)
        {
            Vt.push_back( c % podstawa );
            c /= podstawa;
        }
    }
	if(liczba.toInt()<podstawa && liczba.toInt()>-1)
    { // kiedy miesci sie w 1 polu wektora i jest +
        sign = 0;
		Vt.push_back(liczba.toInt() % podstawa);
    }
    if(liczba.toInt()<0 && liczba.toInt()>-podstawa+1)
    { // kiedy miesci sie w 1 polu wektora i jest -
        sign = 1;
        liczba=abs(liczba.toInt());
        Vt.push_back(liczba.toInt() % podstawa);
    }
    if(liczba.toInt()<-podstawa+1)
    {
        sign = 1;
        liczba = abs(liczba.toInt());
        Vt.push_back(liczba.toInt() % podstawa);
        c = liczba.toInt() / podstawa;
        while (c > 0)
        {
            Vt.push_back( c % podstawa );
            c /= podstawa;
        }
    }
        
}
