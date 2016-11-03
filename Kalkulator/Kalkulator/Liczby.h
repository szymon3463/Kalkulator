#include "MainWindow.h"
#include <vector>
#include <ctime>
#include <string>
#include <stdlib.h>

using namespace std;
class Liczby
{
public:
	vector <int> Vt;
	int sign;
	int podstawa;
	int ilosc;
	
	~Liczby() { Vt.clear(); }
	Liczby();
	Liczby(QString liczba);

	void FromStringToInt();
};