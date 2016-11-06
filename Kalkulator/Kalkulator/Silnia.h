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

	long long ObliczSilnie(int liczbaI);
};