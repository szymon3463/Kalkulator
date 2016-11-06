#include "Liczby.h"
#include <vector>

Liczby::Liczby() 
{
	Vt.push_back(0);
	sign = 0;
	podstawa = 1000000000;
	ilosc = 9;

}

Liczby::Liczby(int liczba)
{
	//qDebug() <<"liczba" << liczba;
	int c=0;
	if(liczba>podstawa -1)
    { // ³adujemy wiecej niz 1 raz
        sign = 0;
		Vt.push_back(liczba % podstawa);
		c = liczba / podstawa;
        while (c > 0)
        {
            Vt.push_back( c % podstawa );
            c /= podstawa;
        }
    }
	if(liczba<podstawa && liczba>-1)
    { // kiedy miesci sie w 1 polu wektora i jest +
        sign = 0;
		Vt.push_back(liczba % podstawa);
    }
    if(liczba<0 && liczba>-podstawa+1)
    { // kiedy miesci sie w 1 polu wektora i jest -
        sign = 1;
        liczba=abs(liczba);
        Vt.push_back(liczba % podstawa);
    }
    if(liczba<-podstawa+1)
    {
        sign = 1;
        liczba = abs(liczba);
        Vt.push_back(liczba % podstawa);
        c = liczba / podstawa;
        while (c > 0)
        {
            Vt.push_back( c % podstawa );
            c /= podstawa;
        }
    }
        
}
