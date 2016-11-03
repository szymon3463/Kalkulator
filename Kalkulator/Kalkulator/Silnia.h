#include "MainWindow.h"
#include <vector>
#include <ctime>
#include <string>
#include <stdlib.h>

using namespace std;

class Silnia
{
public:
	vector <int> Vt;
	int sign;
	int podstawa;
	int ilosc;

	~Silnia();
	Silnia();
	Silnia(int i);
	Silnia(const Silnia & l);
};