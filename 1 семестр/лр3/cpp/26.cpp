#include <iostream>
#include <vector>
char logo[] = "*********************************************************\n"

"* Nizhniy Novgorod Technical University *\n"

"* Study work number 3. Task number 26. *\n"

"* Performed student 19-IVT-3 Sukhorukov V.A. *\n"

"*********************************************************\n";
using namespace std;
int proverkaN() {
	int n = 0;
	char b = 1;
	while (cin.good()) {
		if (n == 0) {
			cout << "write array size ";
			while (b != 0)
			{
				b = cin.get();
				if (b >= '0' && b <= '9')
				{
					n = n * 10 + (b - 48);

				}
				else {
					if (b != '\n')
					{
						cout << "error, write again " << endl;
						n = 0;
					}
					else
					{
						break;
					}
				}

			}
		}
		else {
			break;
		}
	}
	return n;
}
int main()
{
	cout << logo;
	int n = proverkaN(), aMin, iMin = 0;
	vector<int> a(n);
	cout << "write  array element ";
	cin >> a[0];
	aMin = a[0];
	for (int i = 1; i < n; i++) {
		cout << "write  array element ";
		cin >> a[i];
		if (a[i] < aMin) {
			aMin = a[i];
			iMin = i;
		}
	}
	vector<int>b(iMin + 1);
	for (int i = 0; i <= iMin; i++) {b[i] = a[i];}
	cout << "new array : "<<endl;
	for (int i = 0; i < iMin + 1; i++) { cout << b[i] << endl; }
	return 0;
}