#include <iostream>
#include <stdio.h>
#include <cmath>
const double e = 2.7182818284;
char logo[] = "*********************************************************\n"

"* Nizhniy Novgorod Technical University *\n"

"* Study work number 3. Task number 1. *\n"

"* Performed student 19-IVT-3 Sukhorukov V.A. *\n"

"*********************************************************\n";
using namespace std;
int main()
{
	cout << logo;
	cout << "y=x^3+e^(x+1)"<<endl;
	double f[41][2];
	f[0][1] = (-4.0) * (-4.0) * (-4.0) + pow(e, -3.0);
	double yMax = f[0][1], yMin = f[0][1], j = -4.0;
	for (int i = 0; i <41; i ++)
	{
		f[i][0] = j * j * j + pow(e, j + 1.0);
		f[i][1] = j;
		if (f[i][0] > yMax) { yMax = f[i][0]; }
		if (f[i][0] < yMin) { yMin = f[i][0]; }
		printf("i= %2i        x[i]=%4.1lf        y[i]=%7.3lf  \n",i, f[i][1] , f[i][0]);
		j = j + 0.1;
	}
	cout << "yMax= " << yMax << "      yMin= = " << yMin<<endl;
	return 0;
}
