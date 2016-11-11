#include "MainWindow.h"
#include <vector>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <iostream>

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
	Liczby(QString sLiczba);
	Liczby(const Liczby &l);

	Liczby operator* (const int & y);
	Liczby operator* (const Liczby &y);
	Liczby operator+ (Liczby &y);
	Liczby operator++ ();
	Liczby operator- ( Liczby &y);
	Liczby operator/ (const int &y);
	Liczby operator/ (const Liczby &l);
	std::ostream & operator <<(std::ostream & out);
	bool operator< (const Liczby &y);
	bool operator> (Liczby &y);
	
	void FromStringToInt();

	void DebugToConsole();

	QString ToString();
	Liczby Silnia();
	Liczby Potega();
	Liczby Pierwiastek();
};